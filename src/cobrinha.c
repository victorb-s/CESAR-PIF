#ifndef STRUCTS_H
#define STRUCTS_H

#include "config.h"

typedef struct {
    int x, y;
} Posicao;

typedef struct {
    Posicao corpo_cobra[WIDTH * HEIGHT];
    int tamanho_cobra;
    char direcao_cobra;
} Cobra;

typedef struct {
    Posicao comida;
} Jogo;

#endif