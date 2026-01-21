#include <iostream>

#include <SDL2/SDL.h>

#include "GameEngineGlobals.h"

#include "events/EventManager.h"
#include "events/EventQueue.h"
#include "events/SDLEvents/SDLEvents.h"

#ifndef GAME_TITLE
#define GAME_TITLE "G_eNgine"
#endif

#ifndef GAME_VERSION
#define GAME_VERSION 0
#endif

#ifndef GAME_RESOLUTION_X
#define GAME_RESOLUTION_X 320
#endif

#ifndef GAME_RESOLUTION_Y
#define GAME_RESOLUTION_Y 240
#endif


int main() {

    std::cout << "Launching " << GAME_TITLE << "!..." << std::endl;

    std::cout << "Game version " << GAME_VERSION << std::endl;

    std::cout << "Initializing SDL..." << std::endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_RESOLUTION_X, GAME_RESOLUTION_Y, 0);
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    SDL_Event event;

    EventManager event_manager;
    EventQueue event_queue;

    SDLEvents sdlEvents(&event_manager);

    std::cout <<  "Entering main loop..." << std::endl;

    isGameRunning = true;

    while (isGameRunning) {
        // draw a fully black screen
        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_UpdateWindowSurface(window);

        // poll events
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    std::cout << "Quitting... Creating quit event" << std::endl;
                    SDLEventContext quitCtx;
                    event_queue.pushEvent(EventType::Quit, quitCtx);
                    break;
            }
        }

        event_manager.dispatchEvents(&event_queue, false);

    }

    std::cout << GAME_TITLE << ": Game Loop exited" << std::endl;

    // cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Goodbye!" << std::endl;

    return 0;
}