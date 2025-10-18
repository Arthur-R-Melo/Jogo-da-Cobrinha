#ifndef JOGO_H
#define JOGO_H

#include "raylib.h"
#include "snake.h"

#define LARGURA 660
#define ALTURA 660
#define STD_SIZE_X 40
#define STD_SIZE_Y 40
#define TEMPO 0.2
#define COOLDOWN 0.2
#define FOOD_COLOR BLUE

#include "raylib.h"

typedef struct Food{
    Rectangle pos;
    Color color;
}Food;

typedef struct Bordas{
    Rectangle pos;
}Bordas;

typedef struct Jogo{
    Body body;
    Food food;
    Bordas bordas[4];
    double tempo;
    double cooldown;
}Jogo;

void IniciaBordas(Jogo *j);
void IniciaFood(Jogo *j);
void IniciaJogo(Jogo *j);
void DesenhaBody(Jogo *j);
void DesenhaFood(Jogo *j);
void DesenhaBordas(Jogo *j);
void DesenhaJogo(Jogo *j);
void AtualizaDirecao(Jogo *j);
void AtualizaPosBody(Jogo *j);
void AtualizaRodada(Jogo *j);
int ColisaoFood(Jogo *j);

#endif