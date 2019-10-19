#include "carracing.h"
#include "display.h"
#include <windows.h>
#define DEBUG 0

int main(){

    char matrix [ROWS][COLUMNS];

    Carro jogador;

    jogador.i=ROWS-1;
    jogador.j=COLUMNS/2;
    jogador.height = 4; 
    jogador.width = 5;

    Carro competidor;

    competidor.i=0;
    competidor.j=COLUMNS/2;
    competidor.height = 4; 
    competidor.width = 5;

    //inicializando matriz
    init(matrix);
    int m;

    int tecla;
    
    int faixa1 = PIXEL, faixa2 = EMPTY, aux;
    
    int troca;

    //apagar o cursor da tela
    ShowConsoleCursor(0);
   
    system("cls");

     while(1){ 
        
        
            gotoxy(0,0);
        
        //print posição do @
        #if DEBUG == 1
            printf("@ = (%d,%d)\n", jogador.i, jogador.j);
        #endif
        
        
        //desenha o carro
        drawCar(matrix, &jogador, PIXEL);
        drawCar(matrix, &competidor, PIXEL);
        
       // Sleep(100);
        printMatrix(matrix, faixa1, faixa2);
        
        //APAGAR
        drawCar(matrix, &jogador, EMPTY);
        drawCar(matrix, &competidor, EMPTY);

        
        aux = faixa1;
        faixa1 = faixa2;
        faixa2 = aux;
        

        

        competidor.i++;
        if(competidor.i>ROWS+competidor.height) competidor.i = 0;

        
        int tecla;

        if(kbhit()){
            tecla = getch();
            }

        //MOVER
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