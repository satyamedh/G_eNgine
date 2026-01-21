//
// Created by satyamedh on 21/01/26.
//

#ifndef G_ENGINE_EVENTHANDLER_H
#define G_ENGINE_EVENTHANDLER_H
#include "EventHandler.h"
#include "EventQueue.h"

#define MAX_DISPATCH_EVENTS_PER_CYCLE 500

class EventManager {
public:
    EventManager() = default;

    void registerEvent(EventType eventType, EventHandler event);
    void deregisterEvent(EventType eventType, EventHandler event);

    void dispatchEvents(EventQueue* queue, bool finish = false);

private:
    std::unordered_map<EventType, std::vector<EventHandler>> eventMap;
};


#endif //G_ENGINE_EVENTHANDLER_H