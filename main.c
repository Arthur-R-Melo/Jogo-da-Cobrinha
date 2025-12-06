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
    TELA_JOGO,
    TELA_RANKING
} Tela;

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
    CarregaTextureBarreira(&jogo);
    int rankingFlag = 1;

    IniciaJogo(&jogo, 1);

    Tela telaAtual = TELA_MENU;

    while (!WindowShouldClose()){
        BeginDrawing();      
        ClearBackground(BLACK);
        
        if(telaAtual == TELA_MENU){
            desenhaDificuldade(&jogo);
            desenhaTamanhoTela(&jogo);
            desenhaCaixaNome(&jogo);
            if(desenhaBotaoRanking(&jogo)) telaAtual = TELA_RANKING;
            DrawText("MENU", LARGURA*jogo.resize/2 - 55, (ALTURA_JOGO*jogo.resize+BARRA_ALTURA)/2 - 325, 40, YELLOW);
            DrawText("PRESS ENTER TO START", LARGURA*jogo.resize/2 - 260, (ALTURA_JOGO*jogo.resize+BARRA_ALTURA)/2 + 150, 40, RED);
            
            if(IsKeyPressed(KEY_ENTER) ){
                if(jogo.nomeLength == 0){
                    jogo.flagAlertaNome = 1;
                }else{
                    IniciaFood(&jogo);
                    telaAtual = TELA_JOGO;
                }
            }

            if(jogo.flagAlertaNome){
                if(((int)(GetTime() * 2)) % 2 == 0){
                    DrawText("ESCREVA O SEU NOME", LARGURA*jogo.resize/2 - 180, (ALTURA_JOGO * jogo.resize + BARRA_ALTURA) / 2 - 250, 30, RED);
                }                
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
                if(rankingFlag) {
                    int indexRanking = isInRanking(jogo.dificuldade, jogo.pontuacao);
                    if (indexRanking) {
                        Player jogador;
                        strcpy(jogador.nome, jogo.nome);
                        jogador.pont = jogo.pontuacao;
                        addInRanking(jogo.dificuldade, jogador, indexRanking-1);
                    }
                    rankingFlag = 0;
                }
                
                
                DrawText("GAME OVER!", LARGURA*jogo.resize/2 - 130,  (ALTURA_JOGO*jogo.resize+BARRA_ALTURA)/2 - 150, 40, RED);
                DrawText(texto, LARGURA*jogo.resize/2 - 150,  (ALTURA_JOGO*jogo.resize+BARRA_ALTURA)/2 - 90, 30, WHITE);
                DrawText("Continue", LARGURA*jogo.resize/2 - 65,  (ALTURA_JOGO*jogo.resize+BARRA_ALTURA)/2 + 50, 30, WHITE);
                if (IsKeyPressed(KEY_ENTER)){
                    freeSnake(&(jogo.body));
                    IniciaJogo(&jogo, 0);
                    SetWindowSize(LARGURA*jogo.resize, ALTURA_JOGO*jogo.resize + BARRA_ALTURA);
                    jogo.gameOver = 1;
                    rankingFlag = 1;
                    telaAtual = TELA_MENU;
                }
            }
        }else if (telaAtual == TELA_RANKING) {
            if(desenhaRanking()) telaAtual = TELA_MENU;
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
