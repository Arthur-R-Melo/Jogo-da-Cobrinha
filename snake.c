#include <stdlib.h>
#include <stdio.h>

#include "snake.h"

Body newBody(Coord coord, int direcao){
    Body body;
    body.direcao = direcao;
    body.tail = malloc(sizeof(Node));
    body.tail->coord = coord;
    body.tail->prox = NULL;
    body.head = body.tail;

    return body;
}

void insertInHead(Body* cobra, Coord coord){
    NodePointer temp = malloc(sizeof(Node));
    temp->prox = NULL;
    temp->coord = coord;
    cobra->head->prox = temp;
    cobra->head = temp;
}

void removeFromTail(Body* cobra){
    if (cobra->tail->prox == NULL)
    {
        printf("Error: nothing to remove");
        return;
    }
    
    NodePointer temp = cobra->tail;
    cobra->tail = cobra->tail->prox;
    free(temp);    
}

void moveSnake(Body* cobra, Coord coord) {
    insertInHead(cobra, coord);
    removeFromTail(cobra);
}
void growSnake(Body* cobra, Coord coord){
    insertInHead(cobra, coord);
}
int isSnakeInCoord(Body* cobra, Coord coord) {
    NodePointer temp = cobra->tail;

    while (temp){
        if (compareCoord(temp->coord, coord))
        {
            return 1;
        }
        temp = temp->prox;
    }

    return 0;
    
}