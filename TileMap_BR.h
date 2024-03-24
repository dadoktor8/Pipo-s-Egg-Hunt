#ifndef TILEMAP_BR_HPP
#define TILEMAP_BR_HPP

#include "Image_BR.h"
#include <SDL2/SDL.h>
#include <iostream>

class TileMap_BR
{
    public:
        void TileMap_BR_Init(SDL_Renderer* renderer, char* loc, int sW, int sH);
        void TileMap_BR_Draw(SDL_Renderer* renderer);
    private:
        static const int tX = 20; 
        static const int tY = 12;
        SDL_Rect m_Rect_tile_1;
        SDL_Rect m_Rect_tile_2;
        SDL_Rect m_Rect_tile_3;
        SDL_Rect m_Rect_tile_4;
        Image_BR m_tileImage;
        SDL_Rect tiles[tX][tY];
        int tilemap_draw[tX][tY];

};

#endif