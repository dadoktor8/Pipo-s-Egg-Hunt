#ifndef BRFONT_HPP
#define BRFONT_HPP

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class Font_BR{
    public:
        void Font_BR_Init(SDL_Renderer* Frenderer,int fontSize,char* text,int x,int y,int w,int h, SDL_Color color);
        void Font_Br_Draw(SDL_Renderer* renderer);
        void Font_BR_InitDynamic(char* loc, int fontsize, SDL_Color color);
        void Font_BR_DrawDynamic(SDL_Renderer* Frenderer,int fontSize,std::string t,int x,int y,int w,int h, SDL_Color color);
        SDL_Texture* getTexture();
        SDL_Rect getRect();
        int Font_BR_getxVal();
        int Font_BR_getyVal();
        int Font_BR_getwVal();
        int Font_BR_gethVal();
        ~Font_BR();

    private:
        TTF_Font* m_Font;
        TTF_Font* m_DFont;
        SDL_Surface* m_Surface;
        SDL_Texture* m_Texture;
        SDL_Rect m_FontRect;
}; 

#endif