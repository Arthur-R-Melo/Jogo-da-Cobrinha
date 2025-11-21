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
#include "ranking.h"

#define LARGURA 660
#define ALTURA_JOGO 660
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

int main(){
    Jogo jogo;

    //Cria a janela;
    InitWindow(LARGURA, ALTURA_TOTAL, "Snake Game");
    SetTargetFPS(60);
    srand(time(NULL)); 
    int flagRanking = 0;//Verdadeiro se o rank já foi adicionado
    char name[NAME_SIZE];
    name[0] = '\0';
    int indexRanking = 0;
    int len = 0;

    Texture2D Fundo;
    CarregaRabo(&jogo);
    CarregaCabeca(&jogo);
    CarregaBody(&jogo);
    Fundo = CarregaTextureFundo(&jogo); 
    CarregaTexturaComida(&jogo);
    CarregaQuinaCobra(&jogo);
    CarregaTextureBarreira(&jogo);

    IniciaJogo(&jogo);

    Tela telaAtual = TELA_MENU;

    while (!WindowShouldClose()){
        SetWindowSize(LARGURA*jogo.resize, ALTURA_JOGO*jogo.resize + BARRA_ALTURA);
        BeginDrawing();      
        ClearBackground(BLACK);
        
        if(telaAtual == TELA_MENU){
            desenhaDificuldade(&jogo);
            desenhaTamanhoTela(&jogo);
            DrawText("PRESS ENTER TO START", LARGURA*jogo.resize/2 - 260, (ALTURA_JOGO*jogo.resize+BARRA_ALTURA)/2 + 150, 40, RED);

            if(IsKeyPressed(KEY_ENTER)){
                telaAtual = TELA_JOGO;
            }
        }

        else if(telaAtual == TELA_JOGO){
            DrawTexturePro(Fundo, (Rectangle) {0, 0, LARGURA, ALTURA_JOGO},
             (Rectangle) {0, BARRA_ALTURA, LARGURA*jogo.resize, ALTURA_JOGO*jogo.resize}, (Vector2) {0,0}, 0.0f,WHITE);
            AtualizaBordas(&jogo);
            DrawRectangle(0, 0, LARGURA*jogo.resize, BARRA_ALTURA, WHITE);
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
                
                DrawText("GAME OVER!", LARGURA*jogo.resize/2 - 130,  (ALTURA_JOGO*jogo.resize+BARRA_ALTURA)/2 - 150, 40, RED);
                DrawText(texto, LARGURA*jogo.resize/2 - 150,  (ALTURA_JOGO*jogo.resize+BARRA_ALTURA)/2 - 90, 30, WHITE);
                DrawText("Continue", LARGURA*jogo.resize/2 - 65,  (ALTURA_JOGO*jogo.resize+BARRA_ALTURA)/2 + 50, 30, WHITE);
                if(!flagRanking) {
                    if (!indexRanking) indexRanking = isInRanking(jogo.dificuldade, jogo.pontuacao);
                    if (!indexRanking) flagRanking = 1;
                    else {
                        flagRanking = leituraNome(name, &len, &jogo);
                        if (flagRanking) {
                            Player player;
                            strcpy(player.nome, name);
                            player.pont = jogo.pontuacao;
                            addInRanking(jogo.dificuldade, player, flagRanking - 1);
                        }
                    }
                }
                if (IsKeyPressed(KEY_ENTER)){
                    IniciaJogo(&jogo);
                    indexRanking = 0;
                    flagRanking = 0;
                    name[0] = '\0';
                    len = 0;
                    jogo.gameOver = 1;
                    telaAtual = TELA_MENU;
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
    DescarregaTextureBarreira(&jogo);
    CloseWindow();
    return 0;
}
