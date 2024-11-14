#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"

#define WIDTH 60
#define HEIGHT 30
#define INITIAL_LENGTH 3

typedef struct{
    int x, y;
} Posicao;
typedef struct{
    Posicao corpo_cobra[WIDTH*HEIGHT];
    int tamanho_cobra;
    char direcao_cobra;
} Cobra;
typedef struct{
    Posicao comida;
} Jogo;

void inicializarComida(Jogo *jogo){
    jogo->comida.x = rand() % WIDTH;
    jogo->comida.y = rand() % HEIGHT;
}

void inicializarCobra(Cobra *cobra){
    cobra->tamanho_cobra = INITIAL_LENGTH;
    cobra->direcao_cobra = 'R';

    for(int i = 0; i < INITIAL_LENGTH; i++){
        cobra->corpo_cobra[i].x = INITIAL_LENGTH - i - 1;
        cobra->corpo_cobra[i].y = 0;
    }
}

void inicializarJogo(Cobra *cobra, Jogo *jogo, int *pontos_jogo){
    pontos_jogo = 0;
    inicializarCobra(cobra);
    inicializarComida(jogo);
}

void exibirBordas() {
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("-");
    }
    printf("\n");
}

void exibirPontuacao(int *pontos_jogo) {
    screenSetBold();
    printf("Pontuação do jogador: %d\n", *pontos_jogo);
    screenSetBold();
}

void desenharJogo(Cobra *cobra, Jogo *jogo, int *pontos_jogo) {
    screenClear();

    exibirBordas();

    for(int y = 0; y < HEIGHT; y++){
        printf("||");
        for (int x = 0; x < WIDTH; x++){
            int parte_cobra = 0;
            for (int z = 0; z < cobra->tamanho_cobra; z++){
                if (cobra->corpo_cobra[z].x == x && cobra->corpo_cobra[z].y == y){
                    printf("0");
                    parte_cobra = 1;
                    break;
                }
            }
            if (!parte_cobra) {
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

void identificarColisao(Cobra *cobra, int *pontos_jogo, Posicao *cabeca_cobra){
    if(cabeca_cobra->x < 0 || cabeca_cobra->x >= WIDTH || cabeca_cobra->y < 0 || cabeca_cobra->y >= HEIGHT){
        printf("\nJogo finalizado! Sua pontuação foi de: %d, parabéns!\n", *pontos_jogo);
        exit(0);
    }

    for(int i = 0; i < cobra->tamanho_cobra; i++){
        if(cabeca_cobra->x == cobra->corpo_cobra[i].x && cabeca_cobra->y == cobra->corpo_cobra[i].y){
            printf("\nVocê colidiu com o próprio corpo, perdeu! Pontuação final: %d\n", *pontos_jogo);
            exit(0);
        }
    }
}

void atualizarCobra(Cobra *cobra, Jogo *jogo, int *pontos_jogo){
    Posicao cabeca_cobra = cobra->corpo_cobra[0];
    switch(cobra->direcao_cobra){
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

    identificarColisao(cobra, pontos_jogo, &cabeca_cobra);

    for (int i = cobra->tamanho_cobra - 1; i > 0; i--) {
        cobra->corpo_cobra[i] = cobra->corpo_cobra[i - 1];
    }
    cobra->corpo_cobra[0] = cabeca_cobra;

    if (cabeca_cobra.x == jogo->comida.x && cabeca_cobra.y == jogo->comida.y) {
        cobra->tamanho_cobra++;
        (*pontos_jogo)++;
        jogo->comida.x = rand() % WIDTH;
        jogo->comida.y = rand() % HEIGHT;
    }
}

void definirDirecaoCobra(int tecla, Cobra *cobra) {
    switch(tecla){
    case 'w':
        if(cobra->direcao_cobra != 'D'){
            cobra->direcao_cobra = 'U';
        }
        break;

    case 's':
        if(cobra->direcao_cobra != 'U'){
            cobra->direcao_cobra = 'D';
        }
        break;

    case 'a':
        if(cobra->direcao_cobra != 'R'){
            cobra->direcao_cobra = 'L';
        }
        break;

    case 'd':
        if(cobra->direcao_cobra != 'L'){
            cobra->direcao_cobra = 'R';
        }
        break;
    }
}

void executarJogo(int tecla, Cobra *cobra, Jogo *jogo, int *pontos_jogo){
    while (tecla != 10) { 
        if (keyhit()) {
            tecla = readch();
            definirDirecaoCobra(tecla, cobra);
        }

        if (timerTimeOver() == 1) {
            atualizarCobra(cobra, jogo, pontos_jogo);
            desenharJogo(cobra, jogo, pontos_jogo);
        }
    }
}

int main() {
    Cobra cobra;
    Jogo jogo;
    int pontos_jogo = 0;
    int tecla = 0;

    screenInit(1);
    keyboardInit();
    timerInit(150);
    inicializarComida(&jogo);
    inicializarJogo(&cobra, &jogo, &pontos_jogo);
    desenharJogo(&cobra, &jogo, &pontos_jogo);
    executarJogo(tecla, &cobra, &jogo, &pontos_jogo);
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;

}
