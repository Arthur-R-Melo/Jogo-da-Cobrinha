#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "jogo.h"

#define SNAKE_COLOR YELLOW
#define STD_SIZE_STR "660x700"
#define ALT_SIZE_STR "825x865"
#define WIN_SIZE_TXT_COLOR DARKGRAY
#define WIN_SIZE_TXT_FONT_SIZE 30

void DesenhaBody(Jogo *j);
void DesenhaFood(Jogo *j);
void DesenhaBordas(Jogo *j);
void DesenhaJogo(Jogo *j);
void CarregaTexturaComida(Jogo *jogo);
void DescarregaTexturaComida(Jogo *jogo);
Texture2D CarregaTextureFundo(Jogo *jogo);
void DescarregaTexturaFundo(Jogo* jogo, Texture2D fundo);
void CarregaQuinaCobra(Jogo* jogo);
void DescarregaQuinaCobra(Jogo* jogo);
void CarregaCabeca(Jogo* jogo);
void DescarregaCabeca(Jogo* jogo);
void CarregaBody(Jogo* jogo);
void DescarregaBody(Jogo* jogo);
void CarregaRabo(Jogo* jogo);
void DescarregaRabo(Jogo* jogo);
void desenhaDificuldade(Jogo* j);
void DesenhaBarreiras(Jogo *j);
void CarregaTextureBarreira(Jogo *jogo);
void DescarregaTextureBarreira(Jogo *jogo);
void desenhaTamanhoTela(Jogo *Jogo);
void desenhaCaixaNome(Jogo* j);

#endif
