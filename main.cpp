#include <iostream>

#include <SDL2/SDL.h>
#include <string>

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

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }

    SDL_Window *window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_RESOLUTION_X, GAME_RESOLUTION_Y, 0);
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    while (true) {
        // draw a fully black screen
        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_UpdateWindowSurface(window);
    }

    return 0;
}