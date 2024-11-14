#include <stdlib.h>
#include <time.h>
#include "../include/structs.h"
#include "../include/comida.h"

#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"

void acrescentarComida(Jogo *jogo) {
    srand(time(NULL));
    jogo->comida.x = rand() % (WIDTH - 2) + 1;
    jogo->comida.y = rand() % (HEIGHT - 2) + 1;
}
