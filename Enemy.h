#ifndef ENEMY_HPP
#define ENEMY_HPP
#include<iostream>
#include"Image_BR.h"
#include<math.h>


class Enemy
{
public:
    void initEnemyObj(SDL_Renderer* renderer, char* loc, int rX, int rY, int rW, int rH );
    void renderEnemyObj(SDL_Renderer* renderer);
    void updateEnemyPos(float deltaTime,int playerPosX, int playerPosY);
    void preventMovement();
    void startMovement();
    int getEnemyObjXpos();
    int getEnemyObjYpos(); 
    int getEnemyObjW();
    int getEnemyObjH();
    void setObstacleObjXpos(int x);
    void setObstacleObjYpos(int y);
    void setObstacleObjW(int w);
    void setObstacleObjH(int h);

private:
    Image_BR enemyImage;
    bool canMove = true;

};
#endif