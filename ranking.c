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
    FILE *f = fopen(path, "r");
    Ranking r;
    fread(&r, sizeof(Ranking), 1, f);
    return r;
}