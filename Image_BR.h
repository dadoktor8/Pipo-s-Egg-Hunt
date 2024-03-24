#ifndef IMAGE_BR_HPP
#define IMAGE_BR_HPP

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>

class Image_BR{
    public:
        void Image_BR_Init(SDL_Renderer* renderer, char* loc, int x, int y, int w, int h);
        void Image_BR_Init(SDL_Renderer* renderer, char* loc);
        void Image_BR_sInit(SDL_Renderer* renderer, char* loc, int x, int y, int w, int h,int sx, int sy, int sw, int sh);
        void Image_BR_Draw(SDL_Renderer* renderer); 
        void Image_BR_sDraw(SDL_Renderer* renderer, float deltaTime); 
        void Image_BR_InitAnimated(SDL_Renderer* renderer, const char* loc,  int x, int y, int frameWidth, int frameHeight, int frameCount, float frameDelay);
        void update(float deltaTime);
        void renderAnimation(SDL_Renderer* renderer); 
        void setAnimationRect(int frameIndex);
        SDL_Texture* getTexture();
        int Image_BR_getxVal();
        int Image_BR_getyVal();
        int Image_BR_getwVal();
        int Image_BR_gethVal();
        float Image_BR_getangleVal();
        void Image_BR_setxVal(int x);
        void Image_BR_setyVal(int y);
        void Image_BR_setxValstatic(int x);
        void Image_BR_setyValstatic(int y);
        void Image_BR_setwVal(int w);
        void Image_BR_sethVal(int h);
        void Image_BR_setangleValue(float angle); 
        ~Image_BR();
    private:
        SDL_Surface* m_Surface;
        SDL_Texture* m_Texture;
        SDL_Rect m_ImageRect;
        SDL_Rect m_sImageRect;
        SDL_Point m_center;
        SDL_RendererFlip flip;
        int m_frameWidth;
        int m_frameHeight;
        int m_frameCount;
        int m_currentFrame;
        float m_frameDelay;
        float m_frameTimer;
        float m_angle;
};
#endif