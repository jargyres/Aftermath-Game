#include "player.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define PLAYERWALKINGFRAMES 3
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 128
#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

// double getAngle(int MouseX, int MouseY, int playerWidth, int playerHeight, int SCREENWIDTH, int SCREENHEIGHT);
int bulletsOnScreen = 0;
int switchedShootFrame = 0;
int lastFrame = 0;
int bulletsShowing[10] = {0,0,0,0,0,0,0,0,0,0};
int bulletsDirection[10] = {RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT};
int getBulletOffSetX(player * me, int direction);
int getBulletOffsetY(player * me, int direction);
int setNumbers(player * me, int numb);
void player_Constructor(player * me, char* normalImagePath, char* upImagePath, char* shootingImagePath, char* bulletImagePath, char* downImagePath, char* downShootImagePath, char* upShootImagePath, char* numberPath, char* ammoImagePath, char * ammoWordPath, char* playerWalkSound, char* playerShootSound,  int SCREENWIDTH, int SCREENHEIGHT, SDL_Renderer *rend){

    me->gunshot = NULL;
    me->ricePunch = NULL;

    me->gunshot = Mix_LoadWAV(playerShootSound);

    me->ricePunch = Mix_LoadWAV(playerWalkSound);
    // // me->gunshot = Mix_LoadWAV("music/BANGPOWBAP.wav");
    // if(me->gunshot == NULL) printf("couldnt find gunshot\n");
    // me->ricePunch = Mix_LoadWAV(playerWalkSound);
    // if(me->ricePunch == NULL) printf("couldnt find ricepunch\n");

    //window rect that will hold both the rect for the basic left and
    //right walking as well as the shooting rects
    me->screenwidth = SCREENWIDTH;
    me->screenheight = SCREENHEIGHT;

    me->windowRect.w = 128;
    me->windowRect.h = 128;
    me->windowRect.x = (SCREENWIDTH - me->windowRect.w) / 2;
    me->windowRect.y = (SCREENHEIGHT - me->windowRect.h) / 2;

    //rect to hold the rect for the walking up animation
    me->windowRect2.w = PLAYER_WIDTH;
    me->windowRect2.h = PLAYER_HEIGHT;
    me->windowRect2.x = me->windowRect.x;
    me->windowRect2.y = me->windowRect.y;

    //for the tens place of numbers


    me->bulletArray[0] = &(me->bulletRect1);
    me->bulletArray[1] = &(me->bulletRect2);
    me->bulletArray[2] = &(me->bulletRect3);
    me->bulletArray[3] = &(me->bulletRect4);
    me->bulletArray[4] = &(me->bulletRect5);
    me->bulletArray[5] = &(me->bulletRect6);
    me->bulletArray[6] = &(me->bulletRect7);
    me->bulletArray[7] = &(me->bulletRect8);
    me->bulletArray[8] = &(me->bulletRect9);
    me->bulletArray[9] = &(me->bulletRect10);

    for(int i = 0; i < 10; i++)
    {
        (*(me->bulletArray)[i]).w = 8;
        (*(me->bulletArray)[i]).h = 4;
        // (*(me->bulletArray)[i]).x = me->windowRect.x;
        // (*(me->bulletArray)[i]).y = me->windowRect.y + (me->windowRect.h /2);
        (*(me->bulletArray)[i]).x = 0;
        (*(me->bulletArray)[i]).y = 0;
    }
   

    me->normalWalkingTex = NULL;
    me->upWalkingTex = NULL;
    me->shootingTex = NULL;
    me->bulletTex = NULL;
    me->walkingDownTex = NULL;
    me->shootDownTex = NULL;
    me->shootUpTex == NULL;
    me->numberTex = NULL;
    me->ammoTex = NULL;
    me->ammoWordTex = NULL;
    
    SDL_Surface* surface = IMG_Load(normalImagePath);
    SDL_Surface* surface2 = IMG_Load(upImagePath);
    SDL_Surface* surface3 = IMG_Load(shootingImagePath);
    SDL_Surface* surface4 = IMG_Load(bulletImagePath);
    SDL_Surface* surface5 = IMG_Load(downImagePath);
    SDL_Surface* surface6 = IMG_Load(downShootImagePath);
    SDL_Surface* surface7 = IMG_Load(upShootImagePath);
    SDL_Surface* surface8 = IMG_Load(numberPath);
    SDL_Surface* surface9 = IMG_Load(ammoImagePath);
    SDL_Surface* surface10 = IMG_Load(ammoWordPath);


    me->normalWalkingTex = SDL_CreateTextureFromSurface(rend, surface);

    me->upWalkingTex = SDL_CreateTextureFromSurface(rend, surface2);
    
    me->shootingTex = SDL_CreateTextureFromSurface(rend, surface3);

    me->bulletTex = SDL_CreateTextureFromSurface(rend, surface4);

    me->walkingDownTex = SDL_CreateTextureFromSurface(rend, surface5);

    me->shootDownTex = SDL_CreateTextureFromSurface(rend, surface6);

    me->shootUpTex = SDL_CreateTextureFromSurface(rend, surface7);

    me->numberTex = SDL_CreateTextureFromSurface(rend, surface8);

    me->ammoTex = SDL_CreateTextureFromSurface(rend, surface9);

    me->ammoWordTex = SDL_CreateTextureFromSurface(rend, surface10);


    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);
    SDL_FreeSurface(surface3);
    SDL_FreeSurface(surface4);
    SDL_FreeSurface(surface5);
    SDL_FreeSurface(surface6);
    SDL_FreeSurface(surface7);
    SDL_FreeSurface(surface8);
    SDL_FreeSurface(surface9);
    SDL_FreeSurface(surface10);


    me->RectNormal.x = 0;
    me->RectNormal.y = 0;
    me->RectNormal.w = 192;
    me->RectNormal.h = 64;

    me->RectWalkingUp.x = 0;
    me->RectWalkingUp.y = 0;
    me->RectWalkingUp.w = 192;
    me->RectWalkingUp.h = 64;

    me->RectWalkingDown.x = 0;
    me->RectWalkingDown.y = 0;
    me->RectWalkingDown.w = 192;
    me->RectWalkingDown.h = 64;


    me->RectShooting.x = 0;
    me->RectShooting.y = 0;
    me->RectShooting.w = 128;
    me->RectShooting.h = 64;

    me->RectShootingDown.x = 0;
    me->RectShootingDown.y = 0;
    me->RectShootingDown.w = 128;
    me->RectShootingDown.h = 64;

    me->RectShootingUp.x = 0;
    me->RectShootingUp.y = 0;
    me->RectShootingUp.w = 128;
    me->RectShootingUp.h = 64;



    me->playerShootRectWin.w = PLAYER_WIDTH;
    me->playerShootRectWin.h = PLAYER_HEIGHT;
    me->playerShootRectWin.x = (SCREENWIDTH - me->playerShootRectWin.w) /2;
    me->playerShootRectWin.y = (SCREENHEIGHT - me->playerShootRectWin.h) /2;

    //for the tens place
    me->numberRect.w = 200;
    me->numberRect.h = 15;
    me->numberRect.x = 0;
    me->numberRect.y = 0;
    //for the ones place
    me->numberRect2.w = 200;
    me->numberRect2.h = 15;
    me->numberRect2.x = 0;
    me->numberRect2.y = 0;

    me->ammoRect.w = 15;
    me->ammoRect.h = 15;
    me->ammoRect.x = 15;
    me->ammoRect.y = SCREENHEIGHT - 70;

    me->ammoWordRect.w = 15;
    me->ammoWordRect.h = 15;
    me->ammoWordRect.x = 15;
    me->ammoWordRect.y = SCREENHEIGHT - 75;

    
    me->numberWindowRect.w = 20;
    me->numberWindowRect.h = 15;
    me->numberWindowRect.x = me->ammoRect.x + 30;
    me->numberWindowRect.y = me->ammoRect.y + 40;
    //for the ones place of numbers
    me->numberWindowRect2.w = 20;
    me->numberWindowRect2.h = 15;
    me->numberWindowRect2.x = me->numberWindowRect.x + 15;
    me->numberWindowRect2.y = me->numberWindowRect.y;

    SDL_QueryTexture(me->normalWalkingTex, NULL, NULL, &me->RectNormal.w, &me->RectNormal.h);
    SDL_QueryTexture(me->upWalkingTex, NULL, NULL, &me->RectWalkingUp.w, &me->RectWalkingUp.h);
    SDL_QueryTexture(me->shootingTex, NULL, NULL, &me->RectShooting.w, &me->RectShooting.h);
    SDL_QueryTexture(me->walkingDownTex, NULL, NULL, &me->RectWalkingDown.w, &me->RectWalkingDown.h);
    SDL_QueryTexture(me->shootDownTex, NULL, NULL, &me->RectShootingDown.w, &me->RectShootingDown.w);
    SDL_QueryTexture(me->shootUpTex, NULL, NULL, &me->RectShootingUp.w, &me->RectShootingUp.w);
    SDL_QueryTexture(me->numberTex, NULL, NULL, &me->numberRect.w, &me->numberRect.h);
    SDL_QueryTexture(me->numberTex, NULL, NULL, &me->numberRect2.w, &me->numberRect2.h);
    SDL_QueryTexture(me->ammoTex, NULL, NULL, &me->ammoRect.w, &me->ammoRect.h);
    SDL_QueryTexture(me->ammoWordTex, NULL, NULL, &me->ammoWordRect.w, &me->ammoWordRect.h);



    for(int i = 0; i < 10; i++)
    {
        SDL_QueryTexture(me->bulletTex, NULL, NULL, &(*(me->bulletArray)[i]).w,  &(*(me->bulletArray)[i]).h);
        (*(me->bulletArray))[i].w *= 2;
        (*(me->bulletArray))[i].h *= 2;

    }
    

    me->RectNormal.w /= PLAYERWALKINGFRAMES;
    me->RectWalkingUp.w /= PLAYERWALKINGFRAMES;
    me->RectShooting.w /= 2;
    me->RectShootingDown.w  = 64;
    me->RectShootingUp.w = 64;
    me->RectWalkingDown.w /= PLAYERWALKINGFRAMES;
    me->numberRect.w = 20;
    me->numberRect2.w = 20;
    me->ammoRect.w *= 5;
    me->ammoRect.h *= 5;
    

    me->bulletsLeft = 99;

    setNumbers(me, me->bulletsLeft);
 me->channel = 0;


}

void player_Move(player * me, int dx, int dy)
{
    me->posX += dx;
    me->posY += dy;

}

int num = 99;
int playingWalking = 0;
void player_Animate(player * me, int currentlyShooting, int currentlyWalking, int lastRight, int currentlyUp, int lastDown, int up, int down, int left, int right, int mouseAngle, SDL_Renderer *rend)
{

        

        if(currentlyWalking){
            int frames = PLAYERWALKINGFRAMES;

            int delayPerFrame = 220;

            int frame = (SDL_GetTicks() / delayPerFrame) % frames;

            me->RectNormal.x = frame * me->RectNormal.w;
            me->RectWalkingUp.x = frame * me->RectWalkingUp.w;
            me->RectWalkingDown.x = frame * me->RectWalkingDown.w;

            // Mix_HaltMusic();
            // Mix_PlayMusic(me->ricePunch, 0);



            if(frame == 0) me->channel = Mix_PlayChannel(1, (me->ricePunch), 0);
            /*int soundframes = 3;

            int sounddelayPerFrame = 200;

            int soundframe = (SDL_GetTicks() / delayPerFrame) % soundframes;

            if(soundframe == 0)
            {*/
            // if(me->channel != 0) playingWalking = 1;
            // else playingWalking = 0;
            //if(me->channel == 0) me->channel = Mix_PlayChannel(0, (me->gunshot), 0);

            // }


        }
        else if(currentlyShooting)
        {
            int ticks = SDL_GetTicks() / 200;
            int shootFrame = (ticks) % 2;
            me->RectShooting.x = shootFrame * me->RectShooting.w;
            me->RectShootingDown.x = shootFrame * me->RectShootingDown.w;
            me->RectShootingUp.x = shootFrame * me->RectShootingUp.w;

            if(lastFrame != shootFrame)
            {
                switchedShootFrame = 1;
                lastFrame = shootFrame;
            }
            else
            {
                switchedShootFrame = 0;
            }
            
            
            if(switchedShootFrame && shootFrame == 0 && me->bulletsLeft > 0)
            {
                if(bulletsOnScreen < 10)
                {                
                    
                    bulletsOnScreen++;
                    bulletsShowing[bulletsOnScreen] = 1;
                    if(lastDown) {
                        bulletsDirection[bulletsOnScreen] = DOWN;
                        (*(me->bulletArray)[bulletsOnScreen]).x = getBulletOffSetX(me, DOWN);
                        (*(me->bulletArray)[bulletsOnScreen]).y = getBulletOffsetY(me, DOWN);
                    }
                    else if(currentlyUp) {
                        bulletsDirection[bulletsOnScreen] = UP;
                        (*(me->bulletArray)[bulletsOnScreen]).x = getBulletOffSetX(me, UP);
                        (*(me->bulletArray)[bulletsOnScreen]).y = getBulletOffsetY(me, UP);                       
                    }
                    else if(lastRight){ 
                        bulletsDirection[bulletsOnScreen] = RIGHT;
                        (*(me->bulletArray)[bulletsOnScreen]).x = getBulletOffSetX(me, RIGHT);
                        (*(me->bulletArray)[bulletsOnScreen]).y = getBulletOffsetY(me, RIGHT);
                    }
                    else if(!lastRight && !lastDown && !currentlyUp){
                        bulletsDirection[bulletsOnScreen] = LEFT;
                        (*(me->bulletArray)[bulletsOnScreen]).x = getBulletOffSetX(me, LEFT);
                        (*(me->bulletArray)[bulletsOnScreen]).y = getBulletOffsetY(me, LEFT);                        
                    }
                    
                    me->channel = Mix_PlayChannel(-1, (me->gunshot), 0);
                    // Mix_HaltMusic();
                    // Mix_PlayMusic(me->gunshot, 0);

                }
                // setNumbers(me, num);
                
                me->bulletsLeft -= 1;
                if(me->bulletsLeft <= 0) me->bulletsLeft = 0;
                setNumbers(me, me->bulletsLeft);
                // printf("%d\n", num);


            }

        }
        else
        {
                //if we arent walking just show the first sprite so it looks like were standing still
            me->RectNormal.x = 0;
            me->RectNormal.x = 0;

        }



        if(lastRight && !currentlyUp && !currentlyShooting)
        {
                //this'll draw the right left images
            SDL_RenderCopyEx(rend, me->normalWalkingTex, &(me->RectNormal), &(me->windowRect), 0.0, NULL, SDL_FLIP_HORIZONTAL);
        }
        else if(currentlyUp && !currentlyShooting)
        {
                //this'll draw the walking up sprites
            SDL_RenderCopy(rend, me->upWalkingTex, &(me->RectWalkingUp), &(me->windowRect2));

        }
        else if(lastDown && ! currentlyShooting)
        {
            SDL_RenderCopy(rend, me->walkingDownTex, &(me->RectWalkingDown), &(me->windowRect));
        }
        else if(currentlyShooting && lastRight)
        {



            if((mouseAngle > 0 && mouseAngle < 40) || (mouseAngle < 0 && mouseAngle > -40))
            {
                SDL_RenderCopyEx(rend, me->shootingTex, &(me->RectShooting), &(me->windowRect), mouseAngle, NULL, SDL_FLIP_HORIZONTAL);
            }
            else
            {
                SDL_RenderCopyEx(rend, me->shootingTex, &(me->RectShooting), &(me->windowRect), 0.0, NULL, SDL_FLIP_HORIZONTAL);

            }

                
        }
        else if(currentlyShooting && lastDown)
        {

            SDL_RenderCopy(rend, me->shootDownTex, &(me->RectShootingDown), &(me->windowRect));
        }
        else if(currentlyShooting && currentlyUp)
        {

            SDL_RenderCopy(rend, me->shootUpTex, &(me->RectShootingUp), &(me->windowRect));
        }
        else if(currentlyShooting && !lastRight)
        {
                                // printf("%f ", angle);
                //-135
                //-150
            if((mouseAngle > -179 && mouseAngle < -130)  || (mouseAngle < 180 && mouseAngle > 140))
            {
                SDL_RenderCopyEx(rend, me->shootingTex, &(me->RectShooting), &(me->windowRect), mouseAngle - 180 , NULL, SDL_FLIP_NONE);
            }
            else
            {
                SDL_RenderCopy(rend, me->shootingTex, &(me->RectShooting), &(me->windowRect));
            }


                

        }
        
        else
        {
            SDL_RenderCopy(rend, me->normalWalkingTex, &(me->RectNormal), &(me->windowRect));

        }


        int temp = bulletsOnScreen;
        for(int i = 0; i < 10; i++)
        {
            if(bulletsShowing[i])
            {
                if(bulletsDirection[i] == RIGHT)
                {
                    //we are facing right so increment the bullets position
                    (*(me->bulletArray)[i]).x += 15;
                    // (*(me->bulletArray)[i]).y = getBulletOffsetY(me, RIGHT);
                }
                else if(bulletsDirection[i] == LEFT)
                {
                    (*(me->bulletArray)[i]).x -= 15;
                    // (*(me->bulletArray)[i]).y = getBulletOffsetY(me, LEFT);

                }
                else if(bulletsDirection[i] == DOWN)
                {
                    (*(me->bulletArray)[i]).y += 15;
                    // (*(me->bulletArray)[i]).x = getBulletOffSetX(me, DOWN);

                }
                else if(bulletsDirection[i] == UP)
                {
                    (*(me->bulletArray)[i]).y -= 15;
                    // (*(me->bulletArray)[i]).x = getBulletOffSetX(me, UP);

                }


                if((*(me->bulletArray)[i]).x >= me->windowRect.x + 1000 || (*(me->bulletArray)[i]).x <= me->windowRect.x - 1000 
                 || (*(me->bulletArray)[i]).y >= me->windowRect.y + 1000 || (*(me->bulletArray)[i]).y <= me->windowRect.y - 1000)
                {
                    bulletsShowing[i] = 0;
                    (*(me->bulletArray)[i]).x = me->windowRect.x;
                    (*(me->bulletArray)[i]).y = me->windowRect.y + (me->windowRect.h /2);
                }
            }      
        }

        if(bulletsOnScreen == 9)
        {
            bulletsOnScreen = -1;
        }

        for(int i = 0; i < 10; i++)
        {
            //printf("drawing %d bullets\n", bulletsOnScreen);
            if(bulletsDirection[i] == LEFT && bulletsShowing[i]) SDL_RenderCopy(rend, me->bulletTex,NULL, &(*(me->bulletArray)[i]));
            else if(bulletsDirection[i] == RIGHT && bulletsShowing[i]) SDL_RenderCopyEx(rend, me->bulletTex,NULL, &(*(me->bulletArray)[i]),0.0, NULL, SDL_FLIP_HORIZONTAL);
            else if(bulletsDirection[i] == UP && bulletsShowing[i]) SDL_RenderCopyEx(rend, me->bulletTex,NULL, &(*(me->bulletArray)[i]),90.0, NULL, SDL_FLIP_NONE);
            else if(bulletsDirection[i] == DOWN && bulletsShowing[i]) SDL_RenderCopyEx(rend, me->bulletTex,NULL, &(*(me->bulletArray)[i]),270.0, NULL, SDL_FLIP_NONE);
        }

        SDL_RenderCopy(rend, me->ammoWordTex, NULL, &(me->ammoWordRect));
        SDL_RenderCopy(rend, me->ammoTex, NULL, &(me->ammoRect));
        SDL_RenderCopy(rend, me->numberTex, &(me->numberRect), &(me->numberWindowRect));
        SDL_RenderCopy(rend, me->numberTex, &(me->numberRect2), &(me->numberWindowRect2));
    
}


void player_Free(player * me)
{

    SDL_DestroyTexture(me->normalWalkingTex);
    SDL_DestroyTexture(me->upWalkingTex);
    SDL_DestroyTexture(me->shootingTex);
    SDL_DestroyTexture(me->bulletTex);
    SDL_DestroyTexture(me->walkingDownTex);
    SDL_DestroyTexture(me->shootDownTex);
    SDL_DestroyTexture(me->shootUpTex);
    SDL_DestroyTexture(me->numberTex);
    SDL_DestroyTexture(me->ammoTex);
    SDL_DestroyTexture(me-> ammoWordTex);
    Mix_FreeChunk(me->gunshot);
    Mix_FreeChunk(me->ricePunch);
    // Mix_FreeChunk(me->gunshot);
    // Mix_FreeChunk(me->ricePunch);

}

int getBulletOffSetX(player * me, int direction)
{

    if(direction == RIGHT)
    {
        return me->windowRect.x + (me->windowRect.w);
    }
    else if(direction == LEFT)
    {
        return me->windowRect.x;
    }
    else if(direction == UP)
    {
        return me->windowRect.x + (me->windowRect.w / 2) - 5;
    }
    else if(direction == DOWN)
    {
        return me->windowRect.x + (me->windowRect.w / 2) - 3;
    }

}

int getBulletOffsetY(player * me, int direction)
{

    if(direction == RIGHT)
    {
        return me->windowRect.y + (me->windowRect.h / 2);
    }
    else if(direction == LEFT)
    {
        return me->windowRect.y + (me->windowRect.h / 2);
    }
    else if(direction == UP)
    {
        return me->windowRect.y;
    }
    else if(direction == DOWN)
    {
        return me->windowRect.y + (me->windowRect.h / 2);
    }


}

int setNumbers(player * me, int numb)
{
    int ones = (numb % 10);
    int tens = (numb / 10) % 10;

    me->numberRect.x = tens * me->numberRect.w;
    me->numberRect2.x = ones * me->numberRect2.w;

}



