#include "include/headers/Collision_BR.h"
bool Collision_BR::checkMouseCollision(int rX, int rY, int rW, int rH)
{
    int x, y; 
    Uint32 mousePos = SDL_GetMouseState(&x, &y);
    if(((x >= rX) && (x <= rX + rW)) &&((y >= rY) && (y <= rY + rH)))
    {
       // 
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                std::cout<<"Cursor in bounds \n"<<std::endl;
                return 1; 
            }
            
        }
        return 0;
    }
    else
        return 0;
}

bool Collision_BR::checkObjCollision(int rect1X, int rect1Y, int rect1W, int rect1H, int rect2X, int rect2Y, int rect2W, int rect2H)
{
    bool collisionX = (rect1X < (rect2X + rect2W)) && ((rect1X + rect1W) > rect2X);
    bool collisionY = (rect1Y < (rect2Y + rect2H)) && ((rect1Y + rect1H) > rect2Y);

    return collisionX && collisionY;
}

