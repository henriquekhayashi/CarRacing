#include "carracing.h"
#include "display.h"
#include <windows.h>
#define DEBUG 1

int main(){

    char matrix [TRUE_ROWS][COLUMNS];

    Carro jogador;

    jogador.i=ROWS-1;
    jogador.j=COLUMNS/2;
    jogador.height = 4; 
    jogador.width = 5;

    Carro competidor;

    competidor.i=0;
    competidor.j=COLUMNS-3;
    competidor.height = 4; 
    competidor.width = 5;

    //inicializando matriz
    init(matrix);
    int m;

    int tecla;
    
    int faixa1 = 0, faixa2 = 3, aux = 0;
    
    int troca;

    //apagar o cursor da tela
    ShowConsoleCursor(0);
   
    system("cls");

    //loop
    while(1){ 
        
        
            gotoxy(0,0);
        
        //print posição do @
        #if DEBUG == 1
            printf("Competidor = (%d,%d)\n", competidor.i, competidor.j);
        #endif
            printf("FAIXA1 = %d, FAIXA2 = %d)\n", faixa1 , faixa2);
        
        //desenha o carro
        drawCar(matrix, &jogador, PIXEL);
        drawCar(matrix, &competidor, PIXEL);
        
        
        printMatrix(matrix, faixa1);
        
        //APAGAR
        drawCar(matrix, &jogador, EMPTY);
        drawCar(matrix, &competidor, EMPTY);
        //m = getch();
        /*
        aux = faixa1;
        faixa1 = faixa2;
        faixa2 = aux;
        */

        if(faixa1 == 0) faixa1 = 1;
        else faixa1 = 0;

        //mover o competidor para baixo na tela 
        competidor.i++;
        if(competidor.i==TRUE_ROWS) competidor.i = 0;

        //int tecla;

        if(kbhit()){
            tecla = getch();
            }

        //Mover o carro
        switch(tecla){
            case ARROWS: 
                if(kbhit()) tecla = getch();
                    switch(tecla){
                        case LEFT: 
                            if(jogador.j - jogador.width/2 > 1 )jogador.j-=3;
                            else if(jogador.j - jogador.width/2 > 0 ) jogador.j--;
                        break;
                        case RIGHT: 
                            if(jogador.j + jogador.width/2 < COLUMNS-1)jogador.j+=3;
                        break;
                    }
            break;
            case TECLA_A: 
                if(jogador.j - jogador.width/2 > 1 )jogador.j-=3;
                            else if(jogador.j - jogador.width/2 > 0 ) jogador.j--;
            break;
            case TECLA_D: 
                if(jogador.j + jogador.width/2 < COLUMNS-1)jogador.j+=3;
        
    }

    // sair com esc
    if (tecla == ESC) break;

    //apaga tecla
    tecla = 0;

    
    }

    return 0;
}