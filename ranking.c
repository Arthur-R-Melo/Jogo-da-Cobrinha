#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ranking.h"

Ranking getRanking(int dificuldade) {
    char path[50];
    switch (dificuldade){
        case EASY_RANKING:
            strcpy(path, "easyRanking.bin");
        break;
        case MEDIUM_RANKING:
            strcpy(path, "mediumRanking.bin");
        break;
        case HARD_RANKING:
        default:
            strcpy(path, "hardRanking.bin");
        break;
    }
    FILE *f = fopen(path, "rb");
    Ranking r;
    r.lenght = 0;
    if (f == NULL) return r;
    fread(&r, sizeof(Ranking), 1, f);
    fclose(f);
    return r;
}

int isInRanking(int dificuldade, int pont) {
    Ranking r = getRanking(dificuldade);
    for (int i = 0; i<r.lenght; i++) {
        if (pont > r.jogadores[i].pont) return i+1;
    }
    if(r.lenght<RANKING_SIZE) return r.lenght+1;
    return 0;
}

Ranking addInRanking(int dificuldade, Player p, int index, Ranking r) {

    /*
    * Caso lenght = 0, index = 0 e na primeira execução i = -1
    * portanto o for não deverá rodar para valores válidos
    */
    for (int i = r.lenght; i>index; i--) {
        r.jogadores[i] = r.jogadores[i-1];
    }
    r.jogadores[index] = p;
    char path[50];
    switch (dificuldade){
        case EASY_RANKING:
            strcpy(path, "easyRanking.bin");
        break;
        case MEDIUM_RANKING:
            strcpy(path, "mediumRanking.bin");
        break;
        case HARD_RANKING:
        default:
            strcpy(path, "hardRanking.bin");
        break;
    }
    FILE *f = fopen(path, "wb");
    fwrite(&r, sizeof(Ranking), 1, f);
    fclose(f);
}