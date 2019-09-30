#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define LEVEL_WIDTH 2000
#define LEVEL_HEIGHT 2000
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define PLAYERWALKINGFRAMES 3

//Ubuntu should already have SDL so just run this command to get the Image processing files

// "sudo apt-get install libsdl2-image-2.0-0 libsdl2-image-dev"
// and then you should have everything you need
// ive been compiling with
// "gcc main.c -lSDL2 -lSDL2main -lSDL2_image -lm -o main"
// and then I run with "./main"

int main() {

    SDL_Init(SDL_INIT_EVERYTHING);l
    
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
//        printf("error %s\n", SDL_GetError());
//    }
    SDL_Window *win = SDL_CreateWindow("Game",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,
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

    //Initialize some textures to nothing for now
    SDL_Texture* spriteSheet = NULL;
    SDL_Texture* spriteSheet2 = NULL;
    SDL_Texture* castusSprite = NULL;
    SDL_Texture* backgroundTexture = NULL;
    SDL_Texture* title1Tex = NULL;
    SDL_Texture* title2Tex = NULL;
    SDL_Texture* title3Tex = NULL;
    SDL_Texture* playerShootTex = NULL;
    SDL_Texture* bulletTex = NULL;

    //hello

    //load the image into memory using SDL_Image library functions
    SDL_Surface* surface = IMG_Load("images/player.png");
    SDL_Surface* surface2 = IMG_Load("images/playerBack.png");
    SDL_Surface* playerShootSurface = IMG_Load("images/playerShoot.png");
    SDL_Surface* bulletSurface = IMG_Load("images/bullet.png");
    SDL_Surface* cactusSurface = IMG_Load("images/cactus.png");
    SDL_Surface* backgroundSurface = IMG_Load("images/background.png");
    SDL_Surface* titleSurface1 = IMG_Load("images/titlescreen1.png");
    SDL_Surface* titleSurface2 = IMG_Load("images/titlescreen2.png");
    SDL_Surface* titleSurface3 = IMG_Load("images/titlescreen3.png");

    // Make the textures using the renderer and the surfaces we made from the images
    spriteSheet = SDL_CreateTextureFromSurface(rend, surface);
    spriteSheet2 = SDL_CreateTextureFromSurface(rend, surface2);
    playerShootTex = SDL_CreateTextureFromSurface(rend, playerShootSurface);
    bulletTex = SDL_CreateTextureFromSurface(rend, bulletSurface);
    castusSprite = SDL_CreateTextureFromSurface(rend, cactusSurface);
    backgroundTexture = SDL_CreateTextureFromSurface(rend, backgroundSurface);
    title1Tex = SDL_CreateTextureFromSurface(rend, titleSurface1);
    title2Tex = SDL_CreateTextureFromSurface(rend, titleSurface2);
    title3Tex = SDL_CreateTextureFromSurface(rend, titleSurface3);

    //free the images up from memory as they're in the textures now
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);
    SDL_FreeSurface(playerShootSurface);
    SDL_FreeSurface(bulletSurface);
    SDL_FreeSurface(cactusSurface);
    SDL_FreeSurface(backgroundSurface);
    SDL_FreeSurface(titleSurface1);
    SDL_FreeSurface(titleSurface2);
    SDL_FreeSurface(titleSurface3);

    //this is the rectangle that will actually show the images

    SDL_Rect title1Rect;
    title1Rect.w = 1000;
    title1Rect.h = 1000;
    title1Rect.x = 0;
    title1Rect.y = 0;

    SDL_Rect title2Rect;
    title2Rect.w = 1000;
    title2Rect.h = 1000;
    title2Rect.x = 0;
    title2Rect.y = 0;

    SDL_Rect title3Rect;
    title3Rect.w = 1000;
    title3Rect.h = 1000;
    title3Rect.x = 0;
    title3Rect.y = 0;

    SDL_Rect playerShootRectWin;
    playerShootRectWin.w = 128;
    playerShootRectWin.h = 128;
    playerShootRectWin.x = (WINDOW_WIDTH - playerShootRectWin.w) /2;
    playerShootRectWin.y = (WINDOW_HEIGHT - playerShootRectWin.h) /2;

    SDL_Rect playerShootRectTex;
    playerShootRectTex.x = 0;
    playerShootRectTex.y = 0;
    playerShootRectTex.w = 128;
    playerShootRectTex.h = 64;
//
//    //lets give ourselves 10 bullets at a time
//    // also this is super ugly and im sure there's a better way to do this
//    SDL_Rect bulletRectTex;
//    bulletRectTex.x = 0;
//    bulletRectTex.y = 0;
//    bulletRectTex.w = 64;
//    bulletRectTex.h = 64;
//    SDL_Rect bulletRectTex1;
//    bulletRectTex1.x = 0;
//    bulletRectTex1.y = 0;
//    bulletRectTex1.w = 64;
//    bulletRectTex1.h = 64;
//    SDL_Rect bulletRectTex2;
//    bulletRectTex2.x = 0;
//    bulletRectTex2.y = 0;
//    bulletRectTex2.w = 64;
//    bulletRectTex2.h = 64;
//    SDL_Rect bulletRectTex3;
//    bulletRectTex3.x = 0;
//    bulletRectTex3.y = 0;
//    bulletRectTex3.w = 64;
//    bulletRectTex3.h = 64;
//    SDL_Rect bulletRectTex4;
//    bulletRectTex4.x = 0;
//    bulletRectTex4.y = 0;
//    bulletRectTex4.w = 64;
//    bulletRectTex4.h = 64;
//    SDL_Rect bulletRectTex5;
//    bulletRectTex5.x = 0;
//    bulletRectTex5.y = 0;
//    bulletRectTex5.w = 64;
//    bulletRectTex5.h = 64;
//    SDL_Rect bulletRectTex6;
//    bulletRectTex6.x = 0;
//    bulletRectTex6.y = 0;
//    bulletRectTex6.w = 64;
//    bulletRectTex6.h = 64;
//    SDL_Rect bulletRectTex7;
//    bulletRectTex7.x = 0;
//    bulletRectTex7.y = 0;
//    bulletRectTex7.w = 64;
//    bulletRectTex7.h = 64;
//    SDL_Rect bulletRectTex8;
//    bulletRectTex8.x = 0;
//    bulletRectTex8.y = 0;
//    bulletRectTex8.w = 64;
//    bulletRectTex8.h = 64;
//    SDL_Rect bulletRectTex9;
//    bulletRectTex9.x = 0;
//    bulletRectTex9.y = 0;
//    bulletRectTex9.w = 64;
//    bulletRectTex9.h = 64;
//
//    //make an array of the pointers of our bullet rects to make it
//    //easier to call them when drawing the bullets;
//    SDL_Rect *bulletArr[10];
//    bulletArr[0] = &bulletRectTex;
//    bulletArr[1] = &bulletRectTex1;
//    bulletArr[2] = &bulletRectTex2;
//    bulletArr[3] = &bulletRectTex3;
//    bulletArr[4] = &bulletRectTex4;
//    bulletArr[5] = &bulletRectTex5;
//    bulletArr[6] = &bulletRectTex6;
//    bulletArr[7] = &bulletRectTex7;
//    bulletArr[8] = &bulletRectTex8;
//    bulletArr[9] = &bulletRectTex9;
//
//    //this array will "hold" the values for the corresponding bullet's direction so we dont flip bullets
//    // a 0 will denote the bullet at the same index is moving to the right
//    // 1 will be moving to the left
//    int bulletLeftRight[10] = {0,0,0,0,0,0,0,0,0,0};



    SDL_Rect windowRect;
    windowRect.w = 128;
    windowRect.h = 128;
    windowRect.x = (WINDOW_WIDTH - windowRect.w) / 2;
    windowRect.y = (WINDOW_HEIGHT - windowRect.h) / 2;


    SDL_Rect windowRect2;
    windowRect2.w = 128;
    windowRect2.h = 128;
    windowRect2.x = windowRect.x;
    windowRect2.y = windowRect.y;




    //lets give ourselves 10 bullets at a time
    // also this is super ugly and im sure there's a better way to do this
//    SDL_Rect bulletRectTex;
//    bulletRectTex.x = 0;
//    bulletRectTex.y = windowRect.y;
//    bulletRectTex.w = 64;
//    bulletRectTex.h = 64;
//    SDL_Rect bulletRectTex1;
//    bulletRectTex1.x = 0;
//    bulletRectTex1.y = windowRect.y;
//    bulletRectTex1.w = 64;
//    bulletRectTex1.h = 64;
//    SDL_Rect bulletRectTex2;
//    bulletRectTex2.x = 0;
//    bulletRectTex2.y = windowRect.y;
//    bulletRectTex2.w = 64;
//    bulletRectTex2.h = 64;
//    SDL_Rect bulletRectTex3;
//    bulletRectTex3.x = 0;
//    bulletRectTex3.y = windowRect.y;
//    bulletRectTex3.w = 64;
//    bulletRectTex3.h = 64;
//    SDL_Rect bulletRectTex4;
//    bulletRectTex4.x = 0;
//    bulletRectTex4.y = windowRect.y;
//    bulletRectTex4.w = 64;
//    bulletRectTex4.h = 64;
//    SDL_Rect bulletRectTex5;
//    bulletRectTex5.x = 0;
//    bulletRectTex5.y = windowRect.y;
//    bulletRectTex5.w = 64;
//    bulletRectTex5.h = 64;
//    SDL_Rect bulletRectTex6;
//    bulletRectTex6.x = 0;
//    bulletRectTex6.y = windowRect.y;
//    bulletRectTex6.w = 64;
//    bulletRectTex6.h = 64;
//    SDL_Rect bulletRectTex7;
//    bulletRectTex7.x = 0;
//    bulletRectTex7.y = windowRect.y;
//    bulletRectTex7.w = 64;
//    bulletRectTex7.h = 64;
//    SDL_Rect bulletRectTex8;
//    bulletRectTex8.x = 0;
//    bulletRectTex8.y = windowRect.y;
//    bulletRectTex8.w = 64;
//    bulletRectTex8.h = 64;
//    SDL_Rect bulletRectTex9;
//    bulletRectTex9.x = 0;
//    bulletRectTex9.y = windowRect.y;
//    bulletRectTex9.w = 64;
//    bulletRectTex9.h = 64;
//
//    //make an array of the pointers of our bullet rects to make it
//    //easier to call them when drawing the bullets;
//    SDL_Rect *bulletArr[10];
//    bulletArr[0] = &bulletRectTex;
//    bulletArr[1] = &bulletRectTex1;
//    bulletArr[2] = &bulletRectTex2;
//    bulletArr[3] = &bulletRectTex3;
//    bulletArr[4] = &bulletRectTex4;
//    bulletArr[5] = &bulletRectTex5;
//    bulletArr[6] = &bulletRectTex6;
//    bulletArr[7] = &bulletRectTex7;
//    bulletArr[8] = &bulletRectTex8;
//    bulletArr[9] = &bulletRectTex9;
//
//    //this array will "hold" the values for the corresponding bullet's direction so we dont flip bullets
//    // a 0 will denote the bullet at the same index is moving to the right
//    // 1 will be moving to the left
//    int bulletLeftRight[10] = {0,0,0,0,0,0,0,0,0,0};

    //We want 9 backgrounds in total
    // (x,y) as the top left of the rect
    // backgroundRect1(-1000, -1000)      backgroundRect2(0,-1000)         backgroundRect3(1000,-1000)

    // backgroundRect4(-1000,0)           backgroundRect(0,0)              backgroundRect5(1000,0)

    // backgroundRect6 (-1000,1000)       backgroundRect7(0,1000)          backgroundRect8(1000,1000)
    SDL_Rect backgroundRect;
    backgroundRect.w = 1000;
    backgroundRect.h = 1000;
    backgroundRect.x = 0;
    backgroundRect.y = 0;

    SDL_Rect backgroundRect1;
    backgroundRect1.w = 1000;
    backgroundRect1.h = 1000;
    backgroundRect1.x = backgroundRect.x - 1000;
    backgroundRect1.y = backgroundRect.y - 1000;

    SDL_Rect backgroundRect2;
    backgroundRect2.w = 1000;
    backgroundRect2.h = 1000;
    backgroundRect2.x = backgroundRect.x;
    backgroundRect2.y = backgroundRect.y - 1000;

    SDL_Rect backgroundRect3;
    backgroundRect3.w = 1000;
    backgroundRect3.h = 1000;
    backgroundRect3.x = backgroundRect.x + 1000;
    backgroundRect3.y = backgroundRect.y - 1000;

    SDL_Rect backgroundRect4;
    backgroundRect4.w = 1000;
    backgroundRect4.h = 1000;
    backgroundRect4.x = backgroundRect.x - 1000;
    backgroundRect4.y = backgroundRect.y;

    SDL_Rect backgroundRect5;
    backgroundRect5.w = 1000;
    backgroundRect5.h = 1000;
    backgroundRect5.x = backgroundRect.x + 1000;
    backgroundRect5.y = backgroundRect.y;

    SDL_Rect backgroundRect6;
    backgroundRect6.w = 1000;
    backgroundRect6.h = 1000;
    backgroundRect6.x = backgroundRect.x - 1000;
    backgroundRect6.y = backgroundRect.y + 1000;

    SDL_Rect backgroundRect7;
    backgroundRect7.w = 1000;
    backgroundRect7.h = 1000;
    backgroundRect7.x = backgroundRect.x;
    backgroundRect7.y = backgroundRect.y + 1000;

    SDL_Rect backgroundRect8;
    backgroundRect8.w = 1000;
    backgroundRect8.h = 1000;
    backgroundRect8.x = backgroundRect.x + 1000;
    backgroundRect8.y = backgroundRect.y + 1000;

    //this is a rectangle to hold our whole image file,
    // giving us the ability to choose coordinates so we get the right sprite
    SDL_Rect textureRect;
    textureRect.x = 0;
    textureRect.y = 0;
    textureRect.w = 192;
    textureRect.h = 64;

    SDL_Rect textureRect2;
    textureRect2.x = 0;
    textureRect2.y = 0;
    textureRect2.w = 192;
    textureRect2.h = 64;



    // load the textures from the spriteSheets into their respective textureRects
    SDL_QueryTexture(title1Tex, NULL, NULL, &title1Rect.w, &title1Rect.h);
    SDL_QueryTexture(title2Tex, NULL, NULL, &title2Rect.w, &title2Rect.h);
    SDL_QueryTexture(title3Tex, NULL, NULL, &title3Rect.w, &title3Rect.h);
    SDL_QueryTexture(spriteSheet, NULL, NULL, &textureRect.w, &textureRect.h);
    SDL_QueryTexture(spriteSheet2, NULL, NULL, &textureRect2.w, &textureRect2.h);
    SDL_QueryTexture(playerShootTex, NULL, NULL, &playerShootRectTex.w, &playerShootRectTex.h);
//    SDL_QueryTexture(bulletTex, NULL, NULL, &bulletRectTex1.w, &bulletRectTex1.h);
//    SDL_QueryTexture(bulletTex, NULL, NULL, &bulletRectTex2.w, &bulletRectTex2.h);
//    SDL_QueryTexture(bulletTex, NULL, NULL, &bulletRectTex3.w, &bulletRectTex3.h);
//    SDL_QueryTexture(bulletTex, NULL, NULL, &bulletRectTex4.w, &bulletRectTex4.h);
//    SDL_QueryTexture(bulletTex, NULL, NULL, &bulletRectTex5.w, &bulletRectTex5.h);
//    SDL_QueryTexture(bulletTex, NULL, NULL, &bulletRectTex6.w, &bulletRectTex6.h);
//    SDL_QueryTexture(bulletTex, NULL, NULL, &bulletRectTex7.w, &bulletRectTex7.h);
//    SDL_QueryTexture(bulletTex, NULL, NULL, &bulletRectTex8.w, &bulletRectTex8.h);
//    SDL_QueryTexture(bulletTex, NULL, NULL, &bulletRectTex9.w, &bulletRectTex9.h);
//    SDL_QueryTexture(bulletTex, NULL, NULL, &bulletRectTex.w, &bulletRectTex.h);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect.w, &backgroundRect.h);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect1.w, &backgroundRect1.h);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect2.w, &backgroundRect2.h);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect3.w, &backgroundRect3.h);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect4.w, &backgroundRect4.h);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect5.w, &backgroundRect5.h);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect6.w, &backgroundRect6.h);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect7.w, &backgroundRect7.h);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundRect8.w, &backgroundRect8.h);

    // make the widths 64 pixels
    textureRect.w /= PLAYERWALKINGFRAMES;
    textureRect2.w /= PLAYERWALKINGFRAMES;
    playerShootRectTex.w /= 2;


    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    float x_vel = 0.0;
    float y_vel = 0.0;
    int bullet_vel_x = 1;
    int currentlyWalking = 0;
    int lastRight = 0;
    int currentlyUp = 0;
    int currentlyShooting = 0;

    float backgroundPosX = 0.0;
    float backgroundPosY = 0.0;

    int titleScreen = 1;
    int play = 0;
    int bulletsOnScreen = 0;

    if(titleScreen && !play)
    {
        int playHoveredOver = 0;
        int quitHoveredOver = 0;
        int mouse_x;
        int mouse_y;
        int frame = 0;
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
                        if(mouse_x >= 400 && mouse_x <= 540 && mouse_y <= 600 && mouse_y >= 540)
                        {
                            playHoveredOver = 1;
                            quitHoveredOver = 0;
                        }
                        else if(mouse_x >= 400 && mouse_x <= 540 && mouse_y <= 690 && mouse_y >= 630)
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
                }
            }

            SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, title1Tex, NULL, &title1Rect);

            if(play) titleScreen = 0;

            if(playHoveredOver || quitHoveredOver)
            {
                int delayPerFrame = 300;
                frame = (SDL_GetTicks() / delayPerFrame) % 2;
                if(playHoveredOver && frame == 1)
                {
                    SDL_RenderCopy(rend, title2Tex, NULL, &title2Rect);
                }
                else if(quitHoveredOver && frame == 1)
                {
                    SDL_RenderCopy(rend, title3Tex, NULL, &title3Rect);
                }
                else
                {
                    SDL_RenderCopy(rend, title1Tex, NULL, &title1Rect);
                }

            }
            else
            {
                SDL_RenderCopy(rend, title1Tex, NULL, &title1Rect);

            }



            SDL_RenderPresent(rend);
            Uint64 end = SDL_GetPerformanceCounter();
            float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
            SDL_Delay(floor(16.666f - elapsedMS));

        }
    }
    if(!titleScreen && play){
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
                                up = 1;
                                break;
                            case SDL_SCANCODE_A:
                            case SDL_SCANCODE_LEFT:
                                currentlyUp = 0;
                                lastRight = 0;
                                left = 1;
                                break;
                            case SDL_SCANCODE_S:
                            case SDL_SCANCODE_DOWN:
                                currentlyUp = 0;
                                down = 1;
                                break;
                            case SDL_SCANCODE_D:
                            case SDL_SCANCODE_RIGHT:
                                currentlyUp = 0;
                                lastRight = 1;
                                right = 1;
                                break;
                            case SDL_SCANCODE_SPACE:
                                currentlyShooting = 1;
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
                                break;
                            case SDL_SCANCODE_A:
                            case SDL_SCANCODE_LEFT:
                                left = 0;
                                break;
                            case SDL_SCANCODE_S:
                            case SDL_SCANCODE_DOWN:
                                down = 0;
                                break;
                            case SDL_SCANCODE_D:
                            case SDL_SCANCODE_RIGHT:
                                right = 0;
                                break;
                            case SDL_SCANCODE_SPACE:
                                currentlyShooting = 0;
                                break;
                        }
                        break;
                }
            }

            x_vel = y_vel = 0;

            if(up && !down) y_vel = 300;
            if(down && !up) y_vel = -300;
            if(left && !right) x_vel = 300;
            if(right && !left) x_vel = -300;
            if(!up && !down && !left && !right) currentlyWalking = 0;


            if(backgroundPosX >= 1000) backgroundPosX = 0;
            if(backgroundPosX <= -1000) backgroundPosX = 0;
            if(backgroundPosY >= 1000) backgroundPosY = 0;
            if(backgroundPosY <= -1000) backgroundPosY = 0;


            if(currentlyWalking)
            {

                backgroundPosX += x_vel / 60;
                backgroundPosY += y_vel / 60;

                backgroundRect.x = (int) backgroundPosX;
                backgroundRect.y = (int) backgroundPosY;

                backgroundRect1.x = backgroundRect.x - 1000;
                backgroundRect1.y = backgroundRect.y - 1000;

                backgroundRect2.x = backgroundRect.x;
                backgroundRect2.y = backgroundRect.y - 1000;

                backgroundRect3.x = backgroundRect.x + 1000;
                backgroundRect3.y = backgroundRect.y - 1000;

                backgroundRect4.x = backgroundRect.x - 1000;
                backgroundRect4.y = backgroundRect.y;

                backgroundRect5.x = backgroundRect.x + 1000;
                backgroundRect5.y = backgroundRect.y;

                backgroundRect6.x = backgroundRect.x - 1000;
                backgroundRect6.y = backgroundRect.y + 1000;

                backgroundRect7.x = backgroundRect.x;
                backgroundRect7.y = backgroundRect.y + 1000;

                backgroundRect8.x = backgroundRect.x + 1000;
                backgroundRect8.y = backgroundRect.y + 1000;


            }



            if(currentlyWalking){
                int frames = PLAYERWALKINGFRAMES;

                int delayPerFrame = 200;

                int frame = (SDL_GetTicks() / delayPerFrame) % frames;


                textureRect.x = frame * textureRect.w;
                textureRect2.x = frame * textureRect2.w;


            }
            else if(currentlyShooting)
            {
                int ticks = SDL_GetTicks() / 150;
                int shootFrame = (ticks) % 2;
                playerShootRectTex.x = shootFrame * playerShootRectTex.w;
//                if(bulletsOnScreen >= 10) bulletsOnScreen = 0;
//                if(ticks % 2 == 0 || ticks % 2 == 1) ++bulletsOnScreen;
//                for(int i = 0; i < bulletsOnScreen; i++)
//                {
//                    if(lastRight)
//                    {
//                        bulletLeftRight[i] = 0;
//                    } else
//                    {
//                        bulletLeftRight[i] = 1;
//                    }
//
//                }



            }
            else
            {
                //if we arent walking just show the first sprite so it looks like were standing still
                textureRect.x = 0;
                textureRect2.x = 0;
//                int shootFrame = (SDL_GetTicks() / 150) % 2;
//                playerShootRectTex.x = shootFrame * playerShootRectTex.w;



            }

//            for(int j = 0; j < bulletsOnScreen; j++)
//            {
//                if(bulletLeftRight[j])
//                {
//                    bullet_vel_x = -1;
//
//
//                }
//                if(!bulletLeftRight[j])
//                {
//                    bullet_vel_x = 1;
//                }
//                (*bulletArr[j]).x += bullet_vel_x;
//
//            }
//
//            //look at all the x values of our bullets
//            for(int i = 0; i < 10; i++)
//            {
//                if((*bulletArr[i]).x <= -2000 || (*bulletArr[i]).x <= -2000)
//                {
//                    bulletsOnScreen--;
//                }
//            }



            //basically set up the values of RGB we will use
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
            //clear the renderer so we dont just get garbage on our screen
            SDL_RenderClear(rend);


            SDL_RenderCopy(rend, backgroundTexture, NULL, &backgroundRect);
            SDL_RenderCopy(rend, backgroundTexture, NULL, &backgroundRect1);
            SDL_RenderCopy(rend, backgroundTexture, NULL, &backgroundRect2);
            SDL_RenderCopy(rend, backgroundTexture, NULL, &backgroundRect3);
            SDL_RenderCopy(rend, backgroundTexture, NULL, &backgroundRect4);
            SDL_RenderCopy(rend, backgroundTexture, NULL, &backgroundRect5);
            SDL_RenderCopy(rend, backgroundTexture, NULL, &backgroundRect6);
            SDL_RenderCopy(rend, backgroundTexture, NULL, &backgroundRect7);
            SDL_RenderCopy(rend, backgroundTexture, NULL, &backgroundRect8);

            if(lastRight && !currentlyUp && !currentlyShooting)
            {
                //this'll draw the right left images
                SDL_RenderCopyEx(rend, spriteSheet, &textureRect, &windowRect, 0.0, NULL, flip);
            }
            else if(currentlyUp)
            {
                //this'll draw the walking up sprites
                SDL_RenderCopy(rend, spriteSheet2, &textureRect2, &windowRect2);

            }
            else if(currentlyShooting && lastRight)
            {
                SDL_RenderCopyEx(rend, playerShootTex, &playerShootRectTex, &windowRect, 0.0, NULL, flip);
//                if(bulletsOnScreen > 0)
//                {
//                    for(int i = 0; i < bulletsOnScreen; i++)
//                    {
//                        SDL_RenderCopy(rend, bulletTex, NULL, &(*bulletArr[i]));
//                    }
//                }

            }
            else if(currentlyShooting && !lastRight)
            {
                SDL_RenderCopy(rend, playerShootTex, &playerShootRectTex, &windowRect);
//                if(bulletsOnScreen > 0)
//                {
//                    for(int i = 0; i < bulletsOnScreen; i++)
//                    {
//                        SDL_RenderCopy(rend, bulletTex, NULL, &(*bulletArr[i]));
//                    }
//                }
            }
            else
            {
                SDL_RenderCopy(rend, spriteSheet, &textureRect, &windowRect);

            }

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
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyTexture(spriteSheet2);
    SDL_DestroyTexture(playerShootTex);
    SDL_DestroyTexture(bulletTex);
    SDL_DestroyTexture(castusSprite);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(title1Tex);
    SDL_DestroyTexture(title2Tex);
    SDL_DestroyTexture(title3Tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}