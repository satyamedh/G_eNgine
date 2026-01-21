//
// Created by satyamedh on 21/01/26.
//

#include "EventManager.h"

#include <algorithm>

void EventManager::registerEvent(EventType eventType, EventHandler event) {
    eventMap[eventType].push_back(event);
}

void EventManager::deregisterEvent(EventType eventType, EventHandler event) {
    // TODO: Implement deregistration logic
}

void EventManager::dispatchEvents(EventQueue *queue, bool finish) {
    uint32_t eventsDispatched = 0;

    while (!queue->isEmpty() && (finish || eventsDispatched < MAX_DISPATCH_EVENTS_PER_CYCLE)) {
        EventQueueEntry entry;
        queue->popEvent(entry);

        auto handlersIt = eventMap.find(entry.eventType);
        if (handlersIt != eventMap.end()) {
            for (auto& handler : handlersIt->second) {
                handler.fire(entry.eventContext);
            }
        }

        eventsDispatched++;
    }
}

