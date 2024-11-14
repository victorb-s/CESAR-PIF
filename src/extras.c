#include <stdio.h>
#include "../include/structs.h"
#include "../include/extras.h"

#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"

void exibirBordas(){
    for (int i = 0; i < WIDTH + 2; i++){
        printf("=");
    }
    printf("\n");
}

void exibirPontuacao(int *pontos_jogo){
    printf("Pontuação: %d\n", *pontos_jogo);
}
