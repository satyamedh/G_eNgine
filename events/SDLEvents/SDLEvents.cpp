//
// Created by satyamedh on 21/01/26.
//

#include "SDLEvents.h"

#include <iostream>

#include "../EventManager.h"
#include "../../GameEngineGlobals.h"

SDLEvents::SDLEvents(EventManager* eventManager) {
    eventManager->registerEvent(EventType::Quit, this);
    this->eventManager = eventManager;
}

SDLEvents::~SDLEvents() {
    // deregister from event manager
    eventManager->deregisterEvent(EventType::Quit, this);
}

void SDLEvents::fire(EventContextBase ctx) {
    // handle quit event
    SDLEventContext quitCtx = static_cast<SDLEventContext&>(ctx);
    // For now, just print a message
    std::cout << "SDLEvents: Quit event received. Stopping the game loop." << std::endl;

    isGameRunning = false;
}
