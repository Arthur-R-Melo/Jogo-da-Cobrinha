#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

#define SNAKE_COLOR YELLOW

typedef struct Node *NodePointer;

typedef struct Coord{
    int x;
    int y;
}Coord;


typedef struct Node{
    NodePointer prox;
    Coord coord;
}Node;

/*
* O começo da estrutura Body se dá na cauda
*/
typedef struct Body{
    NodePointer head;
    NodePointer tail;
    Rectangle pos;
    Color color;
    int direcao;
}Body;

void insertInHead(Body* cobra, Coord coord);
void removeFromTail(Body* cobra);

#endif