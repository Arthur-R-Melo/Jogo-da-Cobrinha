#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "raylib.h"
#include "snake.h"
#include "jogo.h"
#include "graphic.h"

#define LARGURA 660
#define ALTURA 660
#define STD_SIZE_X 40
#define STD_SIZE_Y 40
#define TEMPO 0.2
#define COOLDOWN 0.2
#define FOOD_COLOR BLUE

int main(){
    Jogo jogo;

    //Cria a janela;
    InitWindow(LARGURA, ALTURA, "Snake Game");
    SetTargetFPS(60);
    srand(time(NULL));  
    
    IniciaJogo(&jogo);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        if (jogo.gameOver){
            DesenhaJogo(&jogo);
            AtualizaRodada(&jogo);
/*            if (ColisaoFood(&jogo)){
              jogo.gameOver = 0;
            }*/
        } else {
            DrawText("Agora é a sua vez!", 150, 200, 40, WHITE);
            DrawText("Continue", 265, 400, 30, WHITE);
            if (IsKeyPressed(KEY_ENTER)){
                IniciaJogo(&jogo);
                jogo.gameOver = 1;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}