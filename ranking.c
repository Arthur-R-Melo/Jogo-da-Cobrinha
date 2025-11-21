#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ranking.h"

void getRankingPath(int dificuldade, char* path);

Ranking getRanking(int dificuldade) {
    char path[50];
    getRankingPath(dificuldade, path);
    FILE *f = fopen(path, "rb");
    Ranking r = { 0 };
    if (f == NULL) return r;
    fread(&r.length, sizeof(int), 1, f);
    fread(r.jogadores, sizeof(Player), r.length, f);
    fclose(f);
    return r;
}


/*
* Retorna indice começando em 1 de forma proposital
* para que possa validar se retorna algo válido de forma mais fácil
*/
int isInRanking(int dificuldade, int pont) {
    Ranking r = getRanking(dificuldade);
    for (int i = 0; i<r.length; i++) {
        if (pont > r.jogadores[i].pont) return i+1;
    }
    if(r.length<RANKING_SIZE) return r.length+1;
    return 0;
}
/*
* Recebe  indice começando do 0
*/
Ranking addInRanking(int dificuldade, Player p, int index) {
    Ranking r = getRanking(dificuldade);
    /*
    * Caso lenght = 0, index = 0 e na primeira execução i = -1
    * portanto o for não deverá rodar para valores válidos
    */
    if (r.length < RANKING_SIZE) r.length++;
    for (int i = r.length-1; i>index; i--) {
        r.jogadores[i] = r.jogadores[i-1];
    }
    r.jogadores[index] = p;
    char path[50];
    getRankingPath(dificuldade, path);
    FILE *f = fopen(path, "wb");
    fwrite(&r.length, sizeof(int), 1, f);
    fwrite(r.jogadores, sizeof(Player), r.length, f);
    fclose(f);
    return r;
}

void getRankingPath(int dificuldade, char* path) {
     switch (dificuldade){
        case EASY_RANKING:
            strcpy(path, EASY_RANKIN_PATH);
        break;
        case MEDIUM_RANKING:
            strcpy(path, MEDIUM_RANKING_PATH);
        break;
        case HARD_RANKING:
        default:
            strcpy(path, HARD_RANKING_PATH);
        break;
    }
}