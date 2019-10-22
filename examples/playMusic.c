#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


int SCREENWIDTH;
int SCREENHEIGHT;

int main() {

    //gcc playMusic.c -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -o bg; ./bg

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
    
    // Track if the game has been exited
    int quit = 0;

    // Load musc file in!
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *titleMusic = NULL;
    titleMusic = Mix_LoadMUS("../music/Basshunter.mp3");

    // Play the song
    Mix_PlayMusic(titleMusic, -1);


    // Keep window open until exit is hit
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
    }


    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    Mix_FreeMusic(titleMusic);
    SDL_Quit();

}


