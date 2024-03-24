#include "include/headers/Image_BR.h"
void Image_BR::Image_BR_Init(SDL_Renderer* renderer, char* loc, int x, int y, int w, int h)
{
    m_Surface = IMG_Load(loc);
    if(m_Surface == nullptr)
    {
        std::cout<<"Could not find Image"<<std::endl;
        exit(1);
    }
    else
    {
        std::cout<<"Image Found!\n";
        m_Texture = SDL_CreateTextureFromSurface(renderer,m_Surface); 
    }  

    if(m_Texture == nullptr)
        std::cout<<"Texture for Image not initialized \n"; 

    m_ImageRect.x = x; 
    m_ImageRect.y = y;
    m_ImageRect.w = w;
    m_ImageRect.h = h;
}
void Image_BR::Image_BR_Init(SDL_Renderer* renderer, char* loc)
{
    m_Surface = IMG_Load(loc);
    if(m_Surface == nullptr)
    {
        std::cout<<"Could not find Image"<<std::endl;
        exit(1);
    }
    else
    {
        std::cout<<"Image Found!\n";
        m_Texture = SDL_CreateTextureFromSurface(renderer,m_Surface); 
    }  

    if(m_Texture == nullptr)
        std::cout<<"Texture for Image not initialized \n"; 
}
void Image_BR::Image_BR_sInit(SDL_Renderer* renderer, char* loc, int x, int y, int w, int h,int sx, int sy, int sw, int sh)
{
    m_Surface = IMG_Load(loc);
    if(m_Surface == nullptr)
    {
        std::cout<<"Could not find Image"<<std::endl;
        exit(1);
    }
    else
    {
        std::cout<<"Image Found!\n";
        m_Texture = SDL_CreateTextureFromSurface(renderer,m_Surface); 
    }  

    if(m_Texture == nullptr)
        std::cout<<"Texture for Image not initialized \n"; 

    m_ImageRect.x = x; 
    m_ImageRect.y = y;
    m_ImageRect.w = w;
    m_ImageRect.h = h;

    m_sImageRect.x = sx; 
    m_sImageRect.y = sy;
    m_sImageRect.w = sw;
    m_sImageRect.h = sh;
}

void Image_BR::Image_BR_InitAnimated(SDL_Renderer* renderer, const char* loc, int x, int y,int frameWidth, int frameHeight, int frameCount, float frameDelay) {
    m_Surface = IMG_Load(loc);
    if(m_Surface == nullptr)
    {
        std::cout<<"Could not find Image"<<std::endl;
        exit(1);
    }
    else
    {
        std::cout<<"Image Found!\n";
        m_Texture = SDL_CreateTextureFromSurface(renderer,m_Surface); 
    }  

    if(m_Texture == nullptr)
        std::cout<<"Texture for Image not initialized \n"; 

    m_frameWidth = frameWidth;
    m_frameHeight = frameHeight;
    m_frameCount = frameCount;
    m_frameDelay = frameDelay;


    m_ImageRect.x = x; 
    m_ImageRect.y = y;
    m_ImageRect.w = frameWidth;
    m_ImageRect.h = frameHeight;

    m_center = {m_ImageRect.w/2, m_ImageRect.h/2}; 

}

void Image_BR::Image_BR_Draw(SDL_Renderer* renderer)
{
    if(m_Texture != nullptr)
    {
        SDL_RenderCopy(renderer,m_Texture,NULL,&m_ImageRect);
    }
    else
    {
        std::cout<<"Image texture could not be initialized!";
        exit(1);
    }
}

void Image_BR::update(float deltaTime) {
    m_frameTimer += deltaTime;
    //std::cout<<"m_frameTimer = "<<m_frameTimer<<" m_frameDelay = "<<m_frameDelay<<std::endl;
    if (m_frameTimer >= m_frameDelay) {
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        setAnimationRect(m_currentFrame);
        //std::cout<<"m_currentFrame = "<<m_currentFrame<<std::endl;
        m_frameTimer = 0.0f;
    }
}

void Image_BR::Image_BR_sDraw(SDL_Renderer* renderer, float deltaTime)
{
    if (m_Texture != nullptr) {
        // Update the animation
        update(deltaTime); // Assuming a constant frame time for simplicity
        // Render the current frame
        SDL_RenderCopyEx(renderer, m_Texture, &m_sImageRect, &m_ImageRect,m_angle,&m_center,SDL_FLIP_NONE);
    } else {
        std::cout << "Image texture could not be initialized!";
        exit(1);
    }
}

void Image_BR::setAnimationRect(int frameIndex) {
    m_sImageRect.x = frameIndex * m_frameWidth;
    m_sImageRect.y = 0;//frameIndex * m_frameHeight;
    m_sImageRect.w = m_frameWidth;
    m_sImageRect.h = m_frameHeight;
}



SDL_Texture* Image_BR::getTexture()
{
    if(m_Texture!= nullptr)
    {
        return m_Texture;
    }
    else
    {
        std::cout<<"Texture is null \n"; 
        exit(1);
    }
}
int Image_BR::Image_BR_getxVal()
{
    return m_ImageRect.x; 
}
int Image_BR::Image_BR_getyVal()
{
    return m_ImageRect.y; 
}
int Image_BR::Image_BR_getwVal()
{
    return m_ImageRect.w; 
}
int Image_BR::Image_BR_gethVal()
{
    return m_ImageRect.h; 
}
void Image_BR::Image_BR_setxVal(int x)
{
    m_ImageRect.x = m_ImageRect.x + x;
}
void Image_BR::Image_BR_setyVal(int y)
{
    m_ImageRect.y = m_ImageRect.y + y;
}
void Image_BR::Image_BR_setxValstatic(int x)
{
    m_ImageRect.x = x;
}
void Image_BR::Image_BR_setyValstatic(int y)
{
    m_ImageRect.y = y;
}
void Image_BR::Image_BR_setwVal(int w)
{
    m_ImageRect.w =  w;
}
void Image_BR::Image_BR_sethVal(int h)
{
    m_ImageRect.h = h;
}

void Image_BR::Image_BR_setangleValue(float angle)
{
    m_angle = angle;
}

Image_BR::~Image_BR()
{
    SDL_FreeSurface(m_Surface);
    SDL_DestroyTexture(m_Texture);
    IMG_Quit();
}