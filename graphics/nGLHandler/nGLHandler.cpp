//
// Created by satyamedh on 22/01/26.
//

#include "nGLHandler.h"


void nGLHandler::init(SDL_Surface *screen, SDL_Window *window) {
    this->screen = screen;
    this->window = window;
    nglInit();
    nglSetBuffer(static_cast<COLOR *>(this->screen->pixels));
}

void nGLHandler::uninit() {
    nglUninit();
}

void nGLHandler::setBackgroundColor(GLFix r, GLFix g, GLFix b) {
    this->bgColor[0] = r;
    this->bgColor[1] = g;
    this->bgColor[2] = b;
}


void nGLHandler::clearScreen() {
    glColor3f(this->bgColor[0], this->bgColor[1], this->bgColor[2]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void nGLHandler::display() {
    nglDisplay();
    SDL_BlitSurface(this->screen, nullptr, SDL_GetWindowSurface(this->window), nullptr);
    SDL_UpdateWindowSurface(this->window);
}
