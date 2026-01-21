//
// Created by satyamedh on 21/01/26.
//

#include "EventManager.h"

#include <algorithm>
#include <iostream>
#include <spdlog/spdlog.h>

void EventManager::registerEvent(EventType eventType, EventHandler* handler) {
    eventMap[eventType].push_back(handler);
}

void EventManager::deregisterEvent(EventType eventType, EventHandler* handler) {
    // TODO: Implement deregistration logic
}

void EventManager::dispatchEvents(EventQueue *queue, bool finish) {
    uint32_t eventsDispatched = 0;

    while (!queue->isEmpty() && (finish || eventsDispatched < MAX_DISPATCH_EVENTS_PER_CYCLE)) {
        EventQueueEntry entry{};
        queue->popEvent(entry);

        auto handlersIt = eventMap.find(entry.eventType);
        if (handlersIt != eventMap.end()) {
            for (auto& handler : handlersIt->second) {
                handler->fire(entry.eventContext);
            }
        } else {
            // No handlers registered for this event type! error out...
            spdlog::error("EventManager: No handlers registered for event type {}", static_cast<int>(entry.eventType));
        }

        eventsDispatched++;
    }
}

