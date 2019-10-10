#include "player.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#define PLAYERWALKINGFRAMES 3
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 128

// double getAngle(int MouseX, int MouseY, int playerWidth, int playerHeight, int SCREENWIDTH, int SCREENHEIGHT);

void player_Constructor(player * me, char* normalImagePath, char* upImagePath, char* shootingImagePath, int SCREENWIDTH, int SCREENHEIGHT, SDL_Renderer *rend){

    //window rect that will hold both the rect for the basic left and
    //right walking as well as the shooting rects
    me->windowRect.w = 128;
    me->windowRect.h = 128;
    me->windowRect.x = (SCREENWIDTH - me->windowRect.w) / 2;
    me->windowRect.y = (SCREENHEIGHT - me->windowRect.h) / 2;

    //rect to hold the rect for the walking up animation
    me->windowRect2.w = PLAYER_WIDTH;
    me->windowRect2.h = PLAYER_HEIGHT;
    me->windowRect2.x = me->windowRect.x;
    me->windowRect2.y = me->windowRect.y;

    me->normalWalkingTex = NULL;
    me->upWalkingTex = NULL;
    me->shootingTex = NULL;
    
    SDL_Surface* surface = IMG_Load(normalImagePath);
    SDL_Surface* surface2 = IMG_Load(upImagePath);
    SDL_Surface* surface3 = IMG_Load(shootingImagePath);

    me->normalWalkingTex = SDL_CreateTextureFromSurface(rend, surface);

    me->upWalkingTex = SDL_CreateTextureFromSurface(rend, surface2);
    
    me->shootingTex = SDL_CreateTextureFromSurface(rend, surface3);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);
    SDL_FreeSurface(surface3);

    me->RectNormal.x = 0;
    me->RectNormal.y = 0;
    me->RectNormal.w = 192;
    me->RectNormal.h = 64;

    me->RectWalkingUp.x = 0;
    me->RectWalkingUp.y = 0;
    me->RectWalkingUp.w = 192;
    me->RectWalkingUp.h = 64;


    me->RectShooting.x = 0;
    me->RectShooting.y = 0;
    me->RectShooting.w = 128;
    me->RectShooting.h = 64;

    me->playerShootRectWin.w = PLAYER_WIDTH;
    me->playerShootRectWin.h = PLAYER_HEIGHT;
    me->playerShootRectWin.x = (SCREENWIDTH - me->playerShootRectWin.w) /2;
    me->playerShootRectWin.y = (SCREENHEIGHT - me->playerShootRectWin.h) /2;

    SDL_QueryTexture(me->normalWalkingTex, NULL, NULL, &me->RectNormal.w, &me->RectNormal.h);
    SDL_QueryTexture(me->upWalkingTex, NULL, NULL, &me->RectWalkingUp.w, &me->RectWalkingUp.h);
    SDL_QueryTexture(me->shootingTex, NULL, NULL, &me->RectShooting.w, &me->RectShooting.h);

    me->RectNormal.w /= PLAYERWALKINGFRAMES;
    me->RectWalkingUp.w /= PLAYERWALKINGFRAMES;
    me->RectShooting.w /= 2;


}

void player_Move(player * me, int dx, int dy)
{
    me->posX += dx;
    me->posY += dy;

}

void player_Animate(player * me, int currentlyShooting, int currentlyWalking, int lastRight, int currentlyUp, int mouseAngle, SDL_Renderer *rend)
{
        if(currentlyWalking){
            int frames = PLAYERWALKINGFRAMES;

            int delayPerFrame = 200;

            int frame = (SDL_GetTicks() / delayPerFrame) % frames;


            me->RectNormal.x = frame * me->RectNormal.w;
            me->RectWalkingUp.x = frame * me->RectWalkingUp.w;


        }
        else if(currentlyShooting)
        {
            int ticks = SDL_GetTicks() / 150;
            int shootFrame = (ticks) % 2;
            me->RectShooting.x = shootFrame * me->RectShooting.w;

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
        else if(currentlyUp)
        {
                //this'll draw the walking up sprites
            SDL_RenderCopy(rend, me->upWalkingTex, &(me->RectWalkingUp), &(me->windowRect2));

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

}


void player_Free(player * me)
{

    SDL_DestroyTexture(me->normalWalkingTex);
    SDL_DestroyTexture(me->upWalkingTex);
    SDL_DestroyTexture(me->shootingTex);

}

