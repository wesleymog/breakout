#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

SDL_Window* gWindow = NULL;
SDL_Surface* gMainScreen = NULL;

int inicio(){
  int sucesso = false;

  SDL_Init(SDL_INIT_VIDEO);
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("O erro foi %s", SDL_GetError());
  }else{
    gWindow = SDL_CreateWindow("O melhor breakout de todos!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
    if (gWindow = NULL){
      printf("O erro foi %s", SDL_GetError());
    }
    else{
      sucesso = true;
      gMainScreen = SDL_GetWindowSurface(gWindow);
      SDL_FillRect( gMainScreen, NULL, SDL_MapRGB( gMainScreen->format,0xFF, 0xFF, 0xFF ) );

    }
  }
  return sucesso;
}

void termino(){
  SDL_DestroyWindow(gWindow);
  SDL_Quit();
}

int main( int argc, char* args[] ) {
  if(inicio == false){
    printf("Deu erro no inicio.\n");
  }
  else{
    SDL_UpdateWindowSurface(gWindow);
    SDL_Delay(2000);
  }
  termino();
  return 0;
}
