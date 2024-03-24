#ifndef EGG_HPP
#define EGG_HPP

#include <SDL2/SDL.h>
#include "Image_BR.h"

class Egg
{
public:
    void initEggObj(SDL_Renderer* renderer, char* loc, int rX, int rY, int rW, int rH);
    void renderEggObj(SDL_Renderer* renderer);
    int getXPos();
    int getYPos();
    void setXPosD(int x);
    void setYPosD(int y);
    void setXPos(int x);
    void setYPos(int y);
    

private:
    Image_BR eggImage;
};

#endif