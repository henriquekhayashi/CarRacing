/*
Jogo interativo tetris implementado em linguagem c para uso 
no console (terminal de comando)

autor:Henrique
data:19/09/2019

*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//Configuração das dimensoes da matriz principal do jogo
#define COLUMNS 11
#define ROWS 30

//Configuração de teclas
#define ESC 27
#define ARROWS 224
#define LEFT 75
#define RIGHT 77
#define TECLA_A 97
#define TECLA_D 100

//Configurações de layou
#define PIXEL 178
#define EMPTY 32


//Estrutura padrão de componentes
typedef struct{
    int i; //posição linhas da matriz
    int j; //posição colunas matriz
    
    //int tipo; // o tipo de 7 possiveis

    int width; //largura
    int height; //altura
}Carro;


/*
    Inicializa a matriz principal com 'espaços vazios'

*/
void init(char matrix[ROWS][COLUMNS]);

/*
    Mostra o conteúdo da matriz principal na tela
    do computador.
*/
void printMatrix(char matrix[ROWS][COLUMNS], int faixa1);

void drawCar(char matrix[ROWS][COLUMNS], Carro *barra, int simbolo);