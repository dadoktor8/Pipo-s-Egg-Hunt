#ifndef OBSTACLE_BR_HPP
#define OBSTACLE_BR_HPP

#include<iostream>
#include<SDL2/SDL.h>
#include"Image_BR.h"
#include"Collision_BR.h"
#include"Player_BR.h"

class Obstacle_BR
{

public:
    void initObstacleObj(SDL_Renderer* renderer, char* loc, int rX, int rY, int rW, int rH);
    void renderObstacleObj(SDL_Renderer* renderer);
    void isColliding(Player_BR getPlayer, Collision_BR collisionCheck);
    int getObstacleObjXpos();
    int getObstacleObjYpos();
    int getObstacleObjW();
    int getObstacleObjH();
    void setObstacleObjXpos(int x);
    void setObstacleObjYpos(int y);
    void setObstacleObjW(int w);
    void setObstacleObjH(int h);


private:
    Image_BR obstacleImage;

};

#endif