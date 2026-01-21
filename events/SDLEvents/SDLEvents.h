//
// Created by satyamedh on 21/01/26.
//

#ifndef G_ENGINE_SDLEVENTS_H
#define G_ENGINE_SDLEVENTS_H
#include "../EventHandler.h"
#include "../EventManager.h"

struct SDLEventContext : EventContextBase {
    // no additional data for quit event... yet
};

class SDLEvents : EventHandler{
public:
    SDLEvents(EventManager* eventManager);
    ~SDLEvents();

    void fire(EventContextBase ctx) override;

private:
    EventManager* eventManager;
};


#endif //G_ENGINE_SDLEVENTS_H