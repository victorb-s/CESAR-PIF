#ifndef COBRINHA_H
#define COBRINHA_H

#include "structs.h"
#include "jogo.h"

void iniciarCobrinha(Cobra *cobra);
void identificarSaidaDoJogo(Cobra *cobra, Jogo *jogo, Posicao *cabeca_cobra);
void identificarColisaoNaCobrinha(Cobra *cobra, int *pontos_jogo, Posicao *cabeca_cobra);
void atualizarCobra(Cobra *cobra, Jogo *jogo, int *pontos_jogo);
void definirDirecaoCobra(int tecla, Cobra *cobra);

#endif
