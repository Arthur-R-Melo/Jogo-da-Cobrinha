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
    Bordas bordas[4];
    double tempo;
    double cooldown;
    int gameOver;
    int pontuacao;
}Jogo;

void IniciaBordas(Jogo *j);
void IniciaFood(Jogo *j);
void IniciaJogo(Jogo *j);
void AtualizaDirecao(Jogo *j);
void AtualizaPosBody(Jogo *j);
void AtualizaRodada(Jogo *j);
int ColisaoFood(Jogo *j);

#endif
