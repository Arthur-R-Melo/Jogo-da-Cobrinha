#ifndef RANKING_H
#define RANKING_H

#define NAME_SIZE 3
#define RANKING_SIZE 20
#define HARD_RANKING 1
#define MEDIUM_RANKING 2
#define EASY_RANKING 3

typedef struct Player{
    char nome[NAME_SIZE];
    int pont;
}Player;

typedef struct Ranking{
    Player jogadores[RANKING_SIZE];
    int lenght;
}Ranking;

Ranking getRanking(int dificuldade);
Ranking addInRanking(int dificuldade, Player jogador);

#endif