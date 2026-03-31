#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>

int main(){
        //header data
    FILE *in = stdin;
    char *pthrow = calloc(1000, sizeof(char));
    //read first line (header [P6 for binary]) {skip}
    fgets(pthrow, 1000, in);
    //read second line (comment) {skip}
    fgets(pthrow, 1000, in);
    //read third line (width height) {important}
    char *pdimensions = calloc(1000, sizeof(char));
    fgets(pdimensions, 1000, in);
    int width=-1;
    int height=-1;
    //best function in the world easiest parse of my life
    sscanf(pdimensions, "%d %d\n", &width, &height);
    free(pdimensions);
    //debug
    printf("width=%d height=%d\n", width, height);
    //read 4th line (max color value) {skip}
    fgets(pthrow, 1000, in);
    free(pthrow);



    SDL_Window *pwindow  = SDL_CreateWindow("hello!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0); 
    //get window surface to draw on
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    //specific pixel with SDL_Rect {x,y,1,1}
    SDL_Rect pixel = (SDL_Rect){0,0,1,1};
    Uint32 color = 0x00;
    for(int y = 0; y<width; y++){
        for(int x = 0; x<height;x++){
            //rgb values
            Uint8 r,g,b;
            //grab from file
            r = (char)getchar();
            g = (char)getchar();
            b = (char)getchar();
            color = SDL_MapRGB(psurface->format, r,g,b);
            pixel.x = x;
            pixel.y = y;
            //fillrect takes (surface, rectangle address (or NULL if you wanna fill the whole screen), color (from SDL_MapRGB))
            SDL_FillRect(psurface, &pixel, color);
        }
    }
    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay(3000);
}