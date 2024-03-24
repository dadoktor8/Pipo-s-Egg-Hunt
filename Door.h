#ifndef DOOR_HPP
#define DOOR_HPP

#include<iostream>
#include<SDL2/SDL.h>
#include"Image_BR.h"


class Door
{


public:
    void initDoorObj(SDL_Renderer* renderer, char* loc, int rX, int rY, int rW, int rH);
    void renderDoorObj(SDL_Renderer* renderer);

    int getDoorObjXpos();
    int getDoorObjYpos();
    int getDoorObjW();
    int getDoorObjH();

    void setDoorXpos(int x);
    void setDoorYpos(int y);
    void setDoorW(int w);
    void setDoorH(int h);


private:
    Image_BR doorImage;

};





#endif