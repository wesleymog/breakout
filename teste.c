#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
/*Dados da tela*/
const int ALT=800;
const int LAR=600;

SDL_Surface* loadSurface( char *path );
typedef struct _Personagem{
    int posX;
    int posY;
    int stepX;
    int stepY;
    SDL_Surface* image;
    int imgW;
    int imgH;
} Personagem;
/*Dados da bola*/
Personagem bola;
const int Largura_bola = 100;
const int Altura_bola = 100;

/*Dados do bastao*/
Personagem bastao;
const int Largura_bastao = 100;
const int Altura_bastao = 50;

/*Dados do tijolo*/
Personagem tijolo[10][3];
const int Largura_tijolo = 70;
const int Altura_tijolo = 35;

/*Funcoes*/
Personagem criarPersonagem( int posX, int posY, int stepX, int stepY, SDL_Surface *image);
int colocarnatela(Personagem p,SDL_Surface* tela,int largura,int altura,int posx, int posy);
int inicializar();
void fechar();


SDL_Window* gTela = NULL;
SDL_Surface* gTelaSurface=NULL;
SDL_Surface* gBastaoSurface = NULL;
SDL_Surface* gBolaSurface = NULL;
SDL_Surface* gTijoloSurface = NULL;



int main(int argc, char *args[]){
  int rodando,x;
  SDL_Event event;
  if(!inicializar()){
    printf("Tivemos um problema na inicializacao");
    return 0;
  }else{
    SDL_FillRect( gTelaSurface, NULL,SDL_MapRGB( gTelaSurface->format,255, 255, 255 ) );
    gBastaoSurface = loadSurface( "./barra.jpg" );
    gBolaSurface = loadSurface( "./ball3.jpg" );
    gTijoloSurface = loadSurface( "./muro.jpg" );
    bastao = criarPersonagem(350,550,50, 50, gBastaoSurface);
    bola = criarPersonagem(300,450,50, 50, gBolaSurface);
    tijolo[0][0] = criarPersonagem(10,0,50, 50, gTijoloSurface);
    colocarnatela(bastao,gTelaSurface,Largura_bastao,Altura_bastao,0,0);
    colocarnatela(bola,gTelaSurface,Largura_bola,Altura_bola,0,0);
    colocarnatela(tijolo[0][0],gTelaSurface,Largura_tijolo,Altura_tijolo,0,0);

    for(x=1;x<11;x++){
      tijolo[x][0] = criarPersonagem(10,0,50, 50, gTijoloSurface);
      colocarnatela(tijolo[x][0],gTelaSurface,Largura_tijolo,Altura_tijolo,(Largura_tijolo*x)+tijolo[x][0].posX,0);
    }
    SDL_UpdateWindowSurface( gTela );
  /*SDL_Renderer *renderer = SDL_CreateRenderer(gTela, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);*/
  rodando = true;
  while( rodando ) {
      while( SDL_PollEvent( &event ) != 0 ) {
          if (event.type==SDL_QUIT){
            rodando = false;
          }
      }
  }
  /* SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_Rect rect = {10, 10, 10, 10};
  SDL_RenderFillRect(renderer, &rect);*/
  SDL_Delay(5);
  fechar();
  return 0;
}
}
int inicializar() {
    int sucesso = true;

    srand(time(NULL));

    /*Initialize SDL*/
    if(SDL_Init(SDL_INIT_VIDEO)<0){
      printf("Não conseguimos inicializar o vídeo");
      sucesso=false;
    }
    else {
      int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
      if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
          printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
          sucesso = false;
      }
      else {
      gTela = SDL_CreateWindow("O melhor breakout de todos!",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,ALT,LAR,SDL_WINDOW_SHOWN);
      if( gTela == NULL ) {
            printf( "Temos um problema na criação de Janela %s\n", SDL_GetError() );
            sucesso = false;
        }else{
          gTelaSurface = SDL_GetWindowSurface( gTela );
        }
    }
  }
    return sucesso;
}
void fechar(){
  SDL_DestroyWindow(gTela);
  SDL_Quit();
}
Personagem criarPersonagem( int posX, int posY, int stepX, int stepY,
               SDL_Surface *image) {
    Personagem p;
    p.posX = posX;
    p.posY = posY;
    p.stepX = stepX;
    p.stepY = stepY;
    p.image = image;
    return p;
}
SDL_Surface* loadSurface( char *path ) {
    /*The final optimized image*/
    SDL_Surface* optimizedSurface = NULL;

    /*Load image at specified path*/
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else {
        /*Convert surface to screen format*/
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gTelaSurface->format, 0 );
        if( optimizedSurface == NULL ) {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        /*Get rid of old loaded surface*/
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}
int colocarnatela(Personagem p,SDL_Surface* tela,int largura,int altura,int posx, int posy){
  int rodando=true;
  SDL_Rect srcRect,dstRect;
  srcRect.x = 0; srcRect.y = 0;
  srcRect.w = largura;
  srcRect.h = altura;
  if(posx==0 && posy==0){
    dstRect.x = p.posX;
    dstRect.y = p.posY;
  }else{
    dstRect.x = posx;
    dstRect.y = posy;
  }
  if( SDL_BlitSurface( p.image, &srcRect,gTelaSurface, &dstRect ) < 0 ) {
      printf( "Problema com o blit! SDL Error: %s\n", SDL_GetError() );
      rodando=false;
  }
  return rodando;
}
