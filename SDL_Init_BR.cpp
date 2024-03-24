#include "include/headers/SDL_Init_BR.h"
SDL_Init_BR::SDL_Init_BR(char* title, int x, int y, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    } else {
        std::cout << "SDL video system is ready to go\n";
    }
    if(TTF_Init() == -1) {
        std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
        exit(1);
    }
    if (IMG_Init(IMG_INIT_PNG))
    {
        std::cout<<" SDL2_image ready!\n"<<std::endl;
    }
    else{
        std::cout<<" SDL2_image could not be initialized!\n"<<std::endl;
    }
    SDL_SetWindowTitle(m_window,title);
    SDL_CreateWindowAndRenderer(w,h,0,&m_window,&m_renderer);
    //m_window = SDL_CreateWindow(title,
       // x,
       // y,
       // w,
       // h,
       // SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    //m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Window* SDL_Init_BR::window() {
    return m_window;
}

SDL_Renderer* SDL_Init_BR::renderer() {
    return m_renderer;
}

SDL_Init_BR::~SDL_Init_BR() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
}