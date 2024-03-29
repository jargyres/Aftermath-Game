#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "player.h"
#include "background.h"


#define LEVEL_WIDTH 30000
#define LEVEL_HEIGHT 30000
#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1000
#define PLAYERWALKINGFRAMES 3
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 128
#define PLAYER_VELOCITY 300
#define BACKGROUND_SQUARE_SIZE 2000
//#define M_PI 3.14159265359
 
// #define M_PI 3.14159
//Ubuntu should already have SDL so just run this command to get the Image processing files
// "sudo apt-get install libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0"
// and then you should have everything you need
// ive been compiling with
//"gcc main.c player.c background.c -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lm -o main"
// and then I run with "./main"
// or just gcc main.c player.c background.c -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lm -o main; ./main
int SCREENHEIGHT;
int SCREENWIDTH;
int bgPositionx = 0;
int bgPositiony = 0;
int startPosX = (LEVEL_WIDTH  / 2); 
int startPosY = (LEVEL_HEIGHT / 2);
// void getOffset(int i, int j);
double getAngle(int MouseX, int MouseY);
// int validMoveMent(int playerPosX, int playerPosY, int right, int left, int up, int down);

int main() {

    SDL_Init(SDL_INIT_EVERYTHING);
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
//        printf("error %s\n", SDL_GetError());
//    }
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
    {
     SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
     return 1;
    }

    SCREENWIDTH = dm.w - (dm.w / 4);
    SCREENHEIGHT = dm.h - (dm.h / 5);

    //printf("Screenwidth = %d, screenheight = %d", SCREENWIDTH, SCREENHEIGHT);

    SDL_Window *win = SDL_CreateWindow("Game",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       SCREENWIDTH, SCREENHEIGHT,
                                       SDL_WINDOW_SHOWN);

    //create a renderer which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    //this will be the rendered we use
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);
    //create a flip option for the renderer when we want to flip our sprites
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    //this is what we will use to see keyboard events, or basically anything like that
    SDL_Event event;
    int quit = 0;

    

    player p;
    background bg;


    // player_Constructor(&p, "images/enemyWalk.png", "images/enemyWalkUp.png", 
    //                 "images/enemyShoot.png", "images/bullet.png", 
    //                 "images/enemyWalkDown.png","images/enemyShootDown.png", "images/enemyShootUp.png", "images/numbers.png", "images/ammo.png", "images/Ammo.png",
    //                 SCREENWIDTH, SCREENHEIGHT, 
    //                 rend);

    background_Constructor(&bg, "images/background.png", "images/minimap.png","images/minimapArrow.png","images/inventory.png", SCREENWIDTH, SCREENHEIGHT, rend);

    

    //Initialize some textures to nothing for now
    SDL_Texture* castusSprite = NULL;
    SDL_Texture* aftermathTex = NULL;
    SDL_Texture* titleBack1Tex = NULL;
    SDL_Texture* titleBack2Tex = NULL;
    SDL_Texture* titleBack3Tex = NULL;
    //SDL_Texture* titleBack1TexCopy = NULL;
    //SDL_Texture* titleBack2TexCopy = NULL;
    //SDL_Texture* titleBack3TexCopy = NULL;
    SDL_Texture* playOnTex = NULL;
    SDL_Texture* ExitOnTex = NULL;
    SDL_Texture* playOffTex = NULL;
    SDL_Texture* ExitOffTex = NULL;
    SDL_Texture* bulletTex = NULL;
    SDL_Texture* controlsTex = NULL;
    SDL_Texture* controlsTexBG = NULL;
    SDL_Texture* blackPixelTex = NULL;


    //load the image into memory using SDL_Image library functions

    SDL_Surface* bulletSurface = IMG_Load("images/bullet.png");
    SDL_Surface* cactusSurface = IMG_Load("images/cactus.png");
    SDL_Surface* aftermathSurface = IMG_Load("images/aftermath.png");
    SDL_Surface* titleBackSurface1 = IMG_Load("images/TitleFarBack.png");
    SDL_Surface* titleBackSurface2 = IMG_Load("images/TitleMidBack.png");
    SDL_Surface* titleBackSurface3 = IMG_Load("images/TitleCloseBack.png");
    SDL_Surface* playOnSurface = IMG_Load("images/PlayOn.png");
    SDL_Surface* exitOnSurface = IMG_Load("images/ExitOn.png");
    SDL_Surface* playOffSurface = IMG_Load("images/PlayOff.png");
    SDL_Surface* exitOffSurface = IMG_Load("images/ExitOff.png");
    SDL_Surface* controlsSurface = IMG_Load("images/newControls.png");
    SDL_Surface* controlsBGSurface = IMG_Load("images/controlsBg.png");
    SDL_Surface* blackPixelSurface = IMG_Load("images/blackPixel.png");

    // Make the textures using the renderer and the surfaces we made from the images
    bulletTex = SDL_CreateTextureFromSurface(rend, bulletSurface);
    castusSprite = SDL_CreateTextureFromSurface(rend, cactusSurface);
    aftermathTex = SDL_CreateTextureFromSurface(rend, aftermathSurface);
    titleBack1Tex = SDL_CreateTextureFromSurface(rend, titleBackSurface1);
    titleBack2Tex = SDL_CreateTextureFromSurface(rend, titleBackSurface2);
    titleBack3Tex = SDL_CreateTextureFromSurface(rend, titleBackSurface3);
    //titleBack1TexCopy = SDL_CreateTextureFromSurface(rend, titleBackSurface1);
    //titleBack2TexCopy = SDL_CreateTextureFromSurface(rend, titleBackSurface2);
    //titleBack3TexCopy = SDL_CreateTextureFromSurface(rend, titleBackSurface3);
    playOnTex = SDL_CreateTextureFromSurface(rend, playOnSurface);
    ExitOnTex = SDL_CreateTextureFromSurface(rend, exitOnSurface);
    playOffTex = SDL_CreateTextureFromSurface(rend, playOffSurface);
    ExitOffTex = SDL_CreateTextureFromSurface(rend, exitOffSurface);
    controlsTex = SDL_CreateTextureFromSurface(rend, controlsSurface);
    controlsTexBG = SDL_CreateTextureFromSurface(rend, controlsBGSurface);
    blackPixelTex = SDL_CreateTextureFromSurface(rend, blackPixelSurface);

    SDL_FreeSurface(bulletSurface);
    SDL_FreeSurface(cactusSurface);
    SDL_FreeSurface(aftermathSurface);
    SDL_FreeSurface(titleBackSurface1);
    SDL_FreeSurface(titleBackSurface2);
    SDL_FreeSurface(titleBackSurface3);
    SDL_FreeSurface(playOnSurface);
    SDL_FreeSurface(exitOnSurface);
    SDL_FreeSurface(playOffSurface);
    SDL_FreeSurface(exitOffSurface);
    SDL_FreeSurface(controlsSurface);
    SDL_FreeSurface(controlsBGSurface);
    SDL_FreeSurface(blackPixelSurface);


    //load our music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *titleMusic = NULL;
    titleMusic = Mix_LoadMUS("music/game_music.mp3");
    Mix_Music *gameMusic = NULL;
    gameMusic = Mix_LoadMUS("music/GAME_STROLL_MP3.mp3");
    // Mix_Chunk *gunshot = NULL;
    // gunshot = Mix_LoadWAV("music/BANGPOWBAP.wav");
    // if(gunshot == NULL) printf("couldnt find gunshot in main\n");

    // Mix_Music *ricePunch = NULL;
    // ricePunch = Mix_LoadMUS("music/RICE_PUNCH.wav");
    player_Constructor(&p, "images/player.png", "images/playerBack.png", 
                    "images/playerShoot.png", "images/bullet.png", 
                    "images/playerWalkDown.png","images/playerShootDown.png", "images/playerShoootUp.png", "images/numbers.png", "images/ammo.png", "images/Ammo.png",
                    "music/rice_punch.wav", "music/bangpowbap.wav",
                    SCREENWIDTH, SCREENHEIGHT, 
                    rend);

    //this is the rectangle that will actually show the images

    SDL_Rect titleBack2Rect;
    SDL_Rect titleBack3Rect;
    SDL_Rect titleBack1Rect;
    titleBack1Rect.w = 1000;
    titleBack1Rect.h = 1000;
    titleBack1Rect.x = 0;
    titleBack1Rect.y = 0;

    titleBack2Rect.w = 1000;
    titleBack2Rect.h = 1000;
    titleBack2Rect.x = 0;
    titleBack2Rect.y = 0;

    titleBack3Rect.w = 1000;
    titleBack3Rect.h = 1000;
    titleBack3Rect.x = 0;
    titleBack3Rect.y = 0;

    SDL_Rect titleBack2RectCopy;
    SDL_Rect titleBack3RectCopy;
    SDL_Rect titleBack1RectCopy;
    titleBack1RectCopy.w = 1000;
    titleBack1RectCopy.h = 1000;
    titleBack1RectCopy.x = 0;
    titleBack1RectCopy.y = 0;

    titleBack2RectCopy.w = 1000;
    titleBack2RectCopy.h = 1000;
    titleBack2RectCopy.x = 0;
    titleBack2RectCopy.y = 0;

    titleBack3RectCopy.w = 1000;
    titleBack3RectCopy.h = 1000;
    titleBack3RectCopy.x = 1000;
    titleBack3RectCopy.y = 0;

    SDL_Rect aftermathRect;
    aftermathRect.w = 1000;
    aftermathRect.h = 1000;
    aftermathRect.x = 0;
    aftermathRect.y = 0;

    SDL_Rect playOnRect;
    playOnRect.w = 1000;
    playOnRect.h = 1000;
    playOnRect.x = 0;
    playOnRect.y = 0;

    SDL_Rect ExitOnRect;
    ExitOnRect.w = 1000;
    ExitOnRect.h = 1000;
    ExitOnRect.x = 0;
    ExitOnRect.y = 0;

    SDL_Rect playOffRect;
    SDL_Rect ExitOffRect;

    SDL_Rect controlRect;
    SDL_Rect controlsBGRect;
    controlRect.w = 1000;
    controlRect.h = 1000;
    controlRect.x = (SCREENWIDTH/2) - (controlRect.w/2);
    controlRect.y = (SCREENHEIGHT/2) - (controlRect.h/2) + 30;

    controlsBGRect.x = 0;
    controlsBGRect.y = 0;
    controlsBGRect.w = 1;
    controlsBGRect.h = 1;

    SDL_Rect blackPixelRect;
    blackPixelRect.w = SCREENWIDTH;
    blackPixelRect.w = SCREENHEIGHT;
    SDL_QueryTexture(blackPixelTex, NULL, NULL, &blackPixelRect.w, &blackPixelRect.h);

    SDL_QueryTexture(controlsTex, NULL, NULL, &controlRect.w, &controlRect.h);
    SDL_QueryTexture(controlsTexBG, NULL, NULL, &controlsBGRect.w, &controlsBGRect.h);

    controlsBGRect.w *= SCREENWIDTH;
    controlsBGRect.h *= SCREENHEIGHT;

    // load the textures from the spriteSheets into their respective textureRects
    SDL_QueryTexture(titleBack1Tex, NULL, NULL, &titleBack1Rect.w, &titleBack1Rect.h);
    titleBack1Rect.w = SCREENHEIGHT * 2.96;
    titleBack1Rect.h = SCREENHEIGHT;
    SDL_QueryTexture(titleBack2Tex, NULL, NULL, &titleBack2Rect.w, &titleBack2Rect.h);
    titleBack2Rect.w = SCREENHEIGHT * 2.96;
    titleBack2Rect.h = SCREENHEIGHT;
    SDL_QueryTexture(titleBack3Tex, NULL, NULL, &titleBack3Rect.w, &titleBack3Rect.h);
    titleBack3Rect.w = SCREENHEIGHT * 2.96;
    titleBack3Rect.h = SCREENHEIGHT;

    //SDL_QueryTexture(titleBack1TexCopy, NULL, NULL, &titleBack1RectCopy.w, &titleBack1RectCopy.h);
    titleBack1RectCopy.w = SCREENHEIGHT * 2.96;
    titleBack1RectCopy.h = SCREENHEIGHT;
    //SDL_QueryTexture(titleBack2TexCopy, NULL, NULL, &titleBack2RectCopy.w, &titleBack2RectCopy.h);
    titleBack2RectCopy.w = SCREENHEIGHT * 2.96;
    titleBack2RectCopy.h = SCREENHEIGHT;
    //SDL_QueryTexture(titleBack3TexCopy, NULL, NULL, &titleBack3RectCopy.w, &titleBack3RectCopy.h);
    titleBack3RectCopy.w = SCREENHEIGHT * 2.96;
    titleBack3RectCopy.h = SCREENHEIGHT;
    
    SDL_QueryTexture(playOnTex, NULL, NULL, &playOnRect.w, &playOnRect.h);
    playOnRect.w = 60 * 4;
    playOnRect.h = 40 * 4;
    playOnRect.x = (WINDOW_WIDTH / 2) - 140;
    playOnRect.y = (WINDOW_HEIGHT / 2) - 40;
    SDL_QueryTexture(ExitOnTex, NULL, NULL, &ExitOnRect.w, &ExitOnRect.h);
    ExitOnRect.w = 60 * 4;
    ExitOnRect.h = 40 * 4;
    ExitOnRect.x = (WINDOW_WIDTH / 2) - 140;
    ExitOnRect.y = (WINDOW_HEIGHT / 2) + 60;
    SDL_QueryTexture(playOffTex, NULL, NULL, &playOffRect.w, &playOffRect.h);
    playOffRect.w = 60 * 4;
    playOffRect.h = 40 * 4;
    playOffRect.x = (WINDOW_WIDTH / 2) - 140;
    playOffRect.y = (WINDOW_HEIGHT / 2)- 40;
    SDL_QueryTexture(ExitOffTex, NULL, NULL, &ExitOffRect.w, &ExitOffRect.h);
    ExitOffRect.w = 60 * 4;
    ExitOffRect.h = 40 * 4;
    ExitOffRect.x = (WINDOW_WIDTH / 2) - 140;
    ExitOffRect.y = (WINDOW_HEIGHT / 2) + 60;
    SDL_QueryTexture(aftermathTex, NULL, NULL, &aftermathRect.w, &aftermathRect.h);
    aftermathRect.w = 200 * 4;
    aftermathRect.h = 60 * 4;
    aftermathRect.x = (WINDOW_WIDTH / 2) - 420;
    aftermathRect.y = (WINDOW_HEIGHT / 2) - 400;


    //just values 0 or 1 telling us which direction were going
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    //keep as a float as we will be dividing by 60 (because were locking at 60 fps)
    float x_vel = 0.0;
    float y_vel = 0.0;
    int currentlyWalking = 0;
    //use this one as when we stand still we want to see if we were last walking right
    //to face in the right direction when standing
    int lastRight = 0;
    //same thing here
    int currentlyUp = 0;
    //also same thing here
    int currentlyShooting = 0;
    
    int lastDown = 0;

    

    
    int backgroundOffsetX = 0;
    int backgroundOffsetY = 0;

    int titleScreen = 1;
    int play = 0;
    int bulletsOnScreen = 0;
    int playerPosX = startPosX;
    int playerPosY = startPosX;
    int miniMapShowing = 0;
    int inventoryShowing = 0;
    int controlsShowing = 0;
    background_SetPlayerPos(&bg, playerPosX, playerPosY);
    double angle = 0.0;
    int titleStop = 0;
    if(titleScreen && !play)
    {
        int playHoveredOver = 0;
        int quitHoveredOver = 0;
        int mouse_x;
        int mouse_y;
        int frame = 0;
        int keepPlayingTitleMusic = 1;
        Mix_PlayMusic(titleMusic, -1);
        while(!quit && !play)
        {
            Uint64 start = SDL_GetPerformanceCounter();
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                        quit = 1;
                        titleScreen = 0;
                        break;
                    case SDL_MOUSEMOTION:
                        SDL_GetMouseState(&mouse_x, &mouse_y);
                        // printf("mousex = %d mouse y = %d", mouse_x, mouse_y);
                        // printf("Mouse x = %d mouse y = %d", mouse_x, mouse_y);
                        // x:(610, 850) y:(500, 564)
                        if(mouse_x >= 610 && mouse_x <= 850 && mouse_y <= 564  && mouse_y >= 500)
                        {
                            playHoveredOver = 1;
                            quitHoveredOver = 0;
                        }
                        // x:(610, 850) y:(594, 655)
                        else if(mouse_x >= 610 && mouse_x <= 850 && mouse_y <= 655 && mouse_y >= 568)
                        {
                            quitHoveredOver = 1;
                            playHoveredOver = 0;
                        }
                        else
                        {
                            playHoveredOver = 0;
                            quitHoveredOver = 0;
                        }

                        break;
                    case SDL_MOUSEBUTTONUP:
                        if(playHoveredOver) play = 1;
                        if(quitHoveredOver) quit = 1;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.scancode)
                        {
                            case SDL_SCANCODE_TAB:
                                if(controlsShowing) controlsShowing = 0;
                                else controlsShowing = 1;
                                break;
                            case SDL_SCANCODE_ESCAPE:
                                quit = 1;
                                break;
                        }
                        break;
                    
                }
            }

            // SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
            SDL_RenderClear(rend);
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

            if(!controlsShowing)
            {
                SDL_RenderCopy(rend, titleBack1Tex, NULL, &titleBack1Rect);
                SDL_RenderCopy(rend, titleBack2Tex, NULL, &titleBack2Rect);
                SDL_RenderCopy(rend, titleBack3Tex, NULL, &titleBack3Rect);
                //SDL_RenderCopy(rend, titleBack1TexCopy, NULL, &titleBack1RectCopy);
                //SDL_RenderCopy(rend, titleBack2TexCopy, NULL, &titleBack2RectCopy);
                //SDL_RenderCopy(rend, titleBack3TexCopy, NULL, &titleBack3RectCopy);
                SDL_RenderCopy(rend, playOffTex, NULL, &playOffRect);
                SDL_RenderCopy(rend, ExitOffTex, NULL, &ExitOffRect);
                SDL_RenderCopy(rend, aftermathTex, NULL, &aftermathRect);

                if(play) titleScreen = 0;

                if(playHoveredOver || quitHoveredOver)
                {
                    int delayPerFrame = 300;
                    frame = (SDL_GetTicks() / delayPerFrame) % 2;
                    if(playHoveredOver && frame == 1)
                    {
                        SDL_RenderCopy(rend, playOnTex, NULL, &playOnRect);
                        SDL_RenderCopy(rend, ExitOffTex, NULL, &ExitOffRect);
                    }
                     else if(quitHoveredOver && frame == 1)
                    {
                        SDL_RenderCopy(rend, ExitOnTex, NULL, &ExitOnRect);
                        SDL_RenderCopy(rend, playOffTex, NULL, &playOffRect);
                    }
                }

                //titleBack1Rect.x -= 1;
                //titleBack2Rect.x -= 2;
                //titleBack3Rect.x -= 3;
                titleBack1RectCopy.x -= 1;
                titleBack2RectCopy.x -= 2;
                titleBack3RectCopy.x -= 8;
                //printf("%d\n", titleBack3Rect.x);
                if(titleBack3Rect.x > -1100){
                    titleBack3Rect.x -= 3;
                    titleBack2Rect.x -= 2;
                    titleBack1Rect.x -= 1;
                }

            } 
            else
            {
                SDL_RenderCopy(rend, controlsTexBG, NULL, &controlsBGRect);
                SDL_RenderCopy(rend, controlsTex, NULL, &controlRect);

            }
            

            SDL_RenderPresent(rend);
            Uint64 end = SDL_GetPerformanceCounter();
            float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
            SDL_Delay(floor(16.666f - elapsedMS));

        }
    }
    if(!titleScreen && play){
        // Mix_HaltMusic();
        int mouse_x;
        int mouse_y;
        Mix_PlayMusic(gameMusic, -1);
        int texalpha = 510;
        while(!quit)
        {
            Uint64 start = SDL_GetPerformanceCounter();

            while (SDL_PollEvent(&event)) {
                switch (event.type)
                {
                    case SDL_QUIT:
                        quit = 1;
                        break;
                    case SDL_KEYDOWN:
                        currentlyWalking = 1;
                        switch (event.key.keysym.scancode)
                        {
                            case SDL_SCANCODE_W:
                            case SDL_SCANCODE_UP:
                                currentlyUp = 1;
                                lastDown = 0;
                                lastRight = 0;
                                up = 1;
                                break;
                            case SDL_SCANCODE_A:
                            case SDL_SCANCODE_LEFT:
                                currentlyUp = 0;
                                lastRight = 0;
                                lastDown = 0;
                                left = 1;
                                break;
                            case SDL_SCANCODE_S:
                            case SDL_SCANCODE_DOWN:
                                currentlyUp = 0;
                                lastDown = 1;
                                lastRight = 0;
                                down = 1;
                                break;
                            case SDL_SCANCODE_D:
                            case SDL_SCANCODE_RIGHT:
                                currentlyUp = 0;
                                lastRight = 1;
                                lastDown = 0;
                                right = 1;
                                break;
                            case SDL_SCANCODE_SPACE:
                                currentlyShooting = 1;
                                break;
                            case SDL_SCANCODE_E:
                                if(miniMapShowing) miniMapShowing = 0;
                                else if(!miniMapShowing) miniMapShowing = 1;
                                inventoryShowing = 0;
                                break;
                            case SDL_SCANCODE_R:
                                if(inventoryShowing) inventoryShowing = 0;
                                else if(!inventoryShowing) inventoryShowing = 1;
                                miniMapShowing = 0;
                                break;
                            case SDL_SCANCODE_ESCAPE:
                                quit = 1;
                                break;
                        }
                        break;
                    case SDL_KEYUP:
                        currentlyWalking = 0;
                        switch (event.key.keysym.scancode)
                        {
                            case SDL_SCANCODE_W:
                            case SDL_SCANCODE_UP:
                                up = 0;
                                lastDown = 0;
                                lastRight = 0;
                                currentlyUp = 1;
                                break;
                            case SDL_SCANCODE_A:
                            case SDL_SCANCODE_LEFT:
                                left = 0;
                                lastRight = 0;
                                lastDown = 0;
                                break;
                            case SDL_SCANCODE_S:
                            case SDL_SCANCODE_DOWN:
                                down = 0;
                                lastDown = 1;
                                lastRight = 0;
                                break;
                            case SDL_SCANCODE_D:
                            case SDL_SCANCODE_RIGHT:
                                right = 0;
                                lastRight = 1;
                                lastDown = 0;
                                break;
                            case SDL_SCANCODE_SPACE:
                                currentlyShooting = 0;
                                break;
                        }
                        break;
                    case SDL_MOUSEMOTION:
                        SDL_GetMouseState(&mouse_x, &mouse_y);
                        angle = getAngle(mouse_x, mouse_y);
                        // printf("angle = %f", angle);
                        break;

                }
            }

            x_vel = y_vel = 0;
            //these should be between 200 or 300 to look good but
            //I want to be fast when testing
            if(up && !down) y_vel = PLAYER_VELOCITY;
            if(down && !up) y_vel = -1 * PLAYER_VELOCITY;
            if(left && !right) x_vel = PLAYER_VELOCITY;
            if(right && !left) x_vel = -1 * PLAYER_VELOCITY;
            if(!up && !down && !left && !right)
            {
                currentlyWalking = 0;
                x_vel = 0;
                y_vel = 0;
            }

            background_Move(&bg, currentlyWalking, right, left, up, down, SCREENWIDTH, SCREENHEIGHT);


            // //basically set up the values of RGB we will use
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

            SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
            //clear the renderer so we dont just get garbage on our screen
            SDL_RenderClear(rend);

            background_Draw(&bg, miniMapShowing, inventoryShowing,lastRight, lastDown, currentlyUp,rend);

            player_Animate(&p, currentlyShooting, currentlyWalking, lastRight, currentlyUp, lastDown, up, down, left, right,
                            angle, rend);

            SDL_SetTextureAlphaMod(blackPixelTex, texalpha/2);
            SDL_SetTextureBlendMode(blackPixelTex, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(rend, blackPixelTex, NULL, &controlsBGRect);
            if(texalpha > 0) texalpha--; 

            // finally push the renderer to the hardware, making the sprites appear on the screen
            SDL_RenderPresent(rend);

            // we calculate the elapsed time it took for the above code to run
            // doing this will give us 60 fps no matter how long it takes the above code to run
            Uint64 end = SDL_GetPerformanceCounter();
            float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
            SDL_Delay(floor(16.666f - elapsedMS));

            

        }
    }

    //clean up our resources before we exit
    player_Free(&p);
    background_Free(&bg);
    SDL_DestroyTexture(bulletTex);
    SDL_DestroyTexture(castusSprite);
    SDL_DestroyTexture(titleBack1Tex);
    SDL_DestroyTexture(titleBack2Tex);
    SDL_DestroyTexture(titleBack3Tex);
    SDL_DestroyTexture(playOnTex);
    SDL_DestroyTexture(ExitOffTex);
    SDL_DestroyTexture(playOffTex);
    SDL_DestroyTexture(ExitOnTex);
    SDL_DestroyTexture(controlsTex);
    SDL_DestroyTexture(controlsTexBG);
    SDL_DestroyTexture(blackPixelTex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    Mix_FreeMusic(titleMusic);
    Mix_FreeMusic(gameMusic);
    Mix_CloseAudio();
    SDL_Quit();
    printf("exited successfully\n");
    return 0;
}



double getAngle(int MouseX, int MouseY)
{
    int multiplierX;
    int multiplierY;

    double deltaX = MouseX - ((SCREENWIDTH - PLAYER_WIDTH)/2);
    double deltaY = MouseY - ((SCREENHEIGHT - PLAYER_HEIGHT)/2);
    

    double angleBetweenPoints = SDL_atan2(deltaY, deltaX) * 180 / 3.14159;

    return angleBetweenPoints;


}


