#ifndef DELTATIME_BR_HPP
#define DELTATIME_BR_HPP
#include <SDL2/SDL.h>

class DeltaTime_BR
{
public:
    float getDeltaTime();   
private:

    Uint64 m_performanceFrequency = SDL_GetPerformanceFrequency();
    Uint64 m_prevPerformanceCounter = SDL_GetPerformanceCounter();
    float m_deltaTime; 
};
#endif