#include "carracing.h"
#include "display.h"

#define DEBUG 0

int main(){

    char matrix [ROWS][COLUMNS];

    begin:;

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

    Carro futuro;

    futuro.i=ROWS-1;
    futuro.j=COLUMNS-3;
    futuro.height = 4; 
    futuro.width = 5;

    
    Carro competidorfut;

    competidorfut.i=0;
    competidorfut.j=COLUMNS-3;
    competidorfut.height = 4; 
    competidorfut.width = 5;

    Score score;
    score.pontos = 0;

 

    //inicializando matriz
    
    init(matrix);

    int m;

    int tecla;
    
    int faixa1 = 0, faixa2 = 3, aux = 0;
    
    int troca;

    int game;

    int cont=0;

    int contfase =0;

    int velocidade=3;
    
    int posicao[3];

    int fase = 1;

    char nome[30];

   int collision;

    //apagar o cursor da tela
    
    ShowConsoleCursor(0);
    system("cls");
    srand(time(NULL));

    
    //verifica se existe um jogo previamente salvo
    if(!(game=abrirSave(&jogador, &competidor, posicao, &score, &contfase))){
        //mostra o menu
         menu(&game);

        system("cls");

        //pede o nome do jogador
         printf("\n\n\n\t\t\tDigite seu nome:");
         fgets(nome, 30, stdin);

         fflush(stdin);

         sscanf(nome, "%30s ", score.nome);

         

        //sorteia as posições inicais dos inimigos
        random(&posicao);
    }else {
        futuro = jogador ;
        competidorfut = competidor;
    }



    system("cls");

    collision = 0;
    
    //loop do jogo
    while(game == 1){ 

    ShowConsoleCursor(0);
        
            gotoxy(0,0);
        
        //Debug
        #if DEBUG == 1
            printf("Competidor = (%d,%d) | cont: %d\n", competidor.i, competidor.j, cont);
            printf("FAIXA1 = %d, FAIXA2 = %d)", faixa1 , faixa2);
        #endif

        //desenha o carro
        drawCar(matrix, &jogador, PIXEL);
        //desenhar inimigos
        drawEnemy(matrix, competidor, PIXEL, posicao);
        
        //mostrar a matriz
        printMatrix(matrix, faixa1);
        
        if(collision != 1)
        collision = collisionCheck(jogador, matrix);
        if( collision){
            getch();
             game = 0;
        }

        //mostrar score e fase
        gotoxy(0,0);
        printf("\n\n\t\t\t\t\t\t\t\t\tSCORE: %d \n", score.pontos*50);
        printf("\t\t\t\t\t\t\t\t\tJOGADOR: %s \n", score.nome);
        printf("\t\t\t\t\t\t\t\t\tFASE: %d ", fase);

      
    
        
        //verifica velocidade
        if(cont%velocidade==0){

            //receber pontuação
            if(competidor.i==ROWS+3) score.pontos++;
            else if(competidor.i==ROWS+17) score.pontos++;
            else if(competidor.i==ROWS+31) score.pontos++;
            
            //alternar animacao borda da estrada
            if(faixa1 == 0) faixa1 = 1;
                else faixa1 = 0;

            //mover o competidor para baixo na tela
            competidorfut.i++;
            if(competidor.i==ROWS+32){ 

                //resetar posição do inimigo para o começo
                competidorfut.i = 0;  

                //sortear posição dos inimigos
                random(&posicao);
            
            }


            contfase++;
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
                           if(jogador.j - jogador.width/2 > 1 ){
                            collision = collisionCheckSides(jogador, matrix, tecla);
                            futuro.j-=6;
                            }
                        case RIGHT: 
                            if(jogador.j + jogador.width/2 < COLUMNS-1){
                                collision = collisionCheckSides(jogador, matrix, tecla);
                                futuro.j+=6;
                            }
                        break;
                    }
            break;
            case TECLA_AUP: 
            case TECLA_A: 
                if(jogador.j - jogador.width/2 > 1 ){
                            collision = collisionCheckSides(jogador, matrix, tecla);
                            futuro.j-=6;
                }          
            break;
            case TECLA_DUP: 
            case TECLA_D: 
                if(jogador.j + jogador.width/2 < COLUMNS-1){
                                collision = collisionCheckSides(jogador, matrix, tecla);
                                futuro.j+=6;
                }
            break;

            //acelerar o carro    
            case SPACE:

                    if(contfase < 800) 
                    if(velocidade==3){
                        velocidade = 1;
                    }else velocidade = 3;
                
            break;
        }

        //APAGAR
        drawCar(matrix, &jogador, EMPTY);
        drawEnemy(matrix, competidor, EMPTY, posicao);

       

    // sair com esc
    if (tecla == ESC){
        salvarJogo(jogador, competidor, posicao, score, contfase);
         return 0;
    }
    //Atualizar posição dos carros
     jogador = futuro;
     competidor = competidorfut;

    //apaga tecla
    tecla = 0;

    cont++;

    if(contfase > 800){
    velocidade = 1;
    fase = 2;
    }
    
    }


    
    system("cls");
    gameOver(score);
    goto begin;

    system("pause");

    return 0;
}