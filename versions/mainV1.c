#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define LEVEL_WIDTH 30000
#define LEVEL_HEIGHT 30000
#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1000
#define PLAYERWALKINGFRAMES 3
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 128
#define PLAYER_VELOCITY 5500
#define BACKGROUND_SQUARE_SIZE 2000
// #define M_PI 3.14159
//Ubuntu should already have SDL so just run this command to get the Image processing files
// "sudo apt-get install libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0"
// and then you should have everything you need
// ive been compiling with
// "gcc main.c -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lm -o main"
// and then I run with "./main"
int SCREENHEIGHT;
int SCREENWIDTH;
int bgPositionx = 0;
int bgPositiony = 0;
int startPosX = (LEVEL_WIDTH  / 2); 
int startPosY = (LEVEL_HEIGHT / 2);
void getOffset(int i, int j);
double getAngle(int MouseX, int MouseY, int playerWidth, int playerHeight);
int validMoveMent(int playerPosX, int playerPosY, int right, int left, int up, int down);

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

    printf("Screenwidth = %d, screenheight = %d", SCREENWIDTH, SCREENHEIGHT);

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


    //load our music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *titleMusic = NULL;
    titleMusic = Mix_LoadMUS("music/Basshunter.mp3");
    

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





    /****************/
    /* PLAYER RECTS */
    /****************/

    

    SDL_Rect windowRect;
    windowRect.w = 128;
    windowRect.h = 128;
    windowRect.x = (SCREENWIDTH - windowRect.w) / 2;
    windowRect.y = (SCREENHEIGHT - windowRect.h) / 2;


    SDL_Rect windowRect2;
    windowRect2.w = PLAYER_WIDTH;
    windowRect2.h = PLAYER_HEIGHT;
    windowRect2.x = windowRect.x;
    windowRect2.y = windowRect.y;

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

    SDL_Rect playerShootRectWin;
    playerShootRectWin.w = PLAYER_WIDTH;
    playerShootRectWin.h = PLAYER_HEIGHT;
    playerShootRectWin.x = (SCREENWIDTH - playerShootRectWin.w) /2;
    playerShootRectWin.y = (SCREENHEIGHT - playerShootRectWin.h) /2;

    SDL_Rect playerShootRectTex;
    playerShootRectTex.x = 0;
    playerShootRectTex.y = 0;
    playerShootRectTex.w = 128;
    playerShootRectTex.h = 64;




    /********************/
    /* BACKGROUND RECTS */
    /********************/


    //now we want 15 by 15 view of the map
    

    //set up our Rects for our background in the messiest way possible

    //there has to be a better way of doing this but oh well

    //if this was python I could dynamically name variables but we can't in C so we have to manually do it

    SDL_Rect bg00, bg01, bg02, bg03, bg04, bg05, bg06, bg07, bg08, bg09, bg010, bg011, bg012, bg013, bg014;
    SDL_Rect bg10, bg11, bg12, bg13, bg14, bg15, bg16, bg17, bg18, bg19, bg11_0, bg11_1, bg11_2, bg11_3, bg11_4;
    SDL_Rect bg20, bg21, bg22, bg23, bg24, bg25, bg26, bg27, bg28, bg29, bg210, bg211, bg212, bg213, bg214;
    SDL_Rect bg30, bg31, bg32, bg33, bg34, bg35, bg36, bg37, bg38, bg39, bg310, bg311, bg312, bg313, bg314;
    SDL_Rect bg40, bg41, bg42, bg43, bg44, bg45, bg46, bg47, bg48, bg49, bg410, bg411, bg412, bg413, bg414;
    SDL_Rect bg50, bg51, bg52, bg53, bg54, bg55, bg56, bg57, bg58, bg59, bg510, bg511, bg512, bg513, bg514;
    SDL_Rect bg60, bg61, bg62, bg63, bg64, bg65, bg66, bg67, bg68, bg69, bg610, bg611, bg612, bg613, bg614;
    SDL_Rect bg70, bg71, bg72, bg73, bg74, bg75, bg76, bg77, bg78, bg79, bg710, bg711, bg712, bg713, bg714;
    SDL_Rect bg80, bg81, bg82, bg83, bg84, bg85, bg86, bg87, bg88, bg89, bg810, bg811, bg812, bg813, bg814;
    SDL_Rect bg90, bg91, bg92, bg93, bg94, bg95, bg96, bg97, bg98, bg99, bg910, bg911, bg912, bg913, bg914;
    SDL_Rect bg100, bg101, bg102, bg103, bg104, bg105, bg106, bg107, bg108, bg109, bg1010, bg1011, gb1012, bg1013, bg1014;
    SDL_Rect bg110, bg111, bg112, bg113, bg114, bg115, bg116, bg117, bg118, bg119, bg1110, bg1111, gb1112, bg1113, bg1114;
    SDL_Rect bg120, bg121, bg122, bg123, bg124, bg125, bg126, bg127, bg128, bg129, bg1210, bg1211, gb1212, bg1213, bg1214;
    SDL_Rect bg130, bg131, bg132, bg133, bg134, bg135, bg136, bg137, bg138, bg139, bg1310, bg1311, gb1312, bg1313, bg1314;
    SDL_Rect bg140, bg141, bg142, bg143, bg144, bg145, b146, bg147, bg148, b149, bg1410, bg1411, gb1412, bg1413, bg1414;


    //throw all the pointers of them into a 15x15 array of pointers for ease of calling later
    SDL_Rect *backgroundArr[15][15] = {
        {&bg00, &bg01, &bg02, &bg03, &bg04, &bg05, &bg06, &bg07, &bg08, &bg09, &bg010, &bg011, &bg012, &bg013, &bg014},
        {&bg10, &bg11, &bg12, &bg13, &bg14, &bg15, &bg16, &bg17, &bg18, &bg19, &bg11_0, &bg11_1, &bg11_2, &bg11_3, &bg11_4},
        {&bg20, &bg21, &bg22, &bg23, &bg24, &bg25, &bg26, &bg27, &bg28, &bg29, &bg210, &bg211, &bg212, &bg213, &bg214},
        {&bg30, &bg31, &bg32, &bg33, &bg34, &bg35, &bg36, &bg37, &bg38, &bg39, &bg310, &bg311, &bg312, &bg313, &bg314},
        {&bg40, &bg41, &bg42, &bg43, &bg44, &bg45, &bg46, &bg47, &bg48, &bg49, &bg410, &bg411, &bg412, &bg413, &bg414},
        {&bg50, &bg51, &bg52, &bg53, &bg54, &bg55, &bg56, &bg57, &bg58, &bg59, &bg510, &bg511, &bg512, &bg513, &bg514},
        {&bg60, &bg61, &bg62, &bg63, &bg64, &bg65, &bg66, &bg67, &bg68, &bg69, &bg610, &bg611, &bg612, &bg613, &bg614},
        {&bg70, &bg71, &bg72, &bg73, &bg74, &bg75, &bg76, &bg77, &bg78, &bg79, &bg710, &bg711, &bg712, &bg713, &bg714},
        {&bg80, &bg81, &bg82, &bg83, &bg84, &bg85, &bg86, &bg87, &bg88, &bg89, &bg810, &bg811, &bg812, &bg813, &bg814},
        {&bg90, &bg91, &bg92, &bg93, &bg94, &bg95, &bg96, &bg97, &bg98, &bg99, &bg910, &bg911, &bg912, &bg913, &bg914},
        {&bg100, &bg101, &bg102, &bg103, &bg104, &bg105, &bg106, &bg107, &bg108, &bg109, &bg1010, &bg1011, &gb1012, &bg1013, &bg1014},
        {&bg110, &bg111, &bg112, &bg113, &bg114, &bg115, &bg116, &bg117, &bg118, &bg119, &bg1110, &bg1111, &gb1112, &bg1113, &bg1114},
        {&bg120, &bg121, &bg122, &bg123, &bg124, &bg125, &bg126, &bg127, &bg128, &bg129, &bg1210, &bg1211, &gb1212, &bg1213, &bg1214},
        {&bg130, &bg131, &bg132, &bg133, &bg134, &bg135, &bg136, &bg137, &bg138, &bg139, &bg1310, &bg1311, &gb1312, &bg1313, &bg1314},
        {&bg140, &bg141, &bg142, &bg143, &bg144, &bg145, &b146, &bg147, &bg148, &b149, &bg1410, &bg1411, &gb1412, &bg1413, &bg1414}

    };

    //Query all the textures into their respective Rects

    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            getOffset(i, j);
            // bgPositionx = i * 1000;
            // bgPositiony = j * 1000;
            (*backgroundArr[i][j]).x = bgPositionx;
            (*backgroundArr[i][j]).y = bgPositiony;
            (*backgroundArr[i][j]).w = 1000;
            (*backgroundArr[i][j]).h = 1000;
           
            SDL_QueryTexture(backgroundTexture, NULL, NULL, &(*backgroundArr[i][j]).w, &((*backgroundArr[i][j]).h));

            (*backgroundArr[i][j]).w = BACKGROUND_SQUARE_SIZE;
            (*backgroundArr[i][j]).h = BACKGROUND_SQUARE_SIZE;
        }
    }


    



    // load the textures from the spriteSheets into their respective textureRects
    SDL_QueryTexture(title1Tex, NULL, NULL, &title1Rect.w, &title1Rect.h);
    title1Rect.w = SCREENWIDTH;
    title1Rect.h = SCREENHEIGHT;
    SDL_QueryTexture(title2Tex, NULL, NULL, &title2Rect.w, &title2Rect.h);
    title2Rect.w = SCREENWIDTH;
    title2Rect.h = SCREENHEIGHT;
    SDL_QueryTexture(title3Tex, NULL, NULL, &title3Rect.w, &title3Rect.h);
    title3Rect.w = SCREENWIDTH;
    title3Rect.h = SCREENHEIGHT;
    SDL_QueryTexture(spriteSheet, NULL, NULL, &textureRect.w, &textureRect.h);
    SDL_QueryTexture(spriteSheet2, NULL, NULL, &textureRect2.w, &textureRect2.h);
    SDL_QueryTexture(playerShootTex, NULL, NULL, &playerShootRectTex.w, &playerShootRectTex.h);


    // make the widths 64 pixels
    textureRect.w /= PLAYERWALKINGFRAMES;
    textureRect2.w /= PLAYERWALKINGFRAMES;
    playerShootRectTex.w /= 2;


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

    

    
    int backgroundOffsetX = 0;
    int backgroundOffsetY = 0;

    int titleScreen = 1;
    int play = 0;
    int bulletsOnScreen = 0;
    int playerPosX = startPosX;
    int playerPosY = startPosX;
    double angle = 0.0;
    
    if(titleScreen && !play)
    {
        int playHoveredOver = 0;
        int quitHoveredOver = 0;
        int mouse_x;
        int mouse_y;
        int frame = 0;
        int keepPlayingTitleMusic = 1;
        // Mix_PlayMusic(titleMusic, -1);
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
                        // printf("Mouse x = %d mouse y = %d", mouse_x, mouse_y);
                        if(mouse_x >= ((2 * SCREENWIDTH) / 5 ) && mouse_x <= ((13 * SCREENWIDTH) / 25) && mouse_y <= (SCREENHEIGHT - (2 * SCREENHEIGHT / 5))  && mouse_y >= ((13 * SCREENHEIGHT) / 25))
                        {
                            playHoveredOver = 1;
                            quitHoveredOver = 0;
                        }
                        else if(mouse_x >= ((2 * SCREENWIDTH) / 5 ) && mouse_x <= ((13 * SCREENWIDTH) / 25) && mouse_y <= ((69 * SCREENHEIGHT) / 100) && mouse_y >= ((63 * SCREENHEIGHT) / 100))
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
        // Mix_HaltMusic();
        int mouse_x;
        int mouse_y;
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
                    case SDL_MOUSEMOTION:
                        SDL_GetMouseState(&mouse_x, &mouse_y);
                        angle = getAngle(mouse_x, mouse_y, windowRect.w, windowRect.h);
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

            // printf("playerXpos = %d playerYPos = %d\n", playerPosX, playerPosY);
            if(currentlyWalking)
            {

                //this offset "moves" the player
                if(validMoveMent(playerPosX, playerPosY, right, left, up, down))
                {
                    backgroundOffsetX += x_vel / 60;
                    backgroundOffsetY += y_vel / 60;
                    //this normalizes the players position to what were seeing
                    playerPosX = startPosX - backgroundOffsetX + (SCREENWIDTH / 2);
                    playerPosY = startPosY - backgroundOffsetY + (SCREENHEIGHT / 2);


                
                    for(int i = 0; i < 15; i++)
                    {
                        for(int j = 0; j < 15; j++)
                        {

                            getOffset(i, j);  

                            (*backgroundArr[i][j]).x = bgPositionx + backgroundOffsetX;
                            (*backgroundArr[i][j]).y = bgPositiony + backgroundOffsetY;  
                            // (*backgroundArr[i][j]).x += backgroundOffsetX;
                            // (*backgroundArr[i][j]).y += backgroundOffsetY;                
                        
                        }

                    }

                }
                
                
                
            }
                            // printf("player Pos = %d, %d    ", playerPosX, playerPosY);
            // printf("bgOffX = %d  ", backgroundOffsetX);
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

            }
            else
            {
                //if we arent walking just show the first sprite so it looks like were standing still
                textureRect.x = 0;
                textureRect2.x = 0;

            }

            //basically set up the values of RGB we will use
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
            //clear the renderer so we dont just get garbage on our screen
            SDL_RenderClear(rend);


            for(int i = 0; i < 15; i++)
            {
                for(int j = 0; j < 15; j++)
                {
                    SDL_RenderCopy(rend, backgroundTexture, NULL, &(*backgroundArr[i][j]));
                }
            }

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
                if((angle > 0 && angle < 40) || (angle < 0 && angle > -40))
                {
                    SDL_RenderCopyEx(rend, playerShootTex, &playerShootRectTex, &windowRect, angle, NULL, flip);
                }
                else
                {
                    SDL_RenderCopyEx(rend, playerShootTex, &playerShootRectTex, &windowRect, 0.0, NULL, flip);

                }
                

            }
            else if(currentlyShooting && !lastRight)
            {
                                // printf("%f ", angle);
                //-135
                //-150
                if((angle > -179 && angle < -130)  || (angle < 180 && angle > 140))
                {
                    SDL_RenderCopyEx(rend, playerShootTex, &playerShootRectTex, &windowRect, angle - 180 , NULL, SDL_FLIP_NONE);
                }
                else
                {
                    SDL_RenderCopy(rend, playerShootTex, &playerShootRectTex, &windowRect);
                }
                

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
    Mix_FreeMusic(titleMusic);
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}

void getOffset(int i, int j)
{
    bgPositionx = (i * BACKGROUND_SQUARE_SIZE) - startPosX;
    bgPositiony = (j * BACKGROUND_SQUARE_SIZE) - startPosY;
   
}

double getAngle(int MouseX, int MouseY, int playerWidth, int playerHeight)
{
    int multiplierX;
    int multiplierY;

    double deltaX = MouseX - ((SCREENWIDTH - PLAYER_WIDTH)/2);
    double deltaY = MouseY - ((SCREENHEIGHT - PLAYER_HEIGHT)/2);
    

    double angleBetweenPoints = SDL_atan2(deltaY, deltaX) * 180 / M_PI;

    return angleBetweenPoints;


}


//Check if the next position is "valid"
// for example if we're on the right edge of the map, dont allow the player to move right anymore
int validMoveMent(int playerPosX, int playerPosY, int right, int left, int up, int down)
{
    if(playerPosX >= LEVEL_WIDTH - (PLAYER_WIDTH/2))
    {
        if(right) return 0;
    }
    if(playerPosX <= 0 + (PLAYER_WIDTH/2))
    {
        if(left) return 0;
    }
    if(playerPosY >= LEVEL_HEIGHT - (PLAYER_HEIGHT/2))
    {
        if(down) return 0;
    }
    if(playerPosY <= 0 + (PLAYER_HEIGHT/2))
    {
        if(up) return 0;
    }


    return 1;
}