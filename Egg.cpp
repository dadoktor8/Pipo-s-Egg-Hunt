#include"include/headers/Egg.h"
void Egg::initEggObj(SDL_Renderer* renderer, char* loc, int rX, int rY, int rW, int rH)
{
    eggImage.Image_BR_Init(renderer,loc,rX,rY,rW,rH);
}
void Egg::renderEggObj(SDL_Renderer* renderer)
{
    eggImage.Image_BR_Draw(renderer); 
}
int Egg::getXPos()
{
    return eggImage.Image_BR_getxVal();
}
int Egg::getYPos()
{
    return eggImage.Image_BR_getyVal();
}
void Egg::setXPos(int x)
{
    eggImage.Image_BR_setxValstatic(x);
}
void Egg::setYPos(int y)
{
    eggImage.Image_BR_setyValstatic(y);
}
void Egg::setXPosD(int x)
{
    eggImage.Image_BR_setxVal(x);
}
void Egg::setYPosD(int y)
{
    eggImage.Image_BR_setyVal(y);
}