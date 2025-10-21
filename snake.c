#include <stdlib.h>
#include <stdio.h>

#include "snake.h"

void iniciaMatrizPosicoes(Body* body){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            body->posicoes[i][j] = 0;
        }
    }
}

Body newBody(Coord coord, int direcao){
    Body body;
    body.direcao = direcao;
    body.tail = malloc(sizeof(Node));
    body.tail->coord = coord;
    body.tail->prox = NULL;
    body.head = body.tail;

    iniciaMatrizPosicoes(&body);

    body.posicoes[body.tail->coord.x][body.tail->coord.y] = 1;

    return body;
}

void insertInHead(Body* cobra, Coord coord){
    NodePointer temp = malloc(sizeof(Node));
    temp->prox = NULL;
    temp->coord = coord;
    cobra->head->prox = temp;
    cobra->head = temp;

    cobra->posicoes[temp->coord.x][temp->coord.y] = 1;
}

void removeFromTail(Body* cobra){
    if (cobra->tail->prox == NULL)
    {
        printf("Error: nothing to remove");
        return;
    }
    
    NodePointer temp = cobra->tail;
    cobra->tail = cobra->tail->prox;

    cobra->posicoes[temp->coord.x][temp->coord.y] = 0;

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