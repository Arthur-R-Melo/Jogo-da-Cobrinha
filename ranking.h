#ifndef RANKING_H
#define RANKING_H

#define NAME_SIZE 3
#define RANKING_SIZE 20
#define HARD_RANKING 1
#define MEDIUM_RANKING 2
#define EASY_RANKING 3
#define EASY_RANKIN_PATH "easyRanking.bin"
#define MEDIUM_RANKING_PATH "mediumRanking.bin"
#define HARD_RANKING_PATH "hardRanking.bin"

typedef struct Player{
    char nome[NAME_SIZE];
    int pont;
}Player;

typedef struct Ranking{
    Player jogadores[RANKING_SIZE];
    int length;
}Ranking;

Ranking getRanking(int dificuldade);
Ranking addInRanking(int dificuldade, Player jogador, int index);
int isInRanking(int dificuldade, int pont); //Retorna o indice + 1 da posicao a ser inserido

#endif