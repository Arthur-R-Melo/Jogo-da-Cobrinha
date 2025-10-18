#include <stdlib.h>
#include <stdio.h>

#include "snake.h"

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