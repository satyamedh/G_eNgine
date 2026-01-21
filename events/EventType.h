//
// Created by satyamedh on 21/01/26.
//

#ifndef G_ENGINE_EVENTMAPPING_H
#define G_ENGINE_EVENTMAPPING_H

#include <SDL.h>
#include <unordered_map>

// Events from different sources might collide
// Hence, we map them to our own event types.
// Mapping is handled when creating an EventQueueEntry object by the caller themselves.
enum EventType {
    None = 0,
    // SDL Events
    Quit, // SDL_QUIT
    // Keypad Events
    KeyDown,  // SDL_KEYDOWN
    KeyUp,  // SDL_KEYUP
};



#endif //G_ENGINE_EVENTMAPPING_H