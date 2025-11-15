#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "raylib.h"
#include "snake.h"
#include "jogo.h"
#include "graphic.h"
#include "food.h"

#define LARGURA 660
#define ALTURA_JOGO 660
#define BARRA_ALTURA 40
#define ALTURA_TOTAL (ALTURA_JOGO + BARRA_ALTURA)
#define STD_SIZE_X 40
#define STD_SIZE_Y 40
#define TEMPO 0.2
#define COOLDOWN 0.2
#define FOOD_COLOR BLUE

typedef enum {
    TELA_MENU,
    TELA_JOGO
} Tela;

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

int main(){
    Jogo jogo;

    //Cria a janela;
    InitWindow(LARGURA, ALTURA_TOTAL, "Snake Game");
    SetTargetFPS(60);
    srand(time(NULL)); 

    Texture2D Fundo;
    CarregaRabo(&jogo);
    CarregaCabeca(&jogo);
    CarregaBody(&jogo);
    Fundo = CarregaTextureFundo(&jogo); 
    CarregaTexturaComida(&jogo);
    CarregaQuinaCobra(&jogo);

    IniciaJogo(&jogo);

    Tela telaAtual = TELA_MENU;

    while (!WindowShouldClose()){
        BeginDrawing();      
        ClearBackground(BLACK);
        
        if(telaAtual == TELA_MENU){
            desenhaDificuldade(&jogo);
            DrawText("PRESS ENTER TO START", 70, 500, 40, RED);

            if(IsKeyPressed(KEY_ENTER)){
                telaAtual = TELA_JOGO;
            }
        }

        else if(telaAtual == TELA_JOGO){
        
            DrawTexture(Fundo, 0, BARRA_ALTURA, WHITE);

            DrawRectangle(0, 0, LARGURA, BARRA_ALTURA, WHITE);
            char pontuacao[50];            
            sprintf(pontuacao, "Pontuação: %d", jogo.pontuacao);
            DrawText(pontuacao, 10, 10, 20, BLACK);

            if (jogo.gameOver){
                DesenhaJogo(&jogo);
                AtualizaRodada(&jogo);
                /*if (ColisaoFood(&jogo)){
                jogo.gameOver = 0;
                }*/
            } else {
                char texto[50];            
                sprintf(texto, "Sua pontuacao foi: %d!", jogo.pontuacao);
                
                DrawText("GAME OVER!", 200, 200, 40, RED);
                DrawText(texto, 180, 260, 30, WHITE);
                DrawText("Continue", 265, 400, 30, WHITE);
                if (IsKeyPressed(KEY_ENTER)){
                    IniciaJogo(&jogo);
                    jogo.gameOver = 1;
                }
            }
        }
        EndDrawing();
    }
    DescarregaRabo(&jogo);
    DescarregaCabeca(&jogo);
    DescarregaBody(&jogo);
    DescarregaTexturaFundo(&jogo, Fundo);
    DescarregaTexturaComida(&jogo);
    DescarregaQuinaCobra(&jogo);
    CloseWindow();
    return 0;
}
