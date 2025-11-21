#ifndef JOGO_H
#define JOGO_H

#include "raylib.h"
#include "snake.h"

#define LARGURA 660
#define ALTURA_JOGO 660
#define BARRA_ALTURA 40
#define ALTURA_TOTAL (ALTURA_JOGO + BARRA_ALTURA)
#define STD_SIZE_X 40
#define STD_SIZE_Y 40
#define TEMPO 0.2
#define COOLDOWN 0.2
#define FOOD_COLOR BLUE
#define DIR_UP 0
#define DIR_RIGHT 1
#define DIR_DOWN 2
#define DIR_LEFT 3
#define STD_WIN_SIZE_FACTOR 1.0f
#define ALT_WIN_SIZE_FACTOR 1.25F;

typedef struct Bordas{
    Rectangle pos;
}Bordas;

typedef struct Food{
    Coord coord;
    Color color;
}Food;

typedef struct FoodTextures{
    Texture2D texture;
} FoodTextures;

typedef struct Jogo{
    Body body;
    Food food;
    FoodTextures foodTexture;
    Texture2D quinaCobra;
    Texture2D cabeca;
    Texture2D corpo;
    Texture2D rabo;
    Texture2D barreira;
    Bordas bordas[4];
    double tempo;
    double cooldown;
    int gameOver;
    int pontuacao;
    int dificuldade;
    Coord posicoesBarreira[18];
    int posicoesBarreiraMatriz[16][16];
    int quantBarreiras;
    float resize;
}Jogo;

void IniciaBordas(Jogo *j);
void IniciaFood(Jogo *j);
void IniciaJogo(Jogo *j);
void AtualizaDirecao(Jogo *j);
void AtualizaPosBody(Jogo *j);
void AtualizaRodada(Jogo *j);
int ColisaoFood(Jogo *j);
int ColisaoBarreira(Jogo* j, Coord coord);
void AtualizaBordas(Jogo *j);

#endif
