#include "graphic.h"
#include "jogo.h"
#include "snake.h"
#include "coord.h"

#include <stdio.h>

void coordToPosition(Coord coord, float* x, float*y);

void DesenhaBody(Jogo *j){
    NodePointer temp = j->body.tail;
    float x, y;
    Rectangle rec;
    while (temp)
    {
        coordToPosition(temp->coord, &x, &y);
        rec.x = x;
        rec.y = y;
        rec.width = STD_SIZE_X;
        rec.height = STD_SIZE_Y;

        if (temp == j->body.head) {
            DrawRectangleRec(rec, RED);
        } else {
            DrawRectangleRec(rec, SNAKE_COLOR);
        }

        temp = temp->prox;
    }
}

void DesenhaFood(Jogo *j){
    float x, y;
    coordToPosition(j->food.coord, &x, &y);
    Rectangle rec;
    rec.width = STD_SIZE_X;
    rec.height = STD_SIZE_Y;
    rec.x = x;
    rec.y = y;

    DrawTexturePro(j->foodTexture.texture,
                  (Rectangle){0, 0, j->foodTexture.texture.width, j->foodTexture.texture.height},
                  rec,
                  (Vector2){0, 0},
                  0.0f,
                  WHITE);
}

void DesenhaBordas(Jogo *j){
    //Desenha as barreiras nas bordas
    for (int i = 0; i < 4; i++){
        DrawRectangleRec(j->bordas[i].pos, LIGHTGRAY);
    }
}

void DesenhaJogo(Jogo *j){
    DesenhaBordas(j);
    DesenhaFood(j);
    DesenhaBody(j);
}

void coordToPosition(Coord coord, float* x, float*y) {
    *x = (float)(coord.x * 40 + 10);
    *y = (float)(coord.y * 40 + 50);
}

Texture2D CarregaTextureFundo(Jogo *jogo){
    Texture2D fundo = LoadTexture("assets/background.png");
    return fundo;
}

void DescarregaTexturaFundo(Jogo* jogo, Texture2D fundo){
    UnloadTexture(fundo);
}

void CarregaTexturaComida(Jogo *jogo) {
    jogo->foodTexture.texture = LoadTexture("assets/teste.png");
    if (jogo->foodTexture.texture.id == 0) {
        printf("ERRO: Não foi possível carregar textura da comida!\n");
    }
}

void DescarregaTexturaComida(Jogo *jogo) {
        UnloadTexture(jogo->foodTexture.texture);
}
