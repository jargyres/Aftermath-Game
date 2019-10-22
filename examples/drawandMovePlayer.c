#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


int SCREENWIDTH;
int SCREENHEIGHT;

int main() {

    //gcc examples/drawBackgrdrawandMovePlayer.c -lSDL2 -lSDL2main -lSDL2_image -o bg

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
    {
     SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
     return 1;
    }

    SCREENWIDTH = dm.w - (dm.w / 4);
    SCREENHEIGHT = dm.h - (dm.h / 5);


    SDL_Window *win = SDL_CreateWindow("Game",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       SCREENWIDTH, SCREENHEIGHT,
                                       SDL_WINDOW_SHOWN);


    
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    //this will be the rendered we use
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);
    SDL_Event event;
    int quit = 0;


    SDL_Texture* backgroundTex = NULL;

    SDL_Texture* playerTex = NULL;

    SDL_Surface* backgroundSurface = IMG_Load("/home/john/Game/images/background.png");

    SDL_Surface* playerSurface = IMG_Load("/home/john/Game/images/player1.png");

    backgroundTex = SDL_CreateTextureFromSurface(rend, backgroundSurface);

    playerTex = SDL_CreateTextureFromSurface(rend, playerSurface);

    SDL_FreeSurface(playerSurface);

    SDL_FreeSurface(backgroundSurface);

    SDL_Rect backgroundRect;

    backgroundRect.x = 0;

    backgroundRect.y = 0;

    backgroundRect.w = 1000;

    backgroundRect.h = 1000;

    SDL_Rect playerRect;

    playerRect.x = 0;

    playerRect.y = 0;

    playerRect.w = 64;

    playerRect.h = 64;

    SDL_QueryTexture(backgroundTex, NULL, NULL, &backgroundRect.w, &backgroundRect.h);

    SDL_QueryTexture(playerTex, NULL, NULL, &playerRect.w, &playerRect.h);

    backgroundRect.w = SCREENWIDTH;

    backgroundRect.h = SCREENHEIGHT;


    while(!quit)
    {

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;
            }
        }

        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

        SDL_RenderCopy(rend, backgroundTex, NULL, &backgroundRect);

        SDL_RenderPresent(rend);

        SDL_Delay(floor(16.666));




    }


    SDL_DestroyTexture(backgroundTex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

}


