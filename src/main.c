#include <stdio.h>
#include <stdlib.h>
#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"
#include "../include/jogo.h"

int main() {
    Cobra cobra;
    Jogo jogo;
    int pontos_jogo = 0;
    int tecla = 0;

    screenInit(1);
    keyboardInit();
    timerInit(150);
    iniciarJogo(&cobra, &jogo);
    iniciarQuadradoDoJogo(&cobra, &jogo, &pontos_jogo);
    executarJogo(tecla, &cobra, &jogo, &pontos_jogo);
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
