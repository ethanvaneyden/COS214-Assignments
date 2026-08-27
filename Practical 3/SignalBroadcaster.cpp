#include "SignalBroadcaster.h"
#include "SignalSubscriber.h"
#include "TechSignal.h"
#include <algorithm>
#include <vector>
using namespace std;

SignalBroadcaster::SignalBroadcaster(
    const vector<SignalSubscriber *> &subscribers) {
  this->subscribers = subscribers;
}

void SignalBroadcaster::subscribe(SignalSubscriber *subscriber) {
  subscribers.push_back(subscriber);
}

void SignalBroadcaster::unsubscribe(SignalSubscriber *subscriber) {
  subscribers.erase(remove(subscribers.begin(), subscribers.end(), subscriber),
                    subscribers.end());
}

void SignalBroadcaster::transmit(const TechSignal &signal) {
  for (auto subscriber : subscribers) {
    subscriber->update(signal);
  }
}

void SignalBroadcaster::clearSubscribers() { subscribers.clear(); }

size_t SignalBroadcaster::getSubscriberCount() const {
  return subscribers.size();
}
