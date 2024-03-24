#include"include/headers/DeltaTime_BR.h"


float DeltaTime_BR::getDeltaTime()
{
        Uint64 currentPerformanceCounter = SDL_GetPerformanceCounter();
        m_deltaTime = static_cast<float>(currentPerformanceCounter - m_prevPerformanceCounter)/m_performanceFrequency;
        m_prevPerformanceCounter = currentPerformanceCounter;

        return m_deltaTime;
}