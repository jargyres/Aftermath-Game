#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct {

    int posX;
    int posY;
    SDL_Rect windowRect;
    SDL_Rect windowRect2;
    SDL_Rect playerShootRectWin;
    SDL_Rect RectNormal;
    SDL_Rect RectShooting;
    SDL_Rect RectWalkingUp;
    SDL_Texture* normalWalkingTex;
    SDL_Texture* upWalkingTex;
    SDL_Texture* shootingTex;
    
    

} player;

void player_Constructor(player * me, char* normalImagePath, char* upImagePath, char* shootingImagePath,int screenWidth, int screenHeight, SDL_Renderer *rend);

void player_Move(player * me, int dx, int dy);

void player_Animate(player * me, int currentlyShooting, int currentlyWalking, int lastRight, int currentlyUp,int mouseAngle, SDL_Renderer *rend);

void player_Free(player * me);



#endif
