#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

typedef struct{
    int x, y;
} Ponto;

typedef struct{
    Ponto *corpo;
    int tamanho;
    int capacidade;
    int velocidade;
} Cobra;

typedef struct{
    Ponto posicao;
} Comida;

void moverCursor(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
}
void exibirCobra(Cobra *cobra){
    for (int i = 0; i < cobra->tamanho; i++){
        moverCursor(cobra->corpo[i].x, cobra->corpo[i].y);
        printf("%c", 219);
    }
}
void limparCobra(Cobra *cobra){
    for (int i = 0; i < cobra->tamanho; i++){
        moverCursor(cobra->corpo[i].x, cobra->corpo[i].y);
        printf(" ");
    }
}
void atualizarPosicaoCobra(Cobra *cobra){
    for (int i = cobra->tamanho - 1; i > 0; i--){
        cobra->corpo[i] = cobra->corpo[i - 1];
    }
}
int verificarBatidaNoCorpo(Cobra *cobra){
    for (int i = 1; i < cobra->tamanho; i++) {
        if (cobra->corpo[0].x == cobra->corpo[i].x && cobra->corpo[0].y == cobra->corpo[i].y){
            return 1;
        }
    }
    return 0;
}
void gerarComida(Comida *comida){
    moverCursor(comida->posicao.x, comida->posicao.y);
    printf(" ");
    srand(time(NULL));
    comida->posicao.x = (rand() % 48) + 1;
    comida->posicao.y = (rand() % 18) + 1;
    moverCursor(comida->posicao.x, comida->posicao.y);
    printf("%c", 4);
}
void desenharCampo() {
    for (int i = 0; i < 50; i++){
        moverCursor(i, 0);
        printf("%c", 219);
        Sleep(5);
    }
    for (int i = 0; i < 20; i++){
        moverCursor(50, i);
        printf("%c", 219);
        Sleep(5);
    }
    for (int i = 50; i >= 0; i--){
        moverCursor(i, 20);
        printf("%c", 219);
        Sleep(5);
    }
    for (int i = 20; i >= 0; i--){
        moverCursor(0, i);
        printf("%c", 219);
        Sleep(5);
    }
}
void inicializarCobra(Cobra *cobra){
    cobra->capacidade = 5;
    cobra->tamanho = 1;
    cobra->velocidade = 150;
    cobra->corpo = (Ponto*) malloc(cobra->capacidade * sizeof(Ponto));
    cobra->corpo[0].x = 2;
    cobra->corpo[0].y = 2;
}
void aumentarCobra(Cobra *cobra){
    if (cobra->tamanho == cobra->capacidade){
        cobra->capacidade *= 2;
        cobra->corpo = (Ponto*) realloc(cobra->corpo, cobra->capacidade * sizeof(Ponto));
    }
    cobra->tamanho++;
}

void liberarCobra(Cobra *cobra){
    free(cobra->corpo);
}

int main() {
    system("cls");
    Cobra cobra;
    Comida comida = {{0, 0}};
    inicializarCobra(&cobra);
    int perdeu = 0;
    char tecla = 'd';
    desenharCampo();
    gerarComida(&comida);
    exibirCobra(&cobra);

    while (perdeu == 0){
        moverCursor(52, 2);
        printf("    Pontos = %d\t", cobra.tamanho - 1);
        moverCursor(52, 4);
        printf("    Desenvolvido por grupo rua da moeda");
        limparCobra(&cobra);
        atualizarPosicaoCobra(&cobra);

        if (tecla == 'w' || tecla == 'W' || tecla == 72){
            cobra.corpo[0].y--;
            if (cobra.corpo[0].y == 0) break;
        }
        if (tecla == 's' || tecla == 'S' || tecla == 80){
            cobra.corpo[0].y++;
            if (cobra.corpo[0].y == 20) break;
        }
        if (tecla == 'a' || tecla == 'A' || tecla == 75){
            cobra.corpo[0].x--;
            if (cobra.corpo[0].x == 0) break;
        }
        if (tecla == 'd' || tecla == 'D' || tecla == 77){
            cobra.corpo[0].x++;
            if (cobra.corpo[0].x == 50) break;
        }
        if (cobra.corpo[0].x == comida.posicao.x && cobra.corpo[0].y == comida.posicao.y){
            aumentarCobra(&cobra);
            if (cobra.velocidade > 50){
                cobra.velocidade -= 10;
            }
            gerarComida(&comida);
        }
        perdeu = verificarBatidaNoCorpo(&cobra);
        exibirCobra(&cobra);
        moverCursor(50, 20);
        Sleep(cobra.velocidade);

        if (kbhit()){
            tecla = getch();
        }
    }

    system("cls");
    printf("Game over!!!!!! e seus pontos foram %d\n", cobra.tamanho - 1);
    system("pause");
    liberarCobra(&cobra);
    return 0;
}