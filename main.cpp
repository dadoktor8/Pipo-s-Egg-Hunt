// On linux compile with:
// g++ -std=c++17 main.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp SDL_Init_BR.cpp BRFont.cpp Image_BR.cpp TileMap_BR.cpp Collision_BR.cpp DeltaTime_BR.cpp Player_BR.cpp Obstacle_BR.cpp Door.cpp ./glad/src/glad.c -I./glad/include -o prog.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image 
// C++ Standard Libraries
//all:
//g++ -Iinclude -Iinclude/SDL2 -Iinclude/headers -Llib *.cpp ./glad/src/glad.c -I./glad/include -o Zi.exe  -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image 
	//g++ -Iinclude -Iinclude/SDL2 -Iinclude/headers -Llib *.cpp ./glad/src/glad.c -I./glad/include -o Zi.exe  -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image 
#include <iostream>
#include <cmath>
#include <csignal>
#include <ctime>
#include <emscripten.h>
// Third-party library
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
//User Defined Classes
#include "include/headers/SDL_Init_BR.h"
#include "include/headers/BRFont.h"
#include "include/headers/Image_BR.h"
#include "include/headers/TileMap_BR.h"
#include "include/headers/Collision_BR.h"
#include "include/headers/DeltaTime_BR.h"
#include "include/headers/Player_BR.h"
#include "include/headers/Egg.h"
#include "emsdk/upstream/emscripten/cache/sysroot/include/emscripten/emscripten.h"
//emcc main.cpp SDL_Init_BR.cpp BRFont.cpp Image_BR.cpp TileMap_BR.cpp Collision_BR.cpp DeltaTime_BR.cpp Player_BR.cpp  -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 --preload-file res --preload-file fonts -o index.js
// Include GLAD
//#include <glad/glad.h>

//using namespace std; 

//Define the resolution in here
#define WIDTH 480
#define HEIGHT 640

struct context{
    volatile sig_atomic_t isRunning = false;
    //Initialize all the neccesary variables
    SDL_Window* window=nullptr;
    SDL_Renderer* renderer = nullptr; 
    //SDL_GLContext context_;
    SDL_Event event;
    bool gameIsRunning = true;

    //Important other variables
    const int FPS = 60;
    const int frameDelay = 1000/ FPS;
    Uint32 frameStart;
    int frameTime;
    Uint64 startTime;
    Uint64 currTime;
    Uint64 elapsedTime;
    SDL_TimerID timerId;
    Mix_Music *music = nullptr; 
    Mix_Chunk *sf = nullptr; 

    //Important Game Initializations
    SDL_Color White = {255,255,255};
    SDL_Color Black = {0,0,0};
    Font_BR titleFont;
    Font_BR menuFont;
    Font_BR creditFont; 
    Font_BR endFont;
    Font_BR retryFont;
    Font_BR scoreFont;
    Font_BR currentScoreObj;
    Font_BR tutObj;
    Image_BR playerSec;
    Image_BR playerThird;
    Image_BR newImage;
    Image_BR bushImage_leftFirst;
    Image_BR bushImage_leftSecond;
    Image_BR bushImage_rightFirst;
    Image_BR bushImage_rightSecond;
    Player_BR playerOne; 
    Image_BR IR_blueWitch;
    Collision_BR collision;
    DeltaTime_BR deltaTimeFunc;
    Egg eggs[4];



    //GameState Variables
    bool menuState = true;
    bool menuStateTransition = false;
    bool gameplayState = false;
    bool gameplayStateTransition = false;
    bool gameoverState = false;
    bool gameoverStateTransition = false;
    bool gameStateEasy;
    bool gameStateHard;
    int currentScore = 0;
    int getRandomVal;
    bool doItOnce = true;
    bool touched = false;
};

//Important Functions
void Init(context *ctx){
    ctx->newImage.Image_BR_Init(ctx->renderer,"res/bg.png",0,0,480,640);
    ctx->bushImage_leftFirst.Image_BR_Init(ctx->renderer,"res/bush.png",0,40,124,124);
    ctx->bushImage_leftSecond.Image_BR_Init(ctx->renderer,"res/bush.png",0, 320, 124,124);
    ctx->bushImage_rightFirst.Image_BR_Init(ctx->renderer,"res/bush.png",(480 - 124), 180, 124,124);
    ctx->bushImage_rightSecond.Image_BR_Init(ctx->renderer,"res/bush.png",(480 - 124), 460, 124,124);
    ctx->titleFont.Font_BR_Init(ctx->renderer,24,"Pipo's Egg Hunt",(WIDTH / 2) - 100,200,200,50,ctx->Black);
    ctx->menuFont.Font_BR_Init(ctx->renderer,24,"Start",(WIDTH / 2) - 45,300,100,50,ctx->Black);
    ctx->creditFont.Font_BR_Init(ctx->renderer,24,"Made By Studio Vaube!",(WIDTH / 2) - 100,400,200,50,ctx->Black);
    ctx->tutObj.Font_BR_Init(ctx->renderer,24,"Move UP and DOWN and Collect the EGGS!",(WIDTH/2) - 140,500,300,50,ctx->Black);
    ctx->playerSec.Image_BR_Init(ctx->renderer,"res/rabbitsec.png", -124,0,128,128); 
    ctx->playerThird.Image_BR_Init(ctx->renderer,"res/rabbitthird.png",-124,0,128,128);
    ctx->playerOne.initPlayerObjAnim(ctx->renderer,"res/rabbit.png",190,HEIGHT/2,128,128);
    ctx->scoreFont.Font_BR_Init(ctx->renderer,24,"SCORE",180,0,100,50,ctx->Black); 
    ctx->currentScoreObj.Font_BR_InitDynamic("fonts/PerfectDOSVGA437Win.ttf",24,ctx->Black);
    for(int i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            ctx->eggs[i].initEggObj(ctx->renderer,"res/egg2.png",-64,40,64,64); // Left first -> 0
            break;
        case 1:
            ctx->eggs[i].initEggObj(ctx->renderer,"res/egg2.png",-64,320,64,64); // Left second -> 1
            break;    
        case 2:
            ctx->eggs[i].initEggObj(ctx->renderer,"res/egg2.png",(480 + 64),180,64,64); // Right first -> 2
            break;
        case 3:
            ctx->eggs[i].initEggObj(ctx->renderer,"res/egg2.png",(480 + 64),460,64,64); // Right second -> 3
            break;
        default:
            break;
        }
    }

    ctx->endFont.Font_BR_Init(ctx->renderer,24,"You Lost!",(WIDTH / 2) - 100,200,200,50,ctx->Black);
    ctx->retryFont.Font_BR_Init(ctx->renderer,24,"Retry",(WIDTH / 2) - 45,300,100,50,ctx->Black);
    ctx->music = Mix_LoadMUS("res/music.wav");
    ctx->sf = Mix_LoadWAV("res/sf.wav");
}
void handleSignal(int signal, context *ctx) {
    ctx->isRunning = false;
}

void Input(context *ctx){

        while(SDL_PollEvent(&ctx->event)){
            if(ctx->event.type == SDL_QUIT){
                ctx->gameIsRunning= false;
                //signal(SIGINT, handleSignal(ct));
                SDL_Quit();
            }

        if(ctx->event.type == SDL_KEYUP)
        {
            switch (ctx->event.key.keysym.sym)
            {         
                case SDLK_w: 
                  //  newImage.Image_BR_setyVal(-1000 * deltaTime);
                    if(ctx->playerOne.getPlayerObjYpos() > ctx->playerOne.getPlayerObjH())
                    {
                        ctx->playerOne.setPlayerObjYposDynamic(-ctx->playerOne.getPlayerObjW());
                        //std::cout<<"Going Up \n";
                    }
                    break;                
                case SDLK_s: 
                  //  newImage.Image_BR_setyVal(1000 * deltaTime);
                    if(ctx->playerOne.getPlayerObjYpos() < HEIGHT - (ctx->playerOne.getPlayerObjH()*2))
                    {
                        ctx->playerOne.setPlayerObjYposDynamic(ctx->playerOne.getPlayerObjW());
                        //std::cout<<"Going Down \n";    
                    }
                    break;
                
                default:
                    break;
            }
        }
    }
}
Uint32 callback(Uint32 interval, void* name)
{
    context *ctx = static_cast<context*>(name);

    std::cout<<"Happening Once! "<<ctx->getRandomVal<<" Is it doing it once? "<<ctx->doItOnce<<" \n"; 
    return 0;
}

void Update(context *ctx){


    
    if(ctx->menuState == true)
    {
      // std::cout<<"Current state is Menu state \n";
       ctx->gameplayState = false;
       ctx->gameplayStateTransition = false;
        Mix_PlayMusic(ctx->music,-1);
        Mix_VolumeMusic(5000);
       ctx->menuStateTransition = ctx->collision.checkMouseCollision(ctx->menuFont.Font_BR_getxVal(),ctx->menuFont.Font_BR_getyVal(),ctx->menuFont.Font_BR_getwVal(),ctx->menuFont.Font_BR_gethVal());
    }
    if(ctx->menuStateTransition == true)
    {
        //cout<<"Going into Gameplay "<<endl;
        ctx->menuState = false;
        ctx->gameplayState = true;
        ctx->gameoverState = false;
    }
    if(ctx->gameplayState == true)
    {
        //std::cout<<"Current state is Gameplay state \n";
        ctx->menuStateTransition = false;
        ctx->playerSec.Image_BR_setxValstatic(ctx->playerOne.getPlayerObjXpos());
        ctx->playerSec.Image_BR_setyValstatic(ctx->playerOne.getPlayerObjYpos());
        ctx->playerThird.Image_BR_setxValstatic(ctx->playerOne.getPlayerObjXpos());
        ctx->playerThird.Image_BR_setyValstatic(ctx->playerOne.getPlayerObjYpos());
        ctx->currTime = SDL_GetTicks64();
        ctx->elapsedTime = ctx->currTime - ctx->startTime;
        if(ctx->doItOnce == true && ctx->elapsedTime >= 2000)
        {
            ctx->getRandomVal = (rand() % 4); 
            ctx->doItOnce = false;
            std::cout<<"Happening Once! "<<ctx->getRandomVal<<" Is it doing it once? "<<ctx->doItOnce<<" \n"; 
            ctx->startTime = ctx->currTime;
        }
        
        if(ctx->currentScore >= 0 && ctx->currentScore <= 15)
        {
            ctx->gameStateEasy = true;
            ctx->gameStateHard = false;
        }
        if(ctx->currentScore >= 15)
        {
            ctx->gameStateEasy = false;
            ctx->gameStateHard = true;
        }

        if(ctx->gameStateEasy == true && ctx->doItOnce == false)
        {
            if(ctx->elapsedTime >= 50)
            {   
                switch (ctx->getRandomVal)
                {
                    case 0:
                        ctx->eggs[ctx->getRandomVal].setXPosD(8); 
                        break;
                    case 1:
                        ctx->eggs[ctx->getRandomVal].setXPosD(8); 
                        break;
                    case 2:
                        ctx->eggs[ctx->getRandomVal].setXPosD(-8); 
                        break;
                    case 3:
                        ctx->eggs[ctx->getRandomVal].setXPosD(-8); 
                        break;
                    
                    default:
                        break;
                }
                ctx->startTime = ctx->currTime;
            }
        }

        if(ctx->gameStateHard == true)
        {
            if(ctx->elapsedTime >= 50)
            {
                //std::cout<<"Hello \n"; 
                for(int i = 0; i < 4; i++)
                {
                    switch (i)
                    {
                    case 0:
                        ctx->eggs[i].setXPosD(8); 
                        break;
                    case 1:
                        ctx->eggs[i].setXPosD(8); 
                        break;
                    case 2:
                        ctx->eggs[i].setXPosD(-8); 
                        break;
                    case 3:
                        ctx->eggs[i].setXPosD(-8); 
                        break;
                    
                    default:
                        break;
                    }
                }
                ctx->startTime = ctx->currTime; 
            }
        } 
        for(int i = 0; i < 4; i++)
        {
            if(i <= 1)
            {
                if(ctx->eggs[i].getXPos() > WIDTH )
                {
                    ctx->menuState= false;
                    ctx->gameplayState = false;
                    ctx->gameoverState = true; 
                    ctx->currentScore = 0;
                    //std::cout<<"Gameoverstate transition is "<<ctx->gameoverStateTransition<<" \n";
                    //std::cout<<"GameOver "<<"The egg is "<<i<<" \n";
                    ctx->eggs[0].setXPos(-64);ctx->eggs[1].setXPos(-64);
                    ctx->eggs[2].setXPos(WIDTH + 64);ctx->eggs[3].setXPos(WIDTH + 64);
                    break;
                    
                }
                    
            }    
            if(i <= 3 && i > 1)
            {
                if(ctx->eggs[i].getXPos() < 0)
                {
                    ctx->menuState= false;
                    ctx->gameplayState = false;
                    ctx->gameoverState = true; 
                    //std::cout<<"GameOver "<<"The egg is "<<i<<" \n";
                    ctx->currentScore = 0;
                    //ctx->gameoverStateTransition = 0;
                    ctx->eggs[i].setXPos(480 - 64);
                    ctx->eggs[0].setXPos(-64);ctx->eggs[1].setXPos(-64);
                    ctx->eggs[2].setXPos(WIDTH + 64);ctx->eggs[3].setXPos(WIDTH + 64);
                    break;
                }
                    
            }
            if(ctx->collision.checkObjCollision(ctx->playerOne.getPlayerObjXpos(),ctx->playerOne.getPlayerObjYpos(),ctx->playerOne.getPlayerObjW(),ctx->playerOne.getPlayerObjH(),
            ctx->eggs[i].getXPos(),ctx->eggs[i].getYPos(),64,64) == true)
            {
                std::cout<<"Egg "<<i<<" in contact with player \n";
                std::cout<<"Contact "<<ctx->currentScore<<" \n"; 
                ctx->currentScore++; 
                Mix_PlayChannel( 2, ctx->sf, 0 );
                Mix_Volume(2,5000);
                switch (i)
                {
                case 0:
                    ctx->touched = true;
                    ctx->eggs[i].setXPos(-64);
                    ctx->getRandomVal =(rand() % 4); 
                    break;
                case 1:
                    ctx->touched = true;
                    ctx->eggs[i].setXPos(-64);
                    ctx->getRandomVal =(rand() % 4);
                    break;
                case 2:
                    ctx->touched = true;
                    ctx->eggs[i].setXPos(480+64);
                    ctx->getRandomVal =(rand() % 4);
                    break;
                case 3:
                    ctx->touched = true;
                    ctx->eggs[i].setXPos(480+64);
                    ctx->getRandomVal =(rand() % 4);
                    break;
                
                default:
                    break;
                }
                

            }
        }
        //playerOne.updatePlayerObj(gameplayState,true,deltaTimeFunc.getDeltaTime(),playerOne.getPlayerObjH(),playerOne.getPlayerObjW(),playerOne.getPlayerObjH(),WIDTH,HEIGHT);
        ctx->gameoverStateTransition = ctx->collision.checkMouseCollision(ctx->scoreFont.Font_BR_getxVal(),ctx->scoreFont.Font_BR_getyVal(),ctx->scoreFont.Font_BR_getwVal(),ctx->scoreFont.Font_BR_gethVal());
    }

    if(ctx->gameoverStateTransition == true)
    {
        //cout<<"Going into Gameover "<<endl;

        ctx->menuState= false;
        ctx->gameplayState = false;
        ctx->gameoverState = true; 
    }
    if(ctx->gameoverState == true)
    {
       //std::cout<<"Current state is Gameover state \n"; 
       ctx->gameoverStateTransition = false;
       ctx->gameplayState = false;

       //cout<<"Gameplay state is "<<gameplayState<<endl;
       ctx->gameplayStateTransition = ctx->collision.checkMouseCollision(ctx->retryFont.Font_BR_getxVal(),ctx->retryFont.Font_BR_getyVal(),ctx->retryFont.Font_BR_getwVal(),ctx->retryFont.Font_BR_gethVal());
    }
    if(ctx->gameplayStateTransition == true)
    {
        //cout<<"Going into Menu "<<endl;
        ctx->menuState = true;
        ctx->gameplayState = false;
        ctx->gameoverState = false;
    }
   

}

   // }


void Draw(context *ctx){
    SDL_SetRenderDrawColor(ctx->renderer,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ctx->renderer);
   
    if(ctx->menuState == true)
    {
        ctx->newImage.Image_BR_Draw(ctx->renderer);
        ctx->titleFont.Font_Br_Draw(ctx->renderer);
        ctx->menuFont.Font_Br_Draw(ctx->renderer);
        ctx->creditFont.Font_Br_Draw(ctx->renderer);
        ctx->tutObj.Font_Br_Draw(ctx->renderer);
    }
    if(ctx->gameplayState == true)
    {
        ctx->newImage.Image_BR_Draw(ctx->renderer);
        ctx->currentScoreObj.Font_BR_DrawDynamic(ctx->renderer,24,std::to_string(ctx->currentScore),290,0,28,50,ctx->Black); 
        for(int i = 0; i < 4; i++)
            ctx->eggs[i].renderEggObj(ctx->renderer);
        ctx->bushImage_rightSecond.Image_BR_Draw(ctx->renderer);
        ctx->bushImage_rightFirst.Image_BR_Draw(ctx->renderer);
        ctx->bushImage_leftFirst.Image_BR_Draw(ctx->renderer);
        ctx->bushImage_leftSecond.Image_BR_Draw(ctx->renderer);
        if(ctx->currentScore == 0)
            ctx->playerOne.renderPlayerObjAnim(ctx->renderer);
        else
        {
            ctx->playerThird.Image_BR_Draw(ctx->renderer);
            if((ctx->touched == true && ctx->currentScore > 0) && ctx->elapsedTime >= 65)
            {
                ctx->playerSec.Image_BR_Draw(ctx->renderer);
                ctx->touched = false;
                ctx->startTime = ctx->currTime;
                std::cout<<ctx->elapsedTime<<" Elapsed Time \n"; 
            }
        }
            
       // else if((ctx->touched == true && ctx->currentScore > 0) && ctx->elapsedTime >= 5)
        //{
            //ctx->playerSec.Image_BR_Draw(ctx->renderer);

       // }
            

        ctx->scoreFont.Font_Br_Draw(ctx->renderer); 


    }
    if(ctx->gameoverState == true)
    {
        ctx->newImage.Image_BR_Draw(ctx->renderer);
        ctx->endFont.Font_Br_Draw(ctx->renderer);
        ctx->retryFont.Font_Br_Draw(ctx->renderer);
    }
   // 
    
    SDL_RenderPresent(ctx->renderer);
}

void loop(context *ctx)
{
    //while(ctx->gameIsRunning){ //Main Game Function! 
        ctx->frameStart = SDL_GetTicks(); // Capping it at 60 fps


        Update(ctx);
        Input(ctx);
        Draw(ctx);
        

        ctx->frameTime = SDL_GetTicks() - ctx->frameStart;

        if(ctx->frameDelay > ctx->frameTime)
        {
            SDL_Delay(ctx->frameDelay - ctx->frameTime);
         

        }

            
    //}

    //SDL_Delay(3000);

    //SDL_Delay(3000);

    //SDL_Delay(3000);

    //SDL_Delay(3000);

    //SDL_Delay(3000);
}
void mainloop(void *args)
{
    context *ctx = static_cast<context*>(args);
    loop(ctx);
}
int main(int argc, char* argv[]){
    context ctx;
    srand((unsigned) time(0));
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);





    // Setup our function pointers
    //gladLoadGLLoader(SDL_GL_GetProcAddress);
    SDL_Init_BR sdlInit("Pipo's Egg Hunt", 50, 50, WIDTH, HEIGHT);
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        std::cout<<"Couldn't initialize mixer \n";
        return 0;    
    }


    ctx.window = sdlInit.window();
    ctx.renderer = sdlInit.renderer();

    // OpenGL setup the graphics context
    //ctx->context_ = SDL_GL_CreateContext(ctx->window);
    

    Init(&ctx); //Initialize function
    emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1);
    ctx.startTime = SDL_GetTicks64();
    //SDL_TimerID timerId = SDL_AddTimer(1000,callback,nullptr);
    //loop(&ctx); 
   // while (1) { mainloop(); }
   



    //SDL_Quit();
    Mix_FreeMusic(ctx.music);
    Mix_FreeChunk(ctx.sf);
    Mix_CloseAudio();
    return 0;
}
