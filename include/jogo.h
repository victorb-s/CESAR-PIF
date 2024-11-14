#ifndef JOGO_H
#define JOGO_H

#include "structs.h"
#include "cobrinha.h"
#include "comida.h"

void iniciarJogo(Cobra *cobra, Jogo *jogo);
void iniciarQuadradoDoJogo(Cobra *cobra, Jogo *jogo, int *pontos_jogo);
void executarJogo(int tecla, Cobra *cobra, Jogo *jogo, int *pontos_jogo);

#endif
