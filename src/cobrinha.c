#include "../include/structs.h"
#include "../include/cobrinha.h"
#include "../include/jogo.h"

#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"

void iniciarCobrinha(Cobra *cobra){
    cobra->tamanho_cobra = INITIAL_LENGTH;
    cobra->direcao_cobra = 'R';
    for (int i = 0; i < INITIAL_LENGTH; i++){
        cobra->corpo_cobra[i].x = INITIAL_LENGTH - i - 1;
        cobra->corpo_cobra[i].y = 0;
    }
}

void identificarSaidaDoJogo(Cobra *cobra, Jogo *jogo, Posicao *cabeca_cobra){
    if (cabeca_cobra->x < 0){
        cabeca_cobra->x = WIDTH - 1;
    }
    else if (cabeca_cobra->x >= WIDTH){ 
        cabeca_cobra->x = 0;
    }
    if (cabeca_cobra->y < 0){
        cabeca_cobra->y = HEIGHT - 1;
    }
    else if (cabeca_cobra->y >= HEIGHT){
        cabeca_cobra->y = 0;
    }
}

void identificarColisaoNaCobrinha(Cobra *cobra, int *pontos_jogo, Posicao *cabeca_cobra){
    for (int i = 0; i < cobra->tamanho_cobra; i++){
        if (cabeca_cobra->x == cobra->corpo_cobra[i].x && cabeca_cobra->y == cobra->corpo_cobra[i].y){
            screenClear();
            printf("\nVocê colidiu com o próprio corpo, perdeu! Pontuação final: %d\n", *pontos_jogo);
            exit(0);
        }
    }
}

void atualizarCobra(Cobra *cobra, Jogo *jogo, int *pontos_jogo){
    Posicao cabeca_cobra = cobra->corpo_cobra[0];
    switch (cobra->direcao_cobra){
        case 'U': 
            cabeca_cobra.y--; 
            break;
        case 'D': 
            cabeca_cobra.y++; 
            break;
        case 'L': 
            cabeca_cobra.x--; 
            break;
        case 'R': 
            cabeca_cobra.x++; 
            break;
    }
    
    identificarSaidaDoJogo(cobra, jogo, &cabeca_cobra);
    identificarColisaoNaCobrinha(cobra, pontos_jogo, &cabeca_cobra);
    
    for (int i = cobra->tamanho_cobra - 1; i > 0; i--){
        cobra->corpo_cobra[i] = cobra->corpo_cobra[i - 1];
    }
    cobra->corpo_cobra[0] = cabeca_cobra;
    
    if (cabeca_cobra.x == jogo->comida.x && cabeca_cobra.y == jogo->comida.y){
        cobra->tamanho_cobra++;
        (*pontos_jogo)++;
        acrescentarComida(jogo);
    }
}

void definirDirecaoCobra(int tecla, Cobra *cobra){
    switch(tecla){
        case 'w':
        case 'W':
            if(cobra->direcao_cobra != 'D'){
                cobra->direcao_cobra = 'U';
            } 
            break;

        case 's':
        case 'S':
            if(cobra->direcao_cobra != 'U'){
                cobra->direcao_cobra = 'D';
            }
            break;

        case 'a':
        case 'A':
            if(cobra->direcao_cobra != 'R'){
                cobra->direcao_cobra = 'L';
            }
            break;

        case 'd':
        case 'D':
            if(cobra->direcao_cobra != 'L'){
                cobra->direcao_cobra = 'R';
            }
            break;
    }
}
