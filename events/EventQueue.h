//
// Created by satyamedh on 21/01/26.
//

#ifndef G_ENGINE_EVENTQUEUE_H
#define G_ENGINE_EVENTQUEUE_H

#include <queue>
#include <SDL_stdinc.h>

#include "EventType.h"

struct EventQueueEntry {
    EventType eventType;
    EventContextBase eventContext; // specific to event type
};

class EventQueue {
public:
    EventQueue() = default;

    void pushEvent(const EventType eventType, EventContextBase eventData) {
        eventQueue.push(EventQueueEntry(eventType, eventData));
    }

    void popEvent(EventQueueEntry& eventQueueEntry) {
        if (!eventQueue.empty()) {
            eventQueueEntry = eventQueue.front();
            eventQueue.pop();
        }
    }

    bool isEmpty() const {
        return eventQueue.empty();
    }

    uint32_t size() const {
        return static_cast<uint32_t>(eventQueue.size());
    }

private:
    std::queue<EventQueueEntry> eventQueue;

};


#endif //G_ENGINE_EVENTQUEUE_H