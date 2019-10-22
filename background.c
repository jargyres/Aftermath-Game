#include "background.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>


#define BACKGROUND_SQUARE_SIZE 2000
#define LEVEL_WIDTH 30000
#define LEVEL_HEIGHT 30000
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 128
#define PLAYER_VELOCITY 300

// int bgpositionx = 0;
// int bgpositiony = 0;
int startposX = (LEVEL_WIDTH  / 2); 
int startposY = (LEVEL_HEIGHT / 2);
int validMoveMent(int playerPosX, int playerPosY, int right, int left, int up, int down);
void getOffset(background * me, int i, int j);

void background_Constructor(background * me, char* backgroundImagePath,char* minimapImagePath, char* minimapArrowImagePath, char* inventoryImagePath, int ScreenWidth, int ScreenHeight, SDL_Renderer *rend)
{
    //    SDL_Rect bg10, bg11, bg12, bg13, bg14, bg15, bg16, bg17, bg18, bg19, bg11_0, bg11_1, bg11_2, bg11_3, bg11_4;
    //    SDL_Rect bg110, bg111, bg112, bg113, bg114, bg115, bg116, bg117, bg118, bg119, bg1110, bg1111, gb1112, bg1113, bg1114;

    me->bgPosX = 0;
    me->bgPosY = 0;

    me->ScreenWidth = ScreenWidth;
    me->ScreenHeight = ScreenHeight;

    me->backgroundArr[0][0] = &(me->b00); me->backgroundArr[0][1] = &(me->b01); me->backgroundArr[0][2] = &(me->b02); me->backgroundArr[0][3] = &(me->b03); me->backgroundArr[0][4] = &(me->b04); me->backgroundArr[0][5] = &(me->b05); me->backgroundArr[0][6] = &(me->b06); me->backgroundArr[0][7] = &(me->b07); me->backgroundArr[0][8] = &(me->b08); me->backgroundArr[0][9] = &(me->b09); me->backgroundArr[0][10] = &(me->b010); me->backgroundArr[0][11] = &(me->b011); me->backgroundArr[0][12] = &(me->b012); me->backgroundArr[0][13] = &(me->b013); me->backgroundArr[0][14] = &(me->b014);
    me->backgroundArr[1][0] = &(me->bg10); me->backgroundArr[1][1] = &(me->bg11); me->backgroundArr[1][2] = &(me->bg12); me->backgroundArr[1][3] = &(me->bg13); me->backgroundArr[1][4] = &(me->bg14); me->backgroundArr[1][5] = &(me->bg15); me->backgroundArr[1][6] = &(me->bg16); me->backgroundArr[1][7] = &(me->bg17); me->backgroundArr[1][8] = &(me->bg18); me->backgroundArr[1][9] = &(me->bg19); me->backgroundArr[1][10] = &(me->bg11_0); me->backgroundArr[1][11] = &(me->bg11_1); me->backgroundArr[1][12] = &(me->bg11_2); me->backgroundArr[1][13] = &(me->bg11_3); me->backgroundArr[1][14] = &(me->bg11_4);
    me->backgroundArr[2][0] = &(me->bg20); me->backgroundArr[2][1] = &(me->bg21); me->backgroundArr[2][2] = &(me->bg22); me->backgroundArr[2][3] = &(me->bg23); me->backgroundArr[2][4] = &(me->bg24); me->backgroundArr[2][5] = &(me->bg25); me->backgroundArr[2][6] = &(me->bg26); me->backgroundArr[2][7] = &(me->bg27); me->backgroundArr[2][8] = &(me->bg28); me->backgroundArr[2][9] = &(me->bg29); me->backgroundArr[2][10] = &(me->bg210); me->backgroundArr[2][11] = &(me->bg211); me->backgroundArr[2][12] = &(me->bg212); me->backgroundArr[2][13] = &(me->bg213); me->backgroundArr[2][14] = &(me->bg214);
    me->backgroundArr[3][0] = &(me->bg30); me->backgroundArr[3][1] = &(me->bg31); me->backgroundArr[3][2] = &(me->bg32); me->backgroundArr[3][3] = &(me->bg33); me->backgroundArr[3][4] = &(me->bg34); me->backgroundArr[3][5] = &(me->bg35); me->backgroundArr[3][6] = &(me->bg36); me->backgroundArr[3][7] = &(me->bg37); me->backgroundArr[3][8] = &(me->bg38); me->backgroundArr[3][9] = &(me->bg39); me->backgroundArr[3][10] = &(me->bg310); me->backgroundArr[3][11] = &(me->bg311); me->backgroundArr[3][12] = &(me->bg312); me->backgroundArr[3][13] = &(me->bg313); me->backgroundArr[3][14] = &(me->bg314);
    me->backgroundArr[4][0] = &(me->bg40); me->backgroundArr[4][1] = &(me->bg41); me->backgroundArr[4][2] = &(me->bg42); me->backgroundArr[4][3] = &(me->bg43); me->backgroundArr[4][4] = &(me->bg44); me->backgroundArr[4][5] = &(me->bg45); me->backgroundArr[4][6] = &(me->bg46); me->backgroundArr[4][7] = &(me->bg47); me->backgroundArr[4][8] = &(me->bg48); me->backgroundArr[4][9] = &(me->bg49); me->backgroundArr[4][10] = &(me->bg410); me->backgroundArr[4][11] = &(me->bg411); me->backgroundArr[4][12] = &(me->bg412); me->backgroundArr[4][13] = &(me->bg413); me->backgroundArr[4][14] = &(me->bg414);
    me->backgroundArr[5][0] = &(me->bg50); me->backgroundArr[5][1] = &(me->bg51); me->backgroundArr[5][2] = &(me->bg52); me->backgroundArr[5][3] = &(me->bg53); me->backgroundArr[5][4] = &(me->bg54); me->backgroundArr[5][5] = &(me->bg55); me->backgroundArr[5][6] = &(me->bg56); me->backgroundArr[5][7] = &(me->bg57); me->backgroundArr[5][8] = &(me->bg58); me->backgroundArr[5][9] = &(me->bg59); me->backgroundArr[5][10] = &(me->bg510); me->backgroundArr[5][11] = &(me->bg511); me->backgroundArr[5][12] = &(me->bg512); me->backgroundArr[5][13] = &(me->bg513); me->backgroundArr[5][14] = &(me->bg514);
    me->backgroundArr[6][0] = &(me->bg60); me->backgroundArr[6][1] = &(me->bg61); me->backgroundArr[6][2] = &(me->bg62); me->backgroundArr[6][3] = &(me->bg63); me->backgroundArr[6][4] = &(me->bg64); me->backgroundArr[6][5] = &(me->bg65); me->backgroundArr[6][6] = &(me->bg66); me->backgroundArr[6][7] = &(me->bg67); me->backgroundArr[6][8] = &(me->bg68); me->backgroundArr[6][9] = &(me->bg69); me->backgroundArr[6][10] = &(me->bg610); me->backgroundArr[6][11] = &(me->bg611); me->backgroundArr[6][12] = &(me->bg612); me->backgroundArr[6][13] = &(me->bg613); me->backgroundArr[6][14] = &(me->bg614);
    me->backgroundArr[7][0] = &(me->bg70); me->backgroundArr[7][1] = &(me->bg71); me->backgroundArr[7][2] = &(me->bg72); me->backgroundArr[7][3] = &(me->bg73); me->backgroundArr[7][4] = &(me->bg74); me->backgroundArr[7][5] = &(me->bg75); me->backgroundArr[7][6] = &(me->bg76); me->backgroundArr[7][7] = &(me->bg77); me->backgroundArr[7][8] = &(me->bg78); me->backgroundArr[7][9] = &(me->bg79); me->backgroundArr[7][10] = &(me->bg710); me->backgroundArr[7][11] = &(me->bg711); me->backgroundArr[7][12] = &(me->bg712); me->backgroundArr[7][13] = &(me->bg713); me->backgroundArr[7][14] = &(me->bg714);
    me->backgroundArr[8][0] = &(me->bg80); me->backgroundArr[8][1] = &(me->bg81); me->backgroundArr[8][2] = &(me->bg82); me->backgroundArr[8][3] = &(me->bg83); me->backgroundArr[8][4] = &(me->bg84); me->backgroundArr[8][5] = &(me->bg85); me->backgroundArr[8][6] = &(me->bg86); me->backgroundArr[8][7] = &(me->bg87); me->backgroundArr[8][8] = &(me->bg88); me->backgroundArr[8][9] = &(me->bg89); me->backgroundArr[8][10] = &(me->bg810); me->backgroundArr[8][11] = &(me->bg811); me->backgroundArr[8][12] = &(me->bg812); me->backgroundArr[8][13] = &(me->bg813); me->backgroundArr[8][14] = &(me->bg814);
    me->backgroundArr[9][0] = &(me->bg90); me->backgroundArr[9][1] = &(me->bg91); me->backgroundArr[9][2] = &(me->bg92); me->backgroundArr[9][3] = &(me->bg93); me->backgroundArr[9][4] = &(me->bg94); me->backgroundArr[9][5] = &(me->bg95); me->backgroundArr[9][6] = &(me->bg96); me->backgroundArr[9][7] = &(me->bg97); me->backgroundArr[9][8] = &(me->bg98); me->backgroundArr[9][9] = &(me->bg99); me->backgroundArr[9][10] = &(me->bg910); me->backgroundArr[9][11] = &(me->bg911); me->backgroundArr[9][12] = &(me->bg912); me->backgroundArr[9][13] = &(me->bg913); me->backgroundArr[9][14] = &(me->bg914);
    me->backgroundArr[10][0] = &(me->bg100); me->backgroundArr[10][1] = &(me->bg101); me->backgroundArr[10][2] = &(me->bg102); me->backgroundArr[10][3] = &(me->bg103); me->backgroundArr[10][4] = &(me->bg104); me->backgroundArr[10][5] = &(me->bg105); me->backgroundArr[10][6] = &(me->bg106); me->backgroundArr[10][7] = &(me->bg107); me->backgroundArr[10][8] = &(me->bg108); me->backgroundArr[10][9] = &(me->bg109); me->backgroundArr[10][10] = &(me->bg1010); me->backgroundArr[10][11] = &(me->bg1011); me->backgroundArr[10][12] = &(me->gb1012); me->backgroundArr[10][13] = &(me->bg1013); me->backgroundArr[10][14] = &(me->bg1014);
    me->backgroundArr[11][0] = &(me->bg110); me->backgroundArr[11][1] = &(me->bg111); me->backgroundArr[11][2] = &(me->bg112); me->backgroundArr[11][3] = &(me->bg113); me->backgroundArr[11][4] = &(me->bg114); me->backgroundArr[11][5] = &(me->bg115); me->backgroundArr[11][6] = &(me->bg116); me->backgroundArr[11][7] = &(me->bg117); me->backgroundArr[11][8] = &(me->bg118); me->backgroundArr[11][9] = &(me->bg119); me->backgroundArr[11][10] = &(me->bg1110); me->backgroundArr[11][11] = &(me->bg1111); me->backgroundArr[11][12] = &(me->gb1112); me->backgroundArr[11][13] = &(me->bg1113); me->backgroundArr[11][14] = &(me->bg1114);
    me->backgroundArr[12][0] = &(me->bg120); me->backgroundArr[12][1] = &(me->bg121); me->backgroundArr[12][2] = &(me->bg122); me->backgroundArr[12][3] = &(me->bg123); me->backgroundArr[12][4] = &(me->bg124); me->backgroundArr[12][5] = &(me->bg125); me->backgroundArr[12][6] = &(me->bg126); me->backgroundArr[12][7] = &(me->bg127); me->backgroundArr[12][8] = &(me->bg128); me->backgroundArr[12][9] = &(me->bg129); me->backgroundArr[12][10] = &(me->bg1210); me->backgroundArr[12][11] = &(me->bg1211); me->backgroundArr[12][12] = &(me->gb1212); me->backgroundArr[12][13] = &(me->bg1213); me->backgroundArr[12][14] = &(me->bg1214);
    me->backgroundArr[13][0] = &(me->bg130); me->backgroundArr[13][1] = &(me->bg131); me->backgroundArr[13][2] = &(me->bg132); me->backgroundArr[13][3] = &(me->bg133); me->backgroundArr[13][4] = &(me->bg134); me->backgroundArr[13][5] = &(me->bg135); me->backgroundArr[13][6] = &(me->bg136); me->backgroundArr[13][7] = &(me->bg137); me->backgroundArr[13][8] = &(me->bg138); me->backgroundArr[13][9] = &(me->bg139); me->backgroundArr[13][10] = &(me->bg1310); me->backgroundArr[13][11] = &(me->bg1311); me->backgroundArr[13][12] = &(me->gb1312); me->backgroundArr[13][13] = &(me->bg1313); me->backgroundArr[13][14] = &(me->bg1314);
    me->backgroundArr[14][0] = &(me->bg140); me->backgroundArr[14][1] = &(me->bg141); me->backgroundArr[14][2] = &(me->bg142); me->backgroundArr[14][3] = &(me->bg143); me->backgroundArr[14][4] = &(me->bg144); me->backgroundArr[14][5] = &(me->bg145); me->backgroundArr[14][6] = &(me->b146); me->backgroundArr[14][7] = &(me->bg147); me->backgroundArr[14][8] = &(me->bg148); me->backgroundArr[14][9] = &(me->b149); me->backgroundArr[14][10] = &(me->bg1410); me->backgroundArr[14][11] = &(me->bg1411); me->backgroundArr[14][12] = &(me->gb1412); me->backgroundArr[14][13] = &(me->bg1413); me->backgroundArr[14][14] = &(me->bg1414);

    
    SDL_Surface* surface = IMG_Load(backgroundImagePath);

    SDL_Surface* surface2 = IMG_Load(minimapArrowImagePath);

    SDL_Surface* surface3 = IMG_Load(minimapImagePath);

    SDL_Surface* surface4 = IMG_Load(inventoryImagePath);

    me->backgroundTexture = SDL_CreateTextureFromSurface(rend, surface);

    me->minimapArrowTex = SDL_CreateTextureFromSurface(rend, surface2);

    me->minimapTex = SDL_CreateTextureFromSurface(rend, surface3);

    me->inventoryTex = SDL_CreateTextureFromSurface(rend, surface4);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);
    SDL_FreeSurface(surface3);
    SDL_FreeSurface(surface4);


    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            getOffset(me, i, j);
            // bgPositionx = i * 1000;
            // bgPositiony = j * 1000;
            (*me->backgroundArr[i][j]).x = me->bgPosX;
            (*me->backgroundArr[i][j]).y = me->bgPosY;
            (*me->backgroundArr[i][j]).w = 1000;
            (*me->backgroundArr[i][j]).h = 1000;
           
            SDL_QueryTexture(me->backgroundTexture, NULL, NULL, &(*(me->backgroundArr)[i][j]).w, &(*(me->backgroundArr)[i][j]).w);

            (*(me->backgroundArr)[i][j]).w = BACKGROUND_SQUARE_SIZE;
            (*(me->backgroundArr)[i][j]).h = BACKGROUND_SQUARE_SIZE;
        }
    }

    me->minimapRect.x = 0;
    me->minimapRect.y = 0;
    me->minimapRect.w = 300;
    me->minimapRect.h = 300;

    me->minimapArrowRect.x = startposX / 100;
    me->minimapArrowRect.y = startposY / 100;
    me->minimapArrowRect.w = 7;
    me->minimapArrowRect.h = 7;

    me->inventoryRect.x = (me->ScreenWidth) - 300;
    me->inventoryRect.y = 0;
    me->inventoryRect.w = 300;
    me->inventoryRect.h = 300;

    SDL_QueryTexture(me->minimapTex, NULL, NULL, &me->minimapRect.w, &me->minimapRect.h);
    SDL_QueryTexture(me->minimapArrowTex, NULL, NULL, &me->minimapArrowRect.w, &me->minimapArrowRect.h);
    SDL_QueryTexture(me->inventoryTex, NULL, NULL, &me->inventoryRect.w, &me->inventoryRect.h);

    me->minimapArrowRect.w *= 2;
    me->minimapArrowRect.h *= 2;
   

}

float x_vel = 0.0;
float y_vel = 0.0;
int backgroundOffsetX = 0;
int backgroundOffsetY = 0;

void background_SetPlayerPos(background * me, int playerPosX, int playerPosY)
{
    me->playerposx = playerPosX;
    me->playerposy = playerPosY;


}

void background_Move(background * me, int currentlyWalking, int right, int left, int up, int down, int SCREENWIDTH, int SCREENHEIGHT)
{
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

    if(currentlyWalking)
            {

                //this offset "moves" the player
                if(validMoveMent(me->playerposx, me->playerposy, right, left, up, down))
                {
                    backgroundOffsetX += x_vel / 60;
                    backgroundOffsetY += y_vel / 60;
                    //this normalizes the players position to what were seeing
                    me->playerposx = startposX - backgroundOffsetX + (SCREENWIDTH / 2);
                    me->playerposy = startposY - backgroundOffsetY + (SCREENHEIGHT / 2);

                    me->minimapArrowRect.x = me->playerposx / 100;
                    me->minimapArrowRect.y = me->playerposy / 100;


                
                    for(int i = 0; i < 15; i++)
                    {
                        for(int j = 0; j < 15; j++)
                        {

                            getOffset(me, i, j);  

                            (*(me->backgroundArr)[i][j]).x = me->bgPosX + backgroundOffsetX;
                            (*(me->backgroundArr)[i][j]).y = me->bgPosY + backgroundOffsetY;  
                            // (*backgroundArr[i][j]).x += backgroundOffsetX;
                            // (*backgroundArr[i][j]).y += backgroundOffsetY;                
                        
                        }

                    }

                }
                
                
                
            }

}

void background_Draw(background * me, int minimapShowing, int inventoryShowing, int lastRight, int lastDown, int currentlyUp, SDL_Renderer *rend)
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            SDL_RenderCopy(rend, me->backgroundTexture, NULL, &(*(me->backgroundArr)[i][j]));
        }
    }

    if(minimapShowing)
    {
        SDL_RenderCopy(rend, me->minimapTex, NULL, &(me->minimapRect));

        if(lastDown) SDL_RenderCopyEx(rend, me->minimapArrowTex, NULL, &(me->minimapArrowRect), 0.0, NULL, SDL_FLIP_VERTICAL);
        else if(lastRight) SDL_RenderCopyEx(rend, me->minimapArrowTex, NULL, &(me->minimapArrowRect), 90.0, NULL, SDL_FLIP_NONE);
        else if(currentlyUp) SDL_RenderCopy(rend, me->minimapArrowTex, NULL, &(me->minimapArrowRect));
        else if(!lastRight) SDL_RenderCopyEx(rend, me->minimapArrowTex, NULL, &(me->minimapArrowRect), 270.0, NULL, SDL_FLIP_NONE);

    }
    else if(inventoryShowing)
    {
        SDL_RenderCopy(rend, me->inventoryTex, NULL, &(me->inventoryRect));
    }

}

void background_Free(background * me)
{
    SDL_DestroyTexture(me->backgroundTexture);
    SDL_DestroyTexture(me->minimapArrowTex);
    SDL_DestroyTexture(me->minimapTex);
    SDL_DestroyTexture(me->inventoryTex);
}


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

void getOffset(background * me, int i, int j)
{

    me->bgPosX = (i * BACKGROUND_SQUARE_SIZE) - startposX;
    me->bgPosY = (j * BACKGROUND_SQUARE_SIZE) - startposY;
   
}
