#include "graphic.h"
#include "coord.h"
#include "jogo.h"
#include "ranking.h"
#include "snake.h"

#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Funções para uso exclusivamente interno, por isso não estão no cabeçalho
void coordToPosition(Coord coord, float *x, float *y, float resizeFactor);
void rotateImage(Vector2 *vec, float *degree, int direction, float resize);
void rotateQuina(int pastDir, int newDir, Vector2 *vec, float *degree,
                 Rectangle *rec, float resize);

int desenhaRanking() {
  static int dificuldade = EASY_RANKING;
  char strDif[10];
  Color cor;

  if (IsKeyPressed(KEY_ENTER))
    return 1;
  int xButton = GetScreenWidth() / 2 - 70, yButton = 10;
  Vector2 p1 = {GetScreenWidth() / 2 - 100, yButton + 30};
  Vector2 p2 = {GetScreenWidth() / 2 - 80, yButton + 60};
  Vector2 p3 = {GetScreenWidth() / 2 - 80, yButton};
  Vector2 p4 = {GetScreenWidth() / 2 + 100, yButton + 30};
  Vector2 p5 = {GetScreenWidth() / 2 + 80, yButton + 60};
  Vector2 p6 = {GetScreenWidth() / 2 + 80, yButton};
  int h1 = CheckCollisionPointTriangle(GetMousePosition(), p1, p2, p3);
  int h2 = CheckCollisionPointTriangle(GetMousePosition(), p4, p5, p6);
  DrawRectangle(xButton, yButton, 140, 60, WHITE);
  if (h1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    dificuldade = (dificuldade + 2) % 3;
  if (h2 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    dificuldade = (dificuldade + 1) % 3;
  switch (dificuldade) {
  case EASY_RANKING:
    strcpy(strDif, "FÁCIL");
    cor = GREEN;
    break;
  case MEDIUM_RANKING:
    strcpy(strDif, "MÉDIA");
    cor = YELLOW;
    break;
  case HARD_RANKING:
  default:
    strcpy(strDif, "DIFÍCIL");
    cor = RED;
    break;
  }
  int txtLen = MeasureText(strDif, 36);
  DrawText(strDif, (GetScreenWidth() - txtLen) / 2, 22, 36, cor);
  Color cor1 = WHITE;
  Color cor2 = WHITE;
  if (h1)
    cor1 = RED;
  if (h2)
    cor2 = RED;
  DrawTriangle(p1, p2, p3, cor1);
  DrawTriangle(p6, p5, p4, cor2);

  Ranking r = getRanking(dificuldade);
  int fontSize = GetScreenHeight() / 20;
  int defY = 150, xTxtLen = MeasureText("_____ ___", fontSize);
  char txtPont[10];
  for (int i = 0; i < 10 && i < r.length; i++) {
    DrawText(r.jogadores[i].nome, GetScreenWidth() / 2 - xTxtLen - fontSize * 3,
             defY + (fontSize + 5) * i, fontSize, WHITE);
    sprintf(txtPont, "%d", r.jogadores[i].pont);
    DrawText(txtPont,
             GetScreenWidth() / 2 - MeasureText(txtPont, fontSize) -
                 fontSize * 3,
             defY + (fontSize + 5) * i, fontSize, WHITE);
  }
  for (int i = 10; i < r.length; i++) {
    DrawText(r.jogadores[i].nome, GetScreenWidth() / 2 + fontSize * 2,
             defY + (fontSize + 5) * (i % 10), fontSize, WHITE);
    sprintf(txtPont, "%d", r.jogadores[i].pont);
    DrawText(txtPont, GetScreenWidth() / 2 + xTxtLen + 10 + fontSize * 2,
             defY + (fontSize + 5) * (i % 10), fontSize, WHITE);
  }

  return 0;
}
int desenhaBotaoRanking(Jogo *j) {
  int x = LARGURA * j->resize / 2 - 70,
      y = (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 + 40;
  DrawRectangle(x, y, 140, 60, WHITE);
  DrawText("Ranking", LARGURA * j->resize / 2 - MeasureText("Ranking", 30) / 2,
           (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 + 55, 30, BLACK);
  int colision =
      CheckCollisionPointRec(GetMousePosition(), (Rectangle){x, y, 140, 60});
  if (colision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    return 1;
  return 0;
}

void desenhaCaixaNome(Jogo *j) {
  char *nome = j->nome;
  static bool typing = false;

  int caixaX = LARGURA * j->resize / 2 - 180;
  int caixaY = (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 190;
  int caixaW = 360;
  int caixaH = 60;

  if (CheckCollisionPointRec(GetMousePosition(),
                             (Rectangle){caixaX, caixaY, caixaW, caixaH})) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      typing = true;
  } else {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      typing = false;
  }

  if (typing) {
    int key = GetCharPressed();
    while (key > 0) {
      if (key >= 32 && key <= 125 && j->nomeLength < 5) {
        nome[j->nomeLength] = (char)key;
        j->nomeLength++;
        nome[j->nomeLength] = '\0';
      }
      key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && j->nomeLength > 0) {
      j->nomeLength--;
      nome[j->nomeLength] = '\0';
    }
  }

  DrawText("Nome:", LARGURA * j->resize / 2 - 280,
           (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 175, 30, WHITE);

  DrawRectangle(caixaX, caixaY, caixaW, caixaH, WHITE);
  DrawText(nome, caixaX + 10, caixaY + 15, 30, BLACK);
  DrawRectangleLines(caixaX, caixaY, caixaW, caixaH, typing ? YELLOW : BLACK);
}

void desenhaTamanhoTela(Jogo *j) {
  Vector2 p1 = {LARGURA * j->resize / 2 - 100,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 70};
  Vector2 p2 = {LARGURA * j->resize / 2 - 80,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 40};
  Vector2 p3 = {LARGURA * j->resize / 2 - 80,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 100};

  Vector2 p4 = {LARGURA * j->resize / 2 + 100,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 70};
  Vector2 p5 = {LARGURA * j->resize / 2 + 80,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 40};
  Vector2 p6 = {LARGURA * j->resize / 2 + 80,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 100};

  DrawRectangle(LARGURA * j->resize / 2 - 70,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 100, 140, 60,
                WHITE);

  bool hoverT1 = CheckCollisionPointTriangle(GetMousePosition(), p1, p2, p3);
  bool hoverT2 = CheckCollisionPointTriangle(GetMousePosition(), p4, p5, p6);

  if ((hoverT1 || hoverT2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (j->resize == STD_WIN_SIZE_FACTOR)
      j->resize = ALT_WIN_SIZE_FACTOR else j->resize = STD_WIN_SIZE_FACTOR;
    SetWindowSize(LARGURA * j->resize, ALTURA_JOGO * j->resize + BARRA_ALTURA);
  }
  Color c1 = WHITE, c2 = WHITE;

  if (j->resize == STD_WIN_SIZE_FACTOR) {
    int x = (LARGURA * j->resize -
             MeasureText(STD_SIZE_STR, WIN_SIZE_TXT_FONT_SIZE)) /
            2;
    DrawText(STD_SIZE_STR, x, (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 85,
             WIN_SIZE_TXT_FONT_SIZE, WIN_SIZE_TXT_COLOR);
  } else {
    int x = (LARGURA * j->resize -
             MeasureText(ALT_SIZE_STR, WIN_SIZE_TXT_FONT_SIZE)) /
            2;
    DrawText(ALT_SIZE_STR, x, (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 85,
             WIN_SIZE_TXT_FONT_SIZE, WIN_SIZE_TXT_COLOR);
  }

  if (hoverT1)
    c1 = RED;
  if (hoverT2)
    c2 = RED;
  DrawTriangle(p1, p2, p3, c1);
  DrawTriangle(p6, p5, p4, c2);
}

void desenhaDificuldade(Jogo *j) {
  Vector2 p1 = {LARGURA * j->resize / 2 - 100,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2};
  Vector2 p2 = {LARGURA * j->resize / 2 - 80,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 30};
  Vector2 p3 = {LARGURA * j->resize / 2 - 80,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 + 30};

  Vector2 p4 = {LARGURA * j->resize / 2 + 100,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2};
  Vector2 p5 = {LARGURA * j->resize / 2 + 80,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 30};
  Vector2 p6 = {LARGURA * j->resize / 2 + 80,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 + 30};

  DrawRectangle(LARGURA * j->resize / 2 - 70,
                (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 30, 140, 60,
                WHITE);

  bool hoverT1 = CheckCollisionPointTriangle(GetMousePosition(), p1, p2, p3);
  bool hoverT2 = CheckCollisionPointTriangle(GetMousePosition(), p4, p5, p6);

  if (hoverT1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (j->dificuldade > 0)
      j->dificuldade--;
    else
      j->dificuldade = 2;
  }

  if (hoverT2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (j->dificuldade < 2)
      j->dificuldade++;
    else
      j->dificuldade = 0;
  }

  switch (j->dificuldade) {
  case 0:
    DrawText("Fácil", LARGURA * j->resize / 2 - 40,
             (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 15, 35, GREEN);
    break;

  case 1:
    DrawText("Médio", LARGURA * j->resize / 2 - 45,
             (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 15, 35, ORANGE);
    break;

  case 2:
    DrawText("Difícil", LARGURA * j->resize / 2 - 45,
             (ALTURA_JOGO * j->resize + BARRA_ALTURA) / 2 - 15, 35, RED);
    break;

  default:
    break;
  }

  Color corT1 = WHITE;
  Color corT2 = WHITE;

  if (hoverT1)
    corT1 = RED;
  if (hoverT2)
    corT2 = RED;

  DrawTriangle(p3, p2, p1, corT1);
  DrawTriangle(p4, p5, p6, corT2);
}

void DesenhaBarreiras(Jogo *j) {

  for (int i = 0; i < j->quantBarreiras; i++) {
    float x, y;
    coordToPosition(j->posicoesBarreira[i], &x, &y, j->resize);
    Rectangle rec;
    rec.width = STD_SIZE_X * j->resize;
    rec.height = STD_SIZE_Y * j->resize;
    rec.x = x;
    rec.y = y;

    DrawTexturePro(j->barreira,
                   (Rectangle){0, 0, j->barreira.width, j->barreira.height},
                   rec, (Vector2){0, 0}, 0.0f, WHITE);
  }
}

void DesenhaBody(Jogo *j) {
  NodePointer temp = j->body.tail;
  float x, y;
  int pastDirection = j->body.head->direcao;
  Rectangle rec;
  while (temp) {
    coordToPosition(temp->coord, &x, &y, j->resize);
    float degree = 0.0f;
    Vector2 position = (Vector2){0, 0};
    rec.x = x;
    rec.y = y;
    rec.width = STD_SIZE_X * j->resize;
    rec.height = STD_SIZE_Y * j->resize;
    Rectangle src = (Rectangle){0, 0, STD_SIZE_X, STD_SIZE_Y};

    if (temp == j->body.head) {
      // DrawRectangleRec(rec, RED);
      rotateImage(&position, &degree, temp->direcao, j->resize);
      DrawTexturePro(j->cabeca,
                     (Rectangle){0, 0, j->cabeca.width, j->cabeca.height}, rec,
                     position, degree, WHITE);
    } else if (pastDirection != temp->direcao && temp != j->body.tail) {
      rotateQuina(pastDirection, temp->direcao, &position, &degree, &src,
                  j->resize);
      DrawTexturePro(j->quinaCobra, src, rec, position, degree, WHITE);
    } else if (temp == j->body.tail) {
      rotateImage(&position, &degree, temp->direcao, j->resize);
      DrawTexturePro(j->rabo, (Rectangle){0, 0, j->rabo.width, j->rabo.height},
                     rec, position, degree, WHITE);
    } else {
      rotateImage(&position, &degree, temp->direcao, j->resize);
      DrawTexturePro(j->corpo,
                     (Rectangle){0, 0, j->corpo.width, j->corpo.height}, rec,
                     position, degree, WHITE);
    }

    pastDirection = temp->direcao;
    temp = temp->prox;
  }
}

void DesenhaFood(Jogo *j) {
    float x, y;
    coordToPosition(j->food.coord, &x, &y, j->resize);

    float baseW = STD_SIZE_X * j->resize;
    float baseH = STD_SIZE_Y * j->resize;

    //animação//
    float pulse = sinf(GetTime() * 4) * 0.15f;
    float scale = 1.0f + pulse;

    Rectangle rec;
    rec.width  = baseW * scale;
    rec.height = baseH * scale;
    rec.x = x + (baseW - rec.width) / 2;
    rec.y = y + (baseH - rec.height) / 2;

    DrawTexturePro(
        j->foodTexture.texture,
        (Rectangle){0, 0, j->foodTexture.texture.width, j->foodTexture.texture.height},
        rec,
        (Vector2){0, 0},
        0.0f,
        WHITE
    );
}

void DesenhaBordas(Jogo *j) {
  // Desenha as barreiras nas bordas
  for (int i = 0; i < 4; i++) {
    DrawRectangleRec(j->bordas[i].pos, LIGHTGRAY);
  }
}

void DesenhaJogo(Jogo *j) {
  DesenhaBordas(j);
  DesenhaFood(j);
  DesenhaBody(j);

  if (j->dificuldade == 2) {
    DesenhaBarreiras(j);
  }
}

void coordToPosition(Coord coord, float *x, float *y, float resizeFactor) {
  *x = (float)(coord.x * 40 * resizeFactor + 10);
  *y = (float)(coord.y * 40 * resizeFactor + 50);
}

void CarregaTextureBarreira(Jogo *jogo) {
  jogo->barreira = LoadTexture("assets/trapSnake.png");
}

void DescarregaTextureBarreira(Jogo *jogo) { UnloadTexture(jogo->barreira); }

Texture2D CarregaTextureFundo(Jogo *jogo) {
  Texture2D fundo;
  if(jogo->dificuldade == 0){
    fundo = LoadTexture("assets/mapa1.png");
  }else if(jogo->dificuldade == 1){
    fundo = LoadTexture("assets/veaine.png");
  }else{
    fundo = LoadTexture("assets/sefuere.png");
  }
  return fundo;
}

void DescarregaTexturaFundo(Jogo *jogo, Texture2D fundo) {
  UnloadTexture(fundo);
}

void CarregaQuinaCobra(Jogo *jogo) {
  jogo->quinaCobra = LoadTexture("assets/curve.png");
}

void DescarregaQuinaCobra(Jogo *jogo) { UnloadTexture(jogo->quinaCobra); }

void CarregaCabeca(Jogo *jogo) {
  jogo->cabeca = LoadTexture("assets/head2.png");
}

void DescarregaCabeca(Jogo *jogo) { UnloadTexture(jogo->cabeca); }

void CarregaBody(Jogo *jogo) { jogo->corpo = LoadTexture("assets/body.png"); }

void DescarregaBody(Jogo *jogo) { UnloadTexture(jogo->corpo); }

void CarregaRabo(Jogo *jogo) { jogo->rabo = LoadTexture("assets/tail.png"); }

void DescarregaRabo(Jogo *jogo) { UnloadTexture(jogo->rabo); }

void CarregaTexturaComida(Jogo *jogo) {
  jogo->foodTexture.texture = LoadTexture("assets/apple.png");
  if (jogo->foodTexture.texture.id == 0) {
    printf("ERRO: Não foi possível carregar textura da comida!\n");
  }
}

void DescarregaTexturaComida(Jogo *jogo) {
  UnloadTexture(jogo->foodTexture.texture);
}

void rotateQuina(int pastDir, int newDir, Vector2 *vec, float *degree,
                 Rectangle *rec, float resize) {

  if (newDir == DIR_LEFT)
    rec->width *= -1;
  if (pastDir == DIR_DOWN)
    rec->height *= -1;
  if (pastDir == DIR_LEFT) {
    *degree = -90.0f;
    vec->x += STD_SIZE_X * resize;
    if (newDir == DIR_DOWN)
      rec->width *= -1;
  }
  if (pastDir == DIR_RIGHT) {
    *degree = 90;
    vec->y += STD_SIZE_Y * resize;
    if (newDir == DIR_UP)
      rec->width *= -1;
  }
}

void rotateImage(Vector2 *vec, float *degree, int direction, float resize) {

  if (direction == DIR_UP)
    return;

  if (direction == DIR_DOWN) {
    *degree = 180.0f;
    vec->x += STD_SIZE_X * resize;
    vec->y += STD_SIZE_Y * resize;

    return;
  }

  if (direction == DIR_LEFT) {
    *degree = -90.0f;
    vec->x += STD_SIZE_X * resize;

    return;
  }

  if (direction == DIR_RIGHT) {
    *degree = 90.0f;
    vec->y += STD_SIZE_Y * resize;

    return;
  }
}
