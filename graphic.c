#include "graphic.h"
#include "jogo.h"
#include "snake.h"
#include "coord.h"

#include <stdio.h>

void coordToPosition(Coord coord, float* x, float*y);

void DesenhaBody(Jogo *j){
    NodePointer temp = j->body.tail;
    float x, y;
    Rectangle rec;
    while (temp)
    {
        coordToPosition(temp->coord, &x, &y);
        rec.x = x;
        rec.y = y;
        rec.width = STD_SIZE_X;
        rec.height = STD_SIZE_Y;

        DrawRectangleRec(rec, SNAKE_COLOR);

        temp = temp->prox;
    }
}

void DesenhaFood(Jogo *j){
    float x, y;
    coordToPosition(j->food.coord, &x, &y);
    Rectangle rec;
    rec.width = STD_SIZE_X;
    rec.height = STD_SIZE_Y;
    rec.x = x;
    rec.y = y;

    DrawRectangleRec(rec, j->food.color);
}

void DesenhaBordas(Jogo *j){
    //Desenha as barreiras nas bordas
    for (int i = 0; i < 4; i++){
        DrawRectangleRec(j->bordas[i].pos, LIGHTGRAY);
    }
}

void DesenhaJogo(Jogo *j){
    DesenhaBordas(j);
    DesenhaFood(j);
    DesenhaBody(j);
}

void coordToPosition(Coord coord, float* x, float*y) {
    *x = (float)(coord.x * 40 + 10);
    *y = (float)(coord.y * 40 + 10);
}