#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "jogo.h"

#define SNAKE_COLOR YELLOW

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

#endif
