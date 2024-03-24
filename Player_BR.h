#ifndef PLAYER_BR_HPP
#define PLAYER_BR_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "Image_BR.h"

class Player_BR
{

public:
    void initPlayerObj(SDL_Renderer* renderer, char* loc, int rX, int rY, int rW, int rH, int rFrames, float rTime);
    void initPlayerObjAnim(SDL_Renderer* renderer, char* loc, int rX, int rY, int rW, int rH);
    void updatePlayerObj(bool currentState, bool isCollisionActive, float deltaTime, float moveSpeed, int playerW, int playerH, int windowW, int windowH);
    void renderPlayerObj(SDL_Renderer* renderer, float deltaTime, float angle); 
    void renderPlayerObjAnim(SDL_Renderer* renderer);
    int getPlayerObjXpos();
    int getPlayerObjYpos();
    int getPlayerObjW();
    int getPlayerObjH();
    void setPlayerObjXpos(int x);
    void setPlayerObjYpos(int y);
    void setPlayerObjXposDynamic(int x);
    void setPlayerObjYposDynamic(int y);
private:
   SDL_Event event;
   Image_BR playerImage;
   float angle;
//Test for mouse look 
    int DeltaX; 
    int DeltaY;
    int mouseX,mouseY;
    double result;
};




#endif