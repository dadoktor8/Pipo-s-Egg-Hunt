#include "include/headers/Player_BR.h"
void Player_BR::initPlayerObj(SDL_Renderer* renderer, char* loc, int rX, int rY, int rW, int rH, int rFrames, float rTime)
{
    playerImage.Image_BR_InitAnimated(renderer,loc,rX,rY,rW,rH,rFrames,rTime);
}
void Player_BR::initPlayerObjAnim(SDL_Renderer* renderer, char* loc, int rX, int rY, int rW, int rH)
{
    playerImage.Image_BR_Init(renderer,loc,rX,rY,rW,rH);
}
void Player_BR::updatePlayerObj(bool currentState, bool isCollisionActive, float deltaTime, float moveSpeed, int playerW, int playerH, int windowW, int windowH)
{
    while(SDL_PollEvent(&event))
    {
        if((event.type == SDL_KEYUP && currentState) && isCollisionActive)
        {
                switch (event.key.keysym.sym)
                {
                /*case SDLK_a: 
                  //  newImage.Image_BR_setxVal(-1000 * deltaTime);
                    if(playerImage.Image_BR_getxVal() > 64)
                    {
                        playerImage.Image_BR_setxVal(-moveSpeed * deltaTime);
                        //std::cout<<"Going Left \n";
                    }
                    break;
                case SDLK_d: 
                 //   newImage.Image_BR_setxVal(1000 * deltaTime);
                    if(playerImage.Image_BR_getxVal() < 1280 - (64*2))
                    {
                        playerImage.Image_BR_setxVal(moveSpeed * deltaTime);
                        //std::cout<<"Going Right \n";
                    }
                    break;    */            
                case SDLK_w: 
                  //  newImage.Image_BR_setyVal(-1000 * deltaTime);
                    if(playerImage.Image_BR_getyVal() > playerH)
                    {
                        playerImage.Image_BR_setyVal(-moveSpeed);
                        //std::cout<<"Going Up \n";
                    }
                    break;                
                case SDLK_s: 
                  //  newImage.Image_BR_setyVal(1000 * deltaTime);
                    if(playerImage.Image_BR_getyVal() < windowH - (playerH*2))
                    {
                        playerImage.Image_BR_setyVal(moveSpeed);
                        //std::cout<<"Going Down \n";    
                    }
                    break;
                
                default:
                    break;
                }
        }
    }
}

void Player_BR::renderPlayerObj(SDL_Renderer* renderer, float deltaTime,float angle)
{
    playerImage.Image_BR_sDraw(renderer,deltaTime); 
}

void Player_BR::renderPlayerObjAnim(SDL_Renderer* renderer)
{
    playerImage.Image_BR_Draw(renderer);
}

int Player_BR::getPlayerObjXpos()
{
    return playerImage.Image_BR_getxVal(); 
}

int Player_BR::getPlayerObjYpos()
{
    return playerImage.Image_BR_getyVal();
}

int Player_BR::getPlayerObjW()
{
    return playerImage.Image_BR_getwVal();
}

int Player_BR::getPlayerObjH()
{
    return playerImage.Image_BR_gethVal();
}

void Player_BR::setPlayerObjXpos(int x)
{
    playerImage.Image_BR_setxValstatic(x);
    std::cout<<"Current player pos x "<<x<<std::endl;
}

void Player_BR::setPlayerObjYpos(int y)
{
    playerImage.Image_BR_setyValstatic(y);
    std::cout<<"Current player pos y "<<y<<std::endl;
}

void Player_BR::setPlayerObjXposDynamic(int x)
{
    playerImage.Image_BR_setxVal(x);   
}

void Player_BR::setPlayerObjYposDynamic(int y)
{
    playerImage.Image_BR_setyVal(y);
}

