#include <stdlib.h>
#include <stdio.h>

#include "food.h"
#include "jogo.h"
#include "snake.h"
#include "coord.h"

//Funcoes para mudar coorFood

int verificaPossivelCoord(int posicoes[16][16], int x, int y){
    return (posicoes[x][y] == 1);
}

int geraXY(){
    return (rand() % 16);
}

void mudaCoordFood(Jogo *j){
    Coord coordFoodAtual = j->food.coord;  
    NodePointer temp = j->body.tail;
    
    //Adiciono todas as coordenadas indevidas em uma Lista Encadeada --
    while(temp->prox != NULL){
        j->body.posicoes[temp->coord.x][temp->coord.y] = 1;
        temp = temp->prox;
    }
    j->body.posicoes[coordFoodAtual.x][coordFoodAtual.y] = 1;    
    //-- x --

    IniciaFood(j);
    Food* tempFood = &j->food;  
    
    //Gero e testo as novas coordenadas para Food
    while(verificaPossivelCoord(j->body.posicoes, tempFood->coord.x, tempFood->coord.y)){
        tempFood->coord.x = geraXY();
        tempFood->coord.y = geraXY();
    }   
}