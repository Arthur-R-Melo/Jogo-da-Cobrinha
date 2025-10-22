#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <stdio.h>

#include "jogo.h"
#include "snake.h"
#include "coord.h"

//Funcoes para mudar coorFood
int verificaPossivelCoord(int posicoes[16][16], int x, int y);
void mudaCoordFood(Jogo *j);

#endif