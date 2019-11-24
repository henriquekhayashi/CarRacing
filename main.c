#include "carracing.h"
#include "display.h"

#define DEBUG 1

int main(){

    char matrix [TRUE_ROWS][COLUMNS];

    Carro jogador;

    jogador.i=ROWS-1;
    jogador.j=COLUMNS-3;
    jogador.height = 4; 
    jogador.width = 5;

    Carro competidor;

    competidor.i=0;
    competidor.j=COLUMNS-3;
    competidor.height = 4; 
    competidor.width = 5;

   /* CarroCompetidor a;

    a.i=&competidor.i;
    a.j=&competidor.j;*/

    //inicializando matriz
    init(matrix);
    int m;

    int tecla;
    
    int faixa1 = 0, faixa2 = 3, aux = 0;
    
    int troca;

    int game = 1;

    int cont=0;

    int velocidade=3;
    
    int posicao[3];

    //menu
    menu();

    //apagar o cursor da tela
    ShowConsoleCursor(0);
   
    system("cls");

    srand(time(NULL));

    random(&posicao);

    //loop
    while(game == 1){ 
    ShowConsoleCursor(0);
        
            gotoxy(0,0);
        
        //print posição do @
        #if DEBUG == 1
            printf("Competidor = (%d,%d)\n", competidor.i, competidor.j);
        #endif
            printf("FAIXA1 = %d, FAIXA2 = %d)\n", faixa1 , faixa2);
        
        

        //desenha o carro
        drawCar(matrix, &jogador, PIXEL);
        //desenhar inimigos
        drawEnemy(matrix, competidor, PIXEL, posicao);
        
        
        
        printMatrix(matrix, faixa1);
        
        if(collisionDetect(jogador, matrix) ){
            getch();
             game = 0;
        }
           //APAGAR
        drawCar(matrix, &jogador, EMPTY);
        drawEnemy(matrix, competidor, EMPTY, posicao);
        
       
        //m = getch();
        /*
        aux = faixa1;
        faixa1 = faixa2;
        faixa2 = aux;
        */

       /* if(faixa1 == 0) faixa1 = 1;
        else faixa1 = 0;*/

        
        
         if(cont%velocidade==0){
            //alternar animacao estrada
            if(faixa1 == 0) faixa1 = 1;
                else faixa1 = 0;

            //mover o competidor para baixo na tela
            competidor.i++;
            if(competidor.i==TRUE_ROWS+24){ 
                competidor.i = 0;     
                //sortear posicao dos inimigos
                random(&posicao);
            }
            }
        
        
      

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
                            if(jogador.j - jogador.width/2 > 1 )jogador.j-=6;
                            
                        break;
                        case RIGHT: 
                            if(jogador.j + jogador.width/2 < COLUMNS-1)jogador.j+=6;
                        break;
                    }
            break;
            case TECLA_A: 
                if(jogador.j - jogador.width/2 > 1 )jogador.j-=6;
                            
            break;
            case TECLA_D: 
                if(jogador.j + jogador.width/2 < COLUMNS-1)jogador.j+=6;
            
            case 'v':
                if(velocidade==3){
                    velocidade = 1;
                }else{
                    velocidade = 3;
                }
            break;
        }

    // sair com esc
    if (tecla == ESC) break;

    //apaga tecla
    tecla = 0;

    cont++;
    }


    //gotoxy(0,0);
    system("cls");
    gameOver();
    system("pause");

    return 0;
}