#include "graphic.h"
#include "jogo.h"
#include "snake.h"
#include "coord.h"

#include <stdio.h>

//Funções para uso exclusivamente interno, por isso não estão no cabeçalho
void coordToPosition(Coord coord, float* x, float*y);
void rotateImage(Vector2* vec, float* degree, int direction);
void rotateQuina(int pastDir, int newDir, Vector2* vec, float* degree, Rectangle* rec);

void desenhaDificuldade(Jogo* j){ 
    Vector2 p1 = {230, 350};
    Vector2 p2 = {250, 380};
    Vector2 p3 = {250, 320};

    Vector2 p4 = {430, 350};
    Vector2 p5 = {410, 320};
    Vector2 p6 = {410, 380};    

    DrawRectangle(260, 320, 140, 60, WHITE);

    bool hoverT1  = CheckCollisionPointTriangle(GetMousePosition(), p1, p2, p3);
    bool hoverT2  = CheckCollisionPointTriangle(GetMousePosition(), p4, p5, p6);

    if(hoverT1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        if(j->dificuldade > 0) j->dificuldade--;
        else j->dificuldade = 2;
    }

    if(hoverT2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        if(j->dificuldade < 2) j->dificuldade++;
        else j->dificuldade = 0;
    }    

    switch (j->dificuldade){
        case 0:
            DrawText("Fácil", 290, 335, 35, GREEN);
            break;

        case 1:
            DrawText("Médio", 285, 335, 35, ORANGE);
            break;

        case 2:
            DrawText("Difícil", 285, 335, 35, RED);
            break;
            
        default:
            break;
    }
    
    Color corT1 = WHITE;
    Color corT2 = WHITE;

    if(hoverT1) corT1 = RED;
    if(hoverT2) corT2 = RED;

    DrawTriangle(p1, p2, p3, corT1);
    DrawTriangle(p4, p5, p6, corT2);
}

void DesenhaBody(Jogo *j){
    NodePointer temp = j->body.tail;
    float x, y;
    int pastDirection = j->body.head->direcao;
    Rectangle rec;
    while (temp)
    {
        coordToPosition(temp->coord, &x, &y);
        float degree = 0.0f;
        Vector2 position = (Vector2){0,0};
        rec.x = x;
        rec.y = y;
        rec.width = STD_SIZE_X;
        rec.height = STD_SIZE_Y;
        Rectangle src = (Rectangle) {0,0,STD_SIZE_X,STD_SIZE_Y};        

        if (temp == j->body.head) {
            //DrawRectangleRec(rec, RED);
            rotateImage(&position, &degree, temp->direcao);
            DrawTexturePro(j->cabeca,
                  (Rectangle){0, 0, j->cabeca.width, j->cabeca.height},
                  rec,
                  position,
                  degree,
                  WHITE);
        } else if (pastDirection != temp->direcao && temp != j->body.tail){
            rotateQuina(pastDirection, temp->direcao, &position, &degree, &src);
            DrawTexturePro(j->quinaCobra, src, rec, position, degree, WHITE);
        }else if (temp == j->body.tail){
            rotateImage(&position, &degree, temp->direcao);
            DrawTexturePro(j->rabo,
                  (Rectangle){0, 0, j->rabo.width, j->rabo.height},
                  rec,
                  position,
                  degree,
                  WHITE);
        }else {
            rotateImage(&position, &degree, temp->direcao);
            DrawTexturePro(j->corpo,
                  (Rectangle){0, 0, j->corpo.width, j->corpo.height},
                  rec,
                  position,
                  degree,
                  WHITE);
        }

        pastDirection = temp->direcao;
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
    Texture2D fundo = LoadTexture("assets/background2.png");
    return fundo;
}

void DescarregaTexturaFundo(Jogo* jogo, Texture2D fundo){
    UnloadTexture(fundo);
}

void CarregaQuinaCobra(Jogo* jogo) {
    jogo->quinaCobra = LoadTexture("assets/curve.png");
}

void DescarregaQuinaCobra(Jogo* jogo) {
    UnloadTexture(jogo->quinaCobra);
}

void CarregaCabeca(Jogo* jogo){
    jogo->cabeca = LoadTexture("assets/head2.png");
}

void DescarregaCabeca(Jogo* jogo){
    UnloadTexture(jogo->cabeca);
}

void CarregaBody(Jogo* jogo){
    jogo->corpo = LoadTexture("assets/body.png");
}

void DescarregaBody(Jogo* jogo){
    UnloadTexture(jogo->corpo);
}

void CarregaRabo(Jogo* jogo){
    jogo->rabo = LoadTexture("assets/tail.png");
}

void DescarregaRabo(Jogo* jogo){
    UnloadTexture(jogo->rabo);
}

void CarregaTexturaComida(Jogo *jogo) {
    jogo->foodTexture.texture = LoadTexture("assets/apple.png");
    if (jogo->foodTexture.texture.id == 0) {
        printf("ERRO: Não foi possível carregar textura da comida!\n");
    }
}

void DescarregaTexturaComida(Jogo *jogo) {
        UnloadTexture(jogo->foodTexture.texture);
}

void rotateQuina(int pastDir, int newDir, Vector2* vec, float* degree, Rectangle* rec) {

    if (newDir == DIR_LEFT) rec->width*=-1;
    if (pastDir == DIR_DOWN) rec->height*=-1;
    if (pastDir == DIR_LEFT) {
        *degree = -90.0f;
        vec->x+=STD_SIZE_X;
        if (newDir == DIR_DOWN) rec->width*=-1;
    }
    if (pastDir == DIR_RIGHT){
        *degree = 90;
        vec->y+=STD_SIZE_Y;
        if (newDir == DIR_UP) rec->width*=-1;
    }
    
}

void rotateImage(Vector2* vec, float* degree, int direction) {

    if (direction == DIR_UP) return;
    
    if (direction == DIR_DOWN) {
        *degree = 180.0f;
        vec->x+=STD_SIZE_X;
        vec->y+=STD_SIZE_Y;

        return;
    }

    if (direction == DIR_LEFT) {
        *degree = -90.0f;
        vec->x+=STD_SIZE_X;

        return;
    }
    
    if (direction == DIR_RIGHT) {
        *degree = 90.0f;
        vec->y+=STD_SIZE_Y;

        return;
    }
}
