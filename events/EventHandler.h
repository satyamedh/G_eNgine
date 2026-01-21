//
// Created by satyamedh on 21/01/26.
//

#ifndef G_ENGINE_EVENT_H
#define G_ENGINE_EVENT_H
#include <cstdint>

#include "EventGlobals.h"

struct EventContextBase {
};

// base Event class
class EventHandler {
public:
    virtual ~EventHandler() = default;

    uint32_t handlerId = globalHandlerIdCounter++;

    virtual void fire(EventContextBase ctx);
};

#endif //G_ENGINE_EVENT_H