#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "snake.h"
#include "food.h"
#include "jogo.h"

#define TAB_SIZE 16

void IniciaFlagAlertaNome(Jogo* j){
    j->flagAlertaNome = 0;
}

void IniciaNomeLength(Jogo* j){
    j->nomeLength = 0;
}

void IniciaNome(Jogo* j){
    j->nome = (char*)calloc(6, sizeof(char));
}

void IniciaPontuacao(Jogo *j){
    j->pontuacao = 0;
}

void IniciaQuantBarreiras(Jogo *j){
    j->quantBarreiras = 18;
}

void IniciaMatrizBarreiras(Jogo *j){
    for(int i = 0; i < 16; i++){
        for(int k = 0; k < 16; k++){
            j->posicoesBarreiraMatriz[i][k] = 0;
        }
    }

    for(int i = 0; i < j->quantBarreiras; i++){
        j->posicoesBarreiraMatriz[j->posicoesBarreira[i].x][j->posicoesBarreira[i].y] = 1;
    }
}

void IniciaDificuldade(Jogo *j){
    j->dificuldade = 0;
}

void IniciaBody(Jogo *j){
    j->body = newBody((Coord) {7, 15}, 0);
}

void IniciaPosicoesBarreira(Jogo *j){
    j->posicoesBarreira[0] = (Coord){5, 5};
    j->posicoesBarreira[1] = (Coord){6, 5};
    j->posicoesBarreira[2] = (Coord){5, 6};

    j->posicoesBarreira[3] = (Coord){12, 9};
    j->posicoesBarreira[4] = (Coord){13, 9};
    j->posicoesBarreira[5] = (Coord){13, 10};
    j->posicoesBarreira[6] = (Coord){13, 11};
    j->posicoesBarreira[7] = (Coord){10, 1};

    j->posicoesBarreira[8] = (Coord){5, 9};
    j->posicoesBarreira[9] = (Coord){2, 4};
    j->posicoesBarreira[10] = (Coord){6, 12};
    j->posicoesBarreira[11] = (Coord){15, 12};
    j->posicoesBarreira[12] = (Coord){11, 10};
    j->posicoesBarreira[13] = (Coord){12, 14};
    j->posicoesBarreira[14] = (Coord){13, 1};
    j->posicoesBarreira[15] = (Coord){8, 3};
    j->posicoesBarreira[16] = (Coord){5, 5};
    j->posicoesBarreira[17] = (Coord){3, 3};
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

void AtualizaBordas(Jogo *j) {
    //Borda de cima
    j->bordas[0].pos = (Rectangle) {0, BARRA_ALTURA, LARGURA*j->resize, 10};
    //Borda da direita
    j->bordas[1].pos = (Rectangle) {(LARGURA-10)*j->resize, BARRA_ALTURA, 10*j->resize, ALTURA_JOGO*j->resize};
    //Borda de baixo
    j->bordas[2].pos = (Rectangle) {0, (ALTURA_JOGO-10)*j->resize + BARRA_ALTURA, LARGURA*j->resize, 10*j->resize};
    //Borda da esquerda
    j->bordas[3].pos = (Rectangle) {0, BARRA_ALTURA, 10*j->resize, ALTURA_JOGO*j->resize};
}

void IniciaFood(Jogo *j){
    Coord tempCoord = (Coord) {rand()%16, rand()%16};
    while(tempCoord.x == 7 && tempCoord.y == 15){
        tempCoord = (Coord) {rand()%16, rand()%16};
    }

    j->food.coord = tempCoord;
    j->food.color = FOOD_COLOR;
}

void IniciaJogo(Jogo *j, int flagNome){

    if(flagNome){
        IniciaNomeLength(j);
        IniciaNome(j);
    }
    IniciaFlagAlertaNome(j);
    IniciaDificuldade(j);
    IniciaPosicoesBarreira(j);
    IniciaQuantBarreiras(j);
    IniciaMatrizBarreiras(j);
    IniciaBordas(j);
    IniciaBody(j);
    IniciaFood(j);
    IniciaPontuacao(j);    
    j->tempo = GetTime();
    j->gameOver = 1;
    j->resize = STD_WIN_SIZE_FACTOR;
}

void AtualizaDirecao(Jogo *j){
    //Atualiza para qual direção a cobra vai  
    if(IsKeyPressed(KEY_UP) && j->body.head->direcao != DIR_DOWN && GetTime() - j->cooldown > COOLDOWN){
        j->body.head->direcao = DIR_UP;
        j->cooldown = GetTime();
    }
    if(IsKeyPressed(KEY_RIGHT) && j->body.head->direcao != DIR_LEFT && GetTime() - j->cooldown > COOLDOWN){
        j->body.head->direcao = DIR_RIGHT;
        j->cooldown = GetTime();
    }
    if(IsKeyPressed(KEY_DOWN) && j->body.head->direcao != DIR_UP && GetTime() - j->cooldown > COOLDOWN){
        j->body.head->direcao = DIR_DOWN;
        j->cooldown = GetTime();
    }
    if(IsKeyPressed(KEY_LEFT) && j->body.head->direcao != DIR_RIGHT && GetTime() - j->cooldown > COOLDOWN){
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

    if(j->dificuldade == 2 && ColisaoBarreira(j, coord)){
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

int ColisaoBarreira(Jogo* j, Coord coord){
    return (j->posicoesBarreiraMatriz[coord.x][coord.y] == 1);
}
