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

int main(){
    Jogo jogo;

    //Cria a janela;
    InitWindow(LARGURA, ALTURA_TOTAL, "Snake Game");
    SetTargetFPS(60);
    srand(time(NULL)); 

    Texture2D Fundo;
    Fundo = CarregaTextureFundo(&jogo); 
    CarregaTexturaComida(&jogo);

    IniciaJogo(&jogo);
    while (!WindowShouldClose()){
        BeginDrawing();      
        ClearBackground(BLACK);
        DrawTexture(Fundo, 0, BARRA_ALTURA, WHITE);

        DrawRectangle(0, 0, LARGURA, BARRA_ALTURA, WHITE);
        char pontuacao[50];            
        sprintf(pontuacao, "Pontuação: %d", jogo.pontuacao);
        DrawText(pontuacao, 10, 10, 20, BLACK);

        if (jogo.gameOver){
            DesenhaJogo(&jogo);
            AtualizaRodada(&jogo);
/*            if (ColisaoFood(&jogo)){
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
        EndDrawing();
    }
    DescarregaTexturaFundo(&jogo, Fundo);
    DescarregaTexturaComida(&jogo);
    CloseWindow();
    return 0;
}
