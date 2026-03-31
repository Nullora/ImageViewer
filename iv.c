#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>

int main(){
    //open window
    SDL_Window *pwindow  = SDL_CreateWindow("hello!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 600, 0); 
    //get window surface to draw on
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    //rgb values
    Uint8 r,g,b;
    r = 0xFF;
    g = 0x0;
    b = 0x0;
    Uint32 color = SDL_MapRGB(psurface->format, r,g,b);
    //specific pixel with SDL_Rect {x,y,1,1}
    int x = 50;
    int y = 50;
    const SDL_Rect pixel = (SDL_Rect){x,y,1,1};
    //fill that pixel.
    //fillrect takes (surface, rectangle address (or NULL if you wanna fill the whole screen), color (from SDL_MapRGB))
    SDL_FillRect(psurface, &pixel, color);
    //update screen
    SDL_UpdateWindowSurface(pwindow);
    //delay to see window
    SDL_Delay(3000);
}