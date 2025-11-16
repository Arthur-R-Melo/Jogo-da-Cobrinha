#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "snake.h"
#include "food.h"
#include "jogo.h"

#define TAB_SIZE 16

void IniciaPontuacao(Jogo *j){
    j->pontuacao = 0;
}

void IniciaDificuldade(Jogo *j){
    j->dificuldade = 0;
}

void IniciaBody(Jogo *j){
    j->body = newBody((Coord) {7, 15}, 0);
}

void IniciaBordas(Jogo *j){
    //Borda de cima
    j->bordas[0].pos = (Rectangle) {0, BARRA_ALTURA, LARGURA, 10};
    //Borda da direita
    j->bordas[1].pos = (Rectangle) {LARGURA - 10, BARRA_ALTURA, 10, ALTURA_JOGO};
    //Borda de baixo
    j->bordas[2].pos = (Rectangle) {0, ALTURA_TOTAL-10, LARGURA, 10};
    //Borda da esquerda
    j->bordas[3].pos = (Rectangle) {0, BARRA_ALTURA, 10, ALTURA_JOGO};
}

void IniciaFood(Jogo *j){
    Coord tempCoord = (Coord) {rand()%16, rand()%16};
    while(tempCoord.x == 7 && tempCoord.y == 15){
        tempCoord = (Coord) {rand()%16, rand()%16};
    }

    j->food.coord = tempCoord;
    j->food.color = FOOD_COLOR;
}

void IniciaJogo(Jogo *j){
    IniciaDificuldade(j);
    IniciaBordas(j);
    IniciaBody(j);
    IniciaFood(j);
    IniciaPontuacao(j);    
    j->tempo = GetTime();
    j->gameOver = 1;
}

void AtualizaDirecao(Jogo *j){
    //Atualiza para qual direção a cobra vai  
    if(IsKeyDown(KEY_UP) && j->body.head->direcao != DIR_DOWN && GetTime() - j->cooldown > COOLDOWN){
        j->body.head->direcao = DIR_UP;
        j->cooldown = GetTime();
    }
    if(IsKeyDown(KEY_RIGHT) && j->body.head->direcao != DIR_LEFT && GetTime() - j->cooldown > COOLDOWN){
        j->body.head->direcao = DIR_RIGHT;
        j->cooldown = GetTime();
    }
    if(IsKeyDown(KEY_DOWN) && j->body.head->direcao != DIR_UP && GetTime() - j->cooldown > COOLDOWN){
        j->body.head->direcao = DIR_DOWN;
        j->cooldown = GetTime();
    }
    if(IsKeyDown(KEY_LEFT) && j->body.head->direcao != DIR_RIGHT && GetTime() - j->cooldown > COOLDOWN){
        j->body.head->direcao = DIR_LEFT;
        j->cooldown = GetTime();
    }
}

void AtualizaPosBody(Jogo *j){

    Coord coord = j->body.head->coord;

    if (j->body.head->direcao == 0){
        coord.y--;
        if(j->dificuldade == 0){
            coord.y+=TAB_SIZE;
            coord.y%=TAB_SIZE;
        }
    }
    if (j->body.head->direcao == 1){
        coord.x++;
        if(j->dificuldade == 0){
            coord.x+=TAB_SIZE;
            coord.x%=16;
        }
    }
    if (j->body.head->direcao == 2){
        coord.y++;
        if(j->dificuldade == 0){
            coord.y+=TAB_SIZE;
            coord.y%=16;
        }
    }
    if (j->body.head->direcao == 3){
        coord.x--;
        if(j->dificuldade == 0){
            coord.x+=TAB_SIZE;
            coord.x%=16;
        }
    }

    if(coord.x < 0 || coord.x > 15 || coord.y < 0 || coord.y > 15){
        j->gameOver = 0;
        return;
    }

    if (isSnakeInCoord(&(j->body), coord) && !(!ColisaoFood(j) && compareCoord(coord, j->body.tail->coord))){
        j->gameOver = 0;
        return;
    }
    
    if (ColisaoFood(j))
    {
        growSnake(&(j->body), coord);
        mudaCoordFood(j);
        j->pontuacao++;
        
        //Mudança de coord food
                

    }else{
        moveSnake(&(j->body), coord);
    }
}

void AtualizaRodada(Jogo *j){
    AtualizaDirecao(j);
    if (GetTime() - j->tempo > TEMPO){
        AtualizaPosBody(j);
        j->tempo = GetTime();
        j->cooldown = COOLDOWN;
    }
}

int ColisaoFood(Jogo *j){
    return compareCoord(j->body.head->coord, j->food.coord);
}
