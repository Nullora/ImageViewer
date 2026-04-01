#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>

//i intentionally write comments everywhere so i teach myself along the way
int main(){
    //header data
        //this is one of the first times C makes perfect sense and works first try!!!!
        //usually i need to consult claude cz C is hell on earth
    printf("Enter a filepath(.ppm only): \n");
    //a big mistake i did here is writing char user; instead of char user[254]; i forgot it needs to be an array
    char user[254];
    //i discovered that scanf waits for user input and sscanf just grabs from an stdin pipe or a file
    scanf("%s", user);
    FILE *in = fopen(user, "rb");
    if(!in){
        //fancy error handling to avoid segfault >:)
        fprintf(stderr,"unable to open file\n");
        exit(1);
    }
    //pthrow is what im gonna throw away and not use
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


    SDL_Window *pwindow  = SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0); 
    //get window surface to draw on
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    //single pixel with SDL_Rect {x,y,1,1}
    SDL_Rect pixel = (SDL_Rect){0,0,1,1};
    Uint32 color = 0x00;
    Uint8 r,g,b;
    for(int y = 0; y<height; y++){
        for(int x = 0; x<width;x++){
            //rgb data for each pixel
            //fgetc instead of getchar cz now were actually opening the file instead of piping the data into stdin
            //"man getc" told me getc is used for some macro shit so i stuck with fgetcs
            r = (char)fgetc(in);
            g = (char)fgetc(in);
            b = (char)fgetc(in);
            color = SDL_MapRGB(psurface->format, r,g,b);
            pixel.x = x;
            pixel.y = y;
            //fillrect takes (surface, rectangle address (or NULL if you wanna fill the whole screen), color (from SDL_MapRGB))
            SDL_FillRect(psurface, &pixel, color);
        }
    }
    SDL_UpdateWindowSurface(pwindow);
    fclose(in);
    //handle quit
    int app_running = 1;
    while(app_running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type== SDL_QUIT){
                app_running = 0;
            }
        }
        SDL_Delay(50);
    }
}