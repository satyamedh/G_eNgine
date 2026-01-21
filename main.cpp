#include <iostream>

#include <SDL2/SDL.h>
#include <string>

#include "events/EventManager.h"

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

    std::cout <<  "Entering main loop..." << std::endl;

    bool running = true;

    while (running) {
        // draw a fully black screen
        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_UpdateWindowSurface(window);

        // poll events
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    std::cout << "Quitting..." << std::endl;
                    running = false; // will quit next loop
                    break;
            }
        }
    }


    // cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Goodbye!" << std::endl;

    return 0;
}