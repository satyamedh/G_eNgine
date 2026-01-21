#include <iostream>

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

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

#ifndef DEBUG
#define DEBUG 0
#endif

int main() {
    if constexpr (DEBUG) {
        spdlog::set_level(spdlog::level::debug);
        spdlog::debug("Debug logging enabled");
    } else {
        spdlog::set_level(spdlog::level::info);
    }

    spdlog::info("Launching {} version {}", GAME_TITLE, GAME_VERSION);

    spdlog::debug("Initializing SDL...");

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        spdlog::error("SDL_Init Error: " + std::string(SDL_GetError()));
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_RESOLUTION_X, GAME_RESOLUTION_Y, 0);
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    SDL_Event event;

    EventManager event_manager;
    EventQueue event_queue;

    SDLEvents sdlEvents(&event_manager);

    spdlog::debug("Entering main loop...");

    isGameRunning = true;

    while (isGameRunning) {
        // draw a fully black screen
        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_UpdateWindowSurface(window);

        // poll events
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    spdlog::debug("Quitting... Creating quit event");
                    SDLEventContext quitCtx;
                    event_queue.pushEvent(EventType::Quit, quitCtx);
                    break;
            }
        }

        event_manager.dispatchEvents(&event_queue, false);

    }

    spdlog::debug("Exiting main loop...");

    // cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();

    spdlog::info("Goodbye!");

    return 0;
}