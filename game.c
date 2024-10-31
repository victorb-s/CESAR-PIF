#include<stdio.h>
#include<stdlib.h> //função srand() e system()
#include<windows.h> //função SetConsoleCursorPosition()
#include<conio.h> //função getch() e kbhit()
#include<time.h> //função rand()

int c[300][2], ponto = 1, cx = 2, cy = 2,comida[2], velo = 150;

void moverCursor(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x,y});
}

void exibirDesenho(){
    for(int i = 0; i < ponto; i++){
        moverCursor(c[i][0], c[i][1]);
        printf("%c",219);
    }
}

void upPositionCobra(){
    moverCursor(c[ponto][0],c[ponto][1]);
    printf(" ");
    for(int i = ponto; i > 0; i--){
    c[i][0] = c[i - 1][0];
    c[i][1] = c[i - 1][1];
    }
}

int verificarBatidaNoCorpo(){
    int retorno = 0;
    for(int i = 1; i < ponto; i++){
        if(cx == c[i][0] && cy == c[i][1]){
            retorno = 1;
        }
    }
    return retorno;
}

void gerarComida(){
    moverCursor(comida[0],comida[1]);
    printf(" ");
    srand(time(NULL));
    comida[0] = (rand() % 48) + 1;
    comida[1] = (rand() % 18) + 1;
    moverCursor(comida[0], comida[1]);
    printf("%c", 4); //mostra a comida na posição que é gerada

}

int main(){
    system("cls");//Explicação lá em baixo
    int perdeu = 0;
    char tecla;

    for(int i = 0; i < 50; i++){//teto

        moverCursor(i,0);
        printf("%c", 219);
        Sleep(5);//vai pausar o jogo por 5 milissegundos pra ficar mais natural o game

    }
    for(int i = 0; i < 20; i++){//parede da direita
        moverCursor(50,i);
        printf("%c",219);
        Sleep(5);
    }
    for(int i = 50; i >= 0; i--){//chão
        moverCursor(i,20);
        printf("%c", 219);
        Sleep(5);
    }
    for(int i = 20; i >= 0;i--){
        moverCursor(0,i);
        printf("%c", 219);
        Sleep(5);

    }
    gerarComida();
    exibirDesenho();
    tecla = 'd'; // vai começar se movendo pra direita

    while(perdeu == 0){
    
        moverCursor(52,2);
        printf("Pontos = %d\t",ponto);
        moverCursor(52,4);
        printf("Desenvolvido por grupo rua da moeda");
        c[0][0] = cx;
        c[0][1] = cy;
        
        if(kbhit()){
            tecla = getch();
        }
        if(tecla == 'w' || tecla == 'W' || tecla == 72){
            cy--; 
            if( cy == 0) break;//Bateu em cima é f
        }
        if(tecla == 's' || tecla == 'S' || tecla == 80){
            cy++; 
            if( cy == 20) break;//Bateu em baixo é f
        }
        if(tecla == 'a' || tecla == 'A' || tecla == 75){
            cx--;
            if(cx == 0) break;//Bateu na esquerda é f
        }
        if(tecla == 'd' || tecla == 'D' || tecla == 77){
            cx++;
            if(cx == 50) break;//Bateu na direita é f
        }
        if(cx == comida[0] && cy == comida[1]){//se a cobra comeu
            ponto++;
            if(velo > 50){
                velo -= 10; // a velocidade cai pq se não fica tenso pra jogar com ela qnd ficar grande
            }
            gerarComida();

        }
        perdeu = verificarBatidaNoCorpo();
        upPositionCobra();
        exibirDesenho();
        moverCursor(50,20);
        Sleep(velo);

    }
    system("cls");//quando perde o sistema ja limpa o console no automático
    printf("Você perdeu!!!!!! e sua pontuação foi %d \n",ponto);
    system("pause");
}