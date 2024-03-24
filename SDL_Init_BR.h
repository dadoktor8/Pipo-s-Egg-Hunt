#ifndef SDL_INIT_BR_HPP
#define SDL_INIT_BR_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class SDL_Init_BR {
public:
    SDL_Init_BR(char* title, int x, int y, int w, int h);
    SDL_Window* window();
    SDL_Renderer* renderer();
    ~SDL_Init_BR();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

#endif 