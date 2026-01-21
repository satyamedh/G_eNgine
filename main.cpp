#include <iostream>

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

#include "GameEngineGlobals.h"
#include "gl.h"

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
    SDL_Surface *screen = SDL_CreateRGBSurfaceWithFormat(0, GAME_RESOLUTION_X, GAME_RESOLUTION_Y, 16, SDL_PIXELFORMAT_RGB565);

    SDL_Event event;

    EventManager event_manager;
    EventQueue event_queue;

    SDLEvents sdlEvents(&event_manager);

    spdlog::debug("Entering main loop...");

    isGameRunning = true;

    nglInit();
    nglSetBuffer(static_cast<COLOR *>(screen->pixels));

    while (isGameRunning) {
        // draw a fully black screen
        glColor3f(0.4f, 0.7f, 1.0f); // sky blue
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        nglDisplay();
        SDL_BlitSurface(screen, nullptr, SDL_GetWindowSurface(window), nullptr);
        SDL_UpdateWindowSurface(window);

        // poll events
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    spdlog::debug("Quitting... Creating quit event");
                    SDLEventContext quitCtx;
                    event_queue.pushEvent(EventType::Quit, quitCtx);
                    break;
                case SDL_MOUSEMOTION:
                case SDL_CLIPBOARDUPDATE:
                case SDL_AUDIODEVICEADDED:
                case SDL_TEXTEDITING:
                case SDL_WINDOWEVENT:
                    break; // we really don't care about these lol
                default:
                    spdlog::warn("Unhandled SDL event type: {}", event.type);
                    break;
            }
        }

        event_manager.dispatchEvents(&event_queue, false);

    }

    spdlog::debug("Exiting main loop...");

    // cleanup
    nglUninit();

    SDL_FreeSurface(screen);
    SDL_DestroyWindow(window);
    SDL_Quit();

    spdlog::info("Goodbye!");

    return 0;
}