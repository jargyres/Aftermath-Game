#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

typedef struct {

    int posX;
    int posY;
    int screenwidth;
    int screenheight;
    // int bulletsLeft;
    SDL_Rect windowRect;
    SDL_Rect windowRect2;
    // SDL_Rect numberWindowRect;
    // SDL_Rect numberWindowRect2;
    SDL_Rect enemyShootRectWin;
    SDL_Rect RectNormal;
    SDL_Rect RectShooting;
    SDL_Rect RectWalkingUp;
    SDL_Rect RectWalkingDown;
    SDL_Rect RectShootingDown;
    SDL_Rect RectShootingUp;
    SDL_Rect bulletRect1;
    SDL_Rect bulletRect2;
    SDL_Rect bulletRect3;
    SDL_Rect bulletRect4;
    SDL_Rect bulletRect5;
    SDL_Rect bulletRect6;
    SDL_Rect bulletRect7;
    SDL_Rect bulletRect8;
    SDL_Rect bulletRect9;
    SDL_Rect bulletRect10;
    SDL_Rect *bulletArray[10];
    // SDL_Rect numberRect;
    // SDL_Rect numberRect2;
    // SDL_Rect ammoRect;
    // SDL_Rect ammoWordRect;
    SDL_Texture* bulletTex;
    SDL_Texture* normalWalkingTex;
    SDL_Texture* upWalkingTex;
    SDL_Texture* shootingTex;
    SDL_Texture* walkingDownTex;
    SDL_Texture* shootDownTex;
    SDL_Texture* shootUpTex;
    // SDL_Texture* numberTex;
    // SDL_Texture* ammoTex;
    // SDL_Texture* ammoWordTex;
    
    

} enemy;

void enemy_Constructor(enemy * me, 
                char* normalImagePath, char* upImagePath, char* shootingImagePath, 
                char* bulletImagePath, char* downImagePath, char* downShootImagePath, 
                char* upShootImagePath, int screenWidth, int screenHeight, 
                SDL_Renderer *rend);

void enemy_SetPosition(enemy * me, int xPosScreen, int yPosScreen, int xPosBackground, int yPosBackground);

void enemy_MoveTowardsPlayer(enemy * me);

void enemy_Animate(enemy * me, int currentlyShooting, int currentlyWalking, int lastRight, int currentlyUp, int lastDown, int up, int down, int left, int right, int mouseAngle, SDL_Renderer *rend);

void enemy_Free(enemy * me);



#endif
