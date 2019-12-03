/*
Jogo interativo tetris implementado em linguagem c para uso 
no console (terminal de comando)

autor:Henrique
data:19/09/2019

*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

//Configuração das dimensoes da matriz principal do jogo
#define COLUMNS 11
#define TRUE_ROWS 30
#define ROWS TRUE_ROWS-5



//Configuração de teclas
#define ESC 27
#define ARROWS 224
#define LEFT 75
#define RIGHT 77

#define TECLA_A 97
#define TECLA_AUP 65
#define TECLA_D 100
#define TECLA_DUP 68
#define TECLA_W 119
#define TECLA_WUP 87
#define TECLA_S 115
#define TECLA_SUP 83
#define DOWN 80
#define UP 72
#define ENTER 13
#define SPACE 32

//Configurações de layou
#define PIXEL 178
#define EMPTY 32


//Estrutura padrão de componentes
typedef struct{
    int i; //posição linhas da matriz
    int j; //posição colunas matriz
    
    int width; //largura
    int height; //altura
}Carro;

//Estrutura padrão de componentes
typedef struct{
    //Carro competidor;

    int *i; //posição linhas da matriz
    int *j; //posição colunas matriz
    
    int width; //largura
    int height; //altura    
    
}CarroCompetidor;

//score
typedef struct{
    int pontos; //pontos
    char nome[30]; //nome do jogador
      
}Score;

//save
typedef struct{
    int cont;
    int jogador, competidor, jogadorpos;
    int posicao[3];
    Score score;
    int velocidade;
    int contfase;

}Save;

/*
    Inicializa a matriz principal com 'espaços vazios'

*/
void init(char matrix[TRUE_ROWS][COLUMNS]);

/*
    Mostra o conteúdo da matriz principal na tela
    do computador.
*/
void printMatrix(char matrix[TRUE_ROWS][COLUMNS], int faixa1);

void drawCar(char matrix[ROWS][COLUMNS], Carro *barra, int simbolo);

void drawEnemy(char matrix[ROWS][COLUMNS], Carro barra, int simbolo, int posicao[3]);

int collisionCheck( Carro barra, char matrix[ROWS][COLUMNS]);

int collisionCheckSides(Carro barra, char matrix[ROWS][COLUMNS], int direcao);

//Fim de jogo e salvar pontuação
void gameOver(Score score);

void menu(int *game);

void score();

//Sortear posição dos oponentes
void random(int (*posicao)[3]);

//Salvar jogo
void salvarJogo(Carro jogador, Carro competidor, int posicao[3], Score score, int contfase);

//Continuar o jogo salvo
int abrirSave(Carro *jogador, Carro *competidor, int posicao[3], Score *score, int*contfase);