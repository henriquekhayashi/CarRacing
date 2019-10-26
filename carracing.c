/*
Jogo interativo tetris implementado em linguagem c para uso 
no console (terminal de comando)

autor:Henrique
data:19/09/2019

*/

#include "carracing.h"

/*
    Inicializa a matriz principal com 'espaços vazios'

*/

void init(char matrix[TRUE_ROWS][COLUMNS])
{
    int i,j;

    for(i=0; i<TRUE_ROWS; i++)
    {
        for(j=0; j<COLUMNS; j++)
        {
            matrix[i][j] = ' ';
        }   
    }
}

/*
    Mostra o conteúdo da matriz principal na tela
    do computador.
*/

void printMatrix(char matrix[TRUE_ROWS][COLUMNS],int faixa1)
{
    int i,j;
    //borda de cima
    printf("\n");
    printf("\t\t\t\t\t");
     for(j=0; j<COLUMNS+4; j++)
        {
           printf("*");
        }

    printf("\n");

    //correr pelo y da matriz
    for(i=0; i<ROWS; i++)
    {
        //print borda esquerda
        printf("\t\t\t\t\t");
        printf("*");
        if(i%2==faixa1)printf("%c", 178);
        else printf(" ");

        //correr pelo x da matriz
        for(j=0; j<COLUMNS; j++)
        {
            //print mapa
            printf("%c", matrix[i][j]);
        }

        //print borda direita
        if(i%2==faixa1)printf("%c", 178);
        else printf(" ");
        printf("*");  

        printf("\n");
    }

    //print borda debaixo
    printf("\t\t\t\t\t");
    for(j=0; j<COLUMNS+4; j++)
        {
            
           printf("*");
           
        }
    }

//desenhar carro

    void drawCar(char matrix[TRUE_ROWS][COLUMNS], Carro *barra, int simbolo){

        matrix[barra->i][barra->j] = simbolo;
         matrix[barra->i][barra->j+1] = simbolo;
         matrix[barra->i][barra->j-1] = simbolo;
         matrix[barra->i][barra->j+2] = simbolo;
         matrix[barra->i][barra->j-2] = simbolo;
        if(barra->i-1>=0 && barra->i-1<=ROWS-1) matrix[barra->i-1][barra->j] = simbolo;
        if(barra->i-2>=0 && barra->i-2<=ROWS-1) matrix[barra->i-2][barra->j] = simbolo;
        if(barra->i-3>=0 && barra->i-3<=ROWS-1) matrix[barra->i-3][barra->j] = simbolo;
        
        if(barra->i-2>=0 && barra->i-2<=ROWS-1){matrix[barra->i-2][barra->j+1] = simbolo;
        matrix[barra->i-2][barra->j-1] = simbolo;
        matrix[barra->i-2][barra->j+2] = simbolo;
        matrix[barra->i-2][barra->j-2] = simbolo;
        }
    }
        
       
