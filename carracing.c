/*
Jogo interativo tetris implementado em linguagem c para uso 
no console (terminal de comando)

autor:Henrique
data:19/09/2019

*/

#include "carracing.h"
#include "display.h"

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
     for(j=0; j<COLUMNS+6; j++)
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
        if(i%2==faixa1)printf("%c ", 178);
        else printf("  ");

        //correr pelo x da matriz
        for(j=0; j<COLUMNS; j++)
        {
            //print mapa
            printf("%c", matrix[i][j]);
        }

        //print borda direita
        if(i%2==faixa1)printf(" %c", 178);
        else printf("  ");
        printf("*");  

        printf("\n");
    }

    //print borda debaixo
    printf("\t\t\t\t\t");
    for(j=0; j<COLUMNS+6; j++)
        {
            
           printf("*");
           
        }
    }

//desenhar carro

    void drawCar(char matrix[TRUE_ROWS][COLUMNS], Carro *barra, int simbolo){
        
        /*
        mapa do carro
        5| 
        4|   1    
        3| 12345  
        2|   1    
        1| 12345
        0|
        */

        
        if(barra->i>=0 && barra->i<=ROWS-1){
        //1|3
        matrix[barra->i][barra->j] = simbolo;
        //1|4
        matrix[barra->i][barra->j+1] = simbolo;
        //1|2
        matrix[barra->i][barra->j-1] = simbolo;
        //1|5
        matrix[barra->i][barra->j+2] = simbolo;
        //1|1
        matrix[barra->i][barra->j-2] = simbolo;
        }
        //2|1
        if(barra->i-1>=0 && barra->i-1<=ROWS-1) matrix[barra->i-1][barra->j] = simbolo;
       
        //4|1
        if(barra->i-3>=0 && barra->i-3<=ROWS-1) matrix[barra->i-3][barra->j] = simbolo;
         //3|3
        if(barra->i-2>=0 && barra->i-2<=ROWS-1){
        matrix[barra->i-2][barra->j] = simbolo;
        //3|4
        matrix[barra->i-2][barra->j+1] = simbolo;
        //3|2
        matrix[barra->i-2][barra->j-1] = simbolo;
        //3|5
        matrix[barra->i-2][barra->j+2] = simbolo;
        //3|1
        matrix[barra->i-2][barra->j-2] = simbolo;
        }

        }
    
        
    void drawEnemy(char matrix[ROWS][COLUMNS], Carro barra, int simbolo){
        Carro a = barra;
        drawCar(matrix, &a, simbolo);
        a.i -= 10;
        drawCar(matrix, &a, simbolo);
        a.i -= 10;
        drawCar(matrix, &a, simbolo);

    }

    int collisionDetect(Carro barra, char matrix[ROWS][COLUMNS]){
        if(matrix[barra.i-3][barra.j+1] == (char)PIXEL)
            return 1;
        
        else return 0;
    }       

    void gameOver(){
        
        printf("GAME OVER\n");
    }

    void menu(){
        char matriz[3][19], str[19];
        int i, j = 0, tecla = 1;
        
        ShowConsoleCursor(0);
        
         //for(i=0;i<3;i++)
           //     for(j=0; j<16;j++){
            //matriz[i][j] = ' ';
           /* strcpy(matriz[0][2], "1 - Novo Jogo\n");
            strcpy(matriz[1][2], "2 - High Scores\n");
            strcpy(matriz[2][2], "3 - Sair\n");*/
            
              //  }
            
       strcpy(matriz[0], "  1 - Novo Jogo\n");
       strcpy(matriz[1], "  2 - High Scores\n");
       strcpy(matriz[2], "  3 - Sair\n");

        while(tecla !=0){
            
           //inicializa cursor
            matriz[j][0] = '*';

            //recebe tecla
        if(kbhit()){
            matriz[j][0] = ' ';
            tecla = getch();
            
            }
        
        gotoxy(0,0);
        
        //printf("%d", tecla);

        
        //printa matriz
        for(i=0;i<3;i++){
            //for(j=0;j<19;j++)
            printf("%s", matriz[i]);  
            
            printf("\n");
        }

        

        

            //movimentação cursor
            switch(tecla){
            case ARROWS: 
                if(kbhit()) tecla = getch();
                    switch(tecla){
                        case UP:
                            if(j==0)
                                j=2;
                            else 
                                j--;
                        break;
                        case DOWN: 
                            if(j==2)
                                j=0;
                            else    
                                j++;
                        break;
                    }
            break;

            case ENTER:
                if(j==0) tecla = 0;
                else if(j==1){
                     printf("high score %c", 178);
                     score();
                }
                else printf("sair do jogo");
                break;
                   
            }
        }

        // enter == 13
        //switch(opc)
        getch();

    }

    void score(){
        FILE *f, *g;
        Score x, z;
        int i, tecla, pos, s =0;

        while(tecla!=0){
        //abrir arquivo highscore.bin para adição de dados
        //f = fopen ("highscore.bin","ab");
        //adicionar dados nas struc score
        

        for(i=0; i<3;i++){
            printf("Digite o nome: ");
            gets(x.nome);
        
            printf("Digite pontos: ");
            scanf("%d",&x.pontos);
            fflush(stdin);
            
             g = fopen ("highscore.bin","rb");
        
        //ver o tamanho    
            fseek (g, 0, SEEK_END);
            pos=ftell(g);
            if(pos >= sizeof(x)*5);{

                //ler todos os scores dentro do arquivo
                while(1){
            
                    //comparar
                    fread(&z, sizeof(Carro),1,g);
                    if (feof(g)) break;
                    
                    if (z.pontos < x.pontos){ 
                        pos = ftell(g);
                        s = 1;
                        break;
                    }
                }
                if(s!=1) break;
            }
        //adicionar para o arquivo
            printf("ok?");
            
            fclose(g);
            f = fopen ("highscore.bin","ab");
            if(s==1)fseek (f , pos, SEEK_SET);
            fwrite(&x,sizeof(Carro),1,f);
            fclose(f);
        }
        
        printf("%d", pos);
        
        

        //abrir arquivo highscore.bin para leitura
        f = fopen ("highscore.bin","rb");
        
        //ler todos os scores dentro do arquivo
        while(1){
            fread(&x, sizeof(Carro),1,f);
            if (feof(f)) break;
        
            printf("Nome: %s Score: %d\n",x.nome, x.pontos); 
	    }

        fclose(f);
        

        }        

    }

    
