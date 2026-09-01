#include "EventComposite.h"
#include "EventComponent.h"

void EventComposite::add(EventComponent *component){

    /*
     * FIX 1:
     * Do not add a null component.
     *
     * Without this check, the vector could contain nullptr and later
     * functions such as open(), close(), or getStatus() could crash
     * when they try to use the component.
     */
    if(component == nullptr){
        return;
    }

    /*
     * FIX 2:
     * A component cannot be its own child.
     *
     * Example:
     *
     *     MainStage.add(MainStage);
     *
     * This would create an invalid hierarchy.
     */
    if(component == this){
        return;
    }

    /*
     * FIX 3:
     * A component can only have one parent.
     *
     * If the component already belongs to another parent, do not
     * automatically move it here.
     *
     * Moving is handled separately by operator>>.
     *
     * This keeps add() simple and prevents the hierarchy from
     * becoming inconsistent.
     */
    if(component->getParent() != nullptr &&
        component->getParent() != this){
        return;
    }

    /*
     * FIX 4:
     * Prevent the same child from being added twice.
     *
     * Without this check:
     *
     *     parent->add(child);
     *     parent->add(child);
     *
     * would result in the same pointer appearing twice in children.
     *
     * This could cause signals, status reports, visitor counts, etc.
     * to be processed twice.
     */
    if(std::find(
            children.begin(),
            children.end(),
            component
        ) != children.end()){

        return;
    }

    /*
     * Add the child to the hierarchy.
     */
    children.push_back(component);

    /*
     * Keep the child's parent pointer in sync with the children vector.
     */
    component->setParent(this);

    /*
     * Subscribe the child to this composite's broadcaster.
     *
     * This allows signals received by the composite to be passed
     * down to its children.
     */
    broadcaster->subscribe(component);
}


void EventComposite::remove(EventComponent *component){

    /*
     * FIX 5:
     * Do nothing if a null component is supplied.
     *
     * This makes remove() safer to call.
     */
    if(component == nullptr){
        return;
    }

    /*
     * Look for the component in this composite's children.
     */
    auto it = std::find(
        children.begin(),
        children.end(),
        component
    );

    /*
     * Only remove the component if it actually belongs to this
     * composite.
     *
     * This is important because remove() should not accidentally
     * change the parent of a component that belongs somewhere else.
     */
    if(it != children.end()){

        /*
         * Remove the parent relationship.
         */
    (*it)->setParent(nullptr);

        /*
         * Stop this composite from sending signals to the removed child.
         */
        broadcaster->unsubscribe(component);

        /*
         * Finally remove the child from the vector.
         */
        children.erase(it);
    }
}

std::string EventComposite::getDisplayDetails() const
{
  return getName() + " (" + getStaff() + ")";  
}

EventComposite::EventComposite(std::string name, EventComponent *parent)
    : EventComponent(name, parent),
      broadcaster(std::unique_ptr<SignalBroadcaster>(new SignalBroadcaster()))
{}

bool EventComposite::hasChildren() const{

    return !children.empty();
}
