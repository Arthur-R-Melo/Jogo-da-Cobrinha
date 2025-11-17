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

void iniciaMatrizPosicoes(int mat[16][16]){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            mat[i][j] = 0;
        }
    }
}

void mudaCoordFood(Jogo *j){
    Coord coordFoodAtual = j->food.coord;  
    NodePointer temp = j->body.tail;

    int posicoes[16][16];    

    iniciaMatrizPosicoes(posicoes);    
    
    //Adiciono todas as coordenadas indevidas em uma Lista Encadeada --
    while(temp->prox != NULL){
        posicoes[temp->coord.x][temp->coord.y] = 1;
        temp = temp->prox;
    }
    posicoes[coordFoodAtual.x][coordFoodAtual.y] = 1;    
    //-- x --

    IniciaFood(j);
    Food* tempFood = &j->food;  
    
    //Gero e testo as novas coordenadas para Food
    if(j->dificuldade == 2){
        while(verificaPossivelCoord(posicoes, tempFood->coord.x, tempFood->coord.y) || 
        verificaPossivelCoord(j->posicoesBarreiraMatriz, tempFood->coord.x, tempFood->coord.y)){
            tempFood->coord.x = geraXY();
            tempFood->coord.y = geraXY();
        }   
    }else{
        while(verificaPossivelCoord(posicoes, tempFood->coord.x, tempFood->coord.y)){
            tempFood->coord.x = geraXY();
            tempFood->coord.y = geraXY();
        }
    }
}