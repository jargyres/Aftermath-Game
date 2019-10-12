#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>



typedef struct {

    SDL_Texture* backgroundTexture;
    SDL_Texture* minimapArrowTex;
    SDL_Texture* minimapTex;
    SDL_Texture* inventoryTex;

    int playerposx;
    int playerposy;
    int bgPosX;
    int bgPosY;
    int ScreenHeight;
    int ScreenWidth;


    
    SDL_Rect b00, b01, b02, b03, b04, b05, b06, b07, b08, b09, b010, b011, b012, b013, b014;
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
    
    SDL_Rect *backgroundArr[15][15];

    SDL_Rect minimapRect;

    SDL_Rect minimapArrowRect;

    SDL_Rect inventoryRect;




} background;

void background_Constructor(background * me, char* backgroundImagePath, char* minimapImagePath, char* minimapArrowImagePath, char* inventoryImagePath,int ScreenWidth, int ScreenHeight, SDL_Renderer *rend);

void background_SetPlayerPos(background * me, int playerPosX, int playerPosY);

void background_Move(background * me, int currentlyWalking, 
                    int right, int left, int up, int down,
                    int SCREENWIDTH, int SCREENHEIGHT);
void background_Draw(background * me, int minimapShowing, int inventoryShowing, int lastRight, int lastDown, int currentlyUp, SDL_Renderer *rend);

void background_Free(background * me);



#endif