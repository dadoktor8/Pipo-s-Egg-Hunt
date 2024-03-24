#include "include/headers/BRFont.h"
void Font_BR::Font_BR_Init(SDL_Renderer* Frenderer,int fontSize,char* text,int x,int y,int w,int h, SDL_Color color)
{
    m_Font = TTF_OpenFont("fonts/PerfectDOSVGA437Win.ttf", fontSize);
    if(m_Font == nullptr)
    {
        std::cout<<"SDL_ttf could not initialize! SDL_ttf Error: \n"<< TTF_GetError();
        exit(1);
    }
    else
    {
        std::cout<<"Font initialized!\n";
        m_Surface = TTF_RenderText_Solid(m_Font,text,color); 
    }
   
    if(m_Surface != nullptr)
    {
        std::cout<<"Surface init for Font \n";
        m_Texture = SDL_CreateTextureFromSurface(Frenderer,m_Surface);        
    }else
        std::cout<<"Texture for Font not  OK!";  

    if(m_Texture == nullptr)
        std::cout<<"Texture for font not initialized \n"; 

    m_FontRect.x = x; 
    m_FontRect.y = y;
    m_FontRect.w = w;
    m_FontRect.h = h;
}
void Font_BR::Font_BR_InitDynamic(char* loc,int fontSize,SDL_Color color)
{
    m_DFont = TTF_OpenFont(loc,fontSize); 
}

void Font_BR::Font_Br_Draw(SDL_Renderer* renderer)
{
    
    if(m_Texture != nullptr)
        SDL_RenderCopy(renderer,m_Texture,NULL,&m_FontRect);
    else
    {
         std::cout<<"Cannot Draw Font!\n";
         exit(1);
    }
       
}
void Font_BR::Font_BR_DrawDynamic(SDL_Renderer* Frenderer,int fontSize,std::string t,int x,int y,int w,int h, SDL_Color color)
{
    const char *text = t.c_str();
    if(m_DFont == nullptr)
    {
        std::cout<<"SDL_ttf could not initialize! SDL_ttf Error: \n"<< TTF_GetError();
        exit(1);
    }
    m_Surface = TTF_RenderText_Solid(m_DFont,text,color);
    if(m_Surface != nullptr)
    {
        //std::cout<<"Surface init for Font Dynamic \n";
        m_Texture = SDL_CreateTextureFromSurface(Frenderer,m_Surface);        
    }else
        std::cout<<"Texture for Font not  OK! \n";  

    if(m_Texture == nullptr)
        std::cout<<"Texture for font not initialized \n"; 


    m_FontRect.x = x; m_FontRect.y = y; m_FontRect.w = w; m_FontRect.h = h;
    SDL_FreeSurface(m_Surface);
    SDL_RenderCopy(Frenderer,m_Texture,NULL,&m_FontRect);
    SDL_DestroyTexture(m_Texture);
}

SDL_Texture* Font_BR::getTexture()
{
    return m_Texture;
}
SDL_Rect Font_BR::getRect()
{
    return m_FontRect;
}

int Font_BR::Font_BR_getxVal()
{
    return m_FontRect.x; 
}
int Font_BR::Font_BR_getyVal()
{
    return m_FontRect.y; 
}
int Font_BR::Font_BR_getwVal()
{
    return m_FontRect.w; 
}
int Font_BR::Font_BR_gethVal()
{
    return m_FontRect.h; 
}

Font_BR::~Font_BR()
{
    SDL_FreeSurface(m_Surface);
    SDL_DestroyTexture(m_Texture);
    TTF_CloseFont(m_Font);
}