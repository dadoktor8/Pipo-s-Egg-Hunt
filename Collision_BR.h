#ifndef COLLISION_BR_HPP
#define COLLISION_BR_HPP

#include<SDL2/SDL.h>
#include<iostream>

class Collision_BR
{
    public:
        bool checkMouseCollision(int rX, int rY, int rW, int rH);
        bool checkObjCollision(int rect1X, int rect1Y, int rect1W, int rect1H, int rect2X, int rect2Y, int rect2W, int rect2H);
    private:
        SDL_Event event;
};





#endif