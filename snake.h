#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

#include "coord.h"

typedef struct Node *NodePointer;


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
//    Rectangle pos;
//    Color color;
    int direcao;
}Body;

Body newBody(Coord coord, int direcao);
void insertInHead(Body* cobra, Coord coord);
void removeFromTail(Body* cobra);

#endif