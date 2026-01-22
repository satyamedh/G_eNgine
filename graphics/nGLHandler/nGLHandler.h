//
// Created by satyamedh on 22/01/26.
//

#ifndef G_ENGINE_NGLHANDLER_H
#define G_ENGINE_NGLHANDLER_H

#include "../nGL/gl.h"
#include <SDL2/SDL.h>

class nGLHandler {
public:
    nGLHandler() = default;

    void init(SDL_Surface* screen, SDL_Window* window);
    void uninit();

    void setBackgroundColor(GLFix r, GLFix g, GLFix b);
    void clearScreen();

    void display();

private:
    GLFix bgColor[3] = {0, 0, 0};
    SDL_Surface* screen = nullptr;
    SDL_Window* window = nullptr;

};


#endif //G_ENGINE_NGLHANDLER_H