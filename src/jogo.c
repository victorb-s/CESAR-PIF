#include <stdio.h>
#include "../include/structs.h"
#include "../include/config.h"
#include "../include/jogo.h"
#include "../include/extras.h"
#include "../include/comida.h"
#include "../include/cobrinha.h"

#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"

void iniciarJogo(Cobra *cobra, Jogo *jogo){
    iniciarCobrinha(cobra);
    acrescentarComida(jogo);
}

void iniciarQuadradoDoJogo(Cobra *cobra, Jogo *jogo, int *pontos_jogo){
    screenClear();
    exibirBordas();

    for (int y = 0; y < HEIGHT; y++){
        printf("||");
        for (int x = 0; x < WIDTH; x++){
            int parte_cobra = 0;
            for (int z = 0; z < cobra->tamanho_cobra; z++) {
                if (cobra->corpo_cobra[z].x == x && cobra->corpo_cobra[z].y == y){
                    printf("0");
                    parte_cobra = 1;
                    break;
                }
            }
            if (!parte_cobra){
                if (jogo->comida.x == x && jogo->comida.y == y){
                    printf("1");
                } else {
                    printf(" ");
                }
            }
        }
        printf("||\n");
    }

    exibirBordas();
    exibirPontuacao(pontos_jogo);
}

void executarJogo(int tecla, Cobra *cobra, Jogo *jogo, int *pontos_jogo){
    while (tecla != 32){
        if (keyhit()){
            tecla = readch();
            definirDirecaoCobra(tecla, cobra);
        }

        if (timerTimeOver() == 1){
            atualizarCobra(cobra, jogo, pontos_jogo);
            iniciarQuadradoDoJogo(cobra, jogo, pontos_jogo);
        }
    }
}
