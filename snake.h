#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

#define SNAKE_COLOR YELLOW

typedef struct Body{
    Rectangle pos;
    Color color;
    int direcao;
}Body;


#endif