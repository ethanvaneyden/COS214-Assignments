#include "SignalBroadcaster.h"
#include "SignalSubscriber.h"
#include "TechSignal.h"
#include <algorithm>
#include <vector>

using namespace std;

SignalBroadcaster::SignalBroadcaster(
    const vector<SignalSubscriber *> &subscribers){

    this->subscribers = subscribers;
}

void SignalBroadcaster::subscribe(SignalSubscriber *subscriber){

    /*
     * FIX:
     * Do not add a nullptr subscriber.
     *
     * The original code allowed this:
     *
     *     subscribe(nullptr);
     *
     * Then transmit() would eventually try to call:
     *
     *     nullptr->update(signal);
     *
     * which could cause a crash.
     */
    if (subscriber == nullptr){
        return;
    }

    /*
     * Prevent the same subscriber from being added more than once.
     *
     * This is useful because EventComposite::add() subscribes its child
     * whenever the child is added.
     */
    if (find(subscribers.begin(), subscribers.end(), subscriber)
        != subscribers.end()){
        return;
    }

    subscribers.push_back(subscriber);
}

void SignalBroadcaster::unsubscribe(SignalSubscriber *subscriber){

    if (subscriber == nullptr){
        return;
    }

    subscribers.erase(
        remove(
            subscribers.begin(),
            subscribers.end(),
            subscriber
        ),
        subscribers.end()
    );
}

void SignalBroadcaster::transmit(const TechSignal &signal){

    /*
     * Send the signal to every registered subscriber.
     *
     * FIX:
     * Check for nullptr before calling update().
     *
     * This prevents a bad subscriber pointer from causing a crash.
     */
    for (auto subscriber : subscribers){

        if (subscriber != nullptr){
            subscriber->update(signal);
        }
    }
}

void SignalBroadcaster::clearSubscribers(){

    subscribers.clear();
}

size_t SignalBroadcaster::getSubscriberCount() const{

    return subscribers.size();
}
