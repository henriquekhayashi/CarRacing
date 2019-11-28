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

void init(char matrix[ROWS][COLUMNS])
{
    int i,j;

    for(i=0; i<ROWS; i++)
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

void printMatrix(char matrix[ROWS][COLUMNS],int faixa1)
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

    void drawCar(char matrix[ROWS][COLUMNS], Carro *barra, int simbolo){
        
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
    
        
    void drawEnemy(char matrix[ROWS][COLUMNS], Carro barra, int simbolo, int posicao[3]){
        
        barra.j = posicao[0];
        if(barra.i<ROWS+4||barra.i>=0)drawCar(matrix, &barra, simbolo);
        barra.i -= 14;
        barra.j = posicao[1];
        drawCar(matrix, &barra, simbolo);
        barra.i -= 14;
        barra.j = posicao[2];
        drawCar(matrix, &barra, simbolo);

    }

    void random(int (*posicao)[3]){
        int i;
        for(i=0; i<3; i++)
            if(rand()%2 == 1)
                (*posicao)[i] = COLUMNS-3;
            else
                (*posicao)[i] = 2;
        
    }

    int collisionDetect(Carro barra, char matrix[ROWS][COLUMNS]){
        if(matrix[barra.i-3][barra.j+1] == (char)PIXEL)
            return 1;
        
        else return 0;
    }       

    void gameOver(score){
        Score pontos, z;
        FILE *f, *g;
        int i = 0, tecla, pos, s =0, aux;

        f = fopen ("highscore.bin","ab");
         fclose(f);

        pontos.pontos = score;
        printf("GAME OVER\n");
        printf("score: %d\n", pontos.pontos);
        printf("nome: ");
        gets(pontos.nome);

        g = fopen ("highscore.bin","rb");
        
        //ver o tamanho    
            printf("vertamanho/pos: ");
            fseek (g, 0, SEEK_END);
            pos=ftell(g);
            printf("%d\n ", pos);
            printf("size of score*3: %d\n ", sizeof(Score)*3);
            printf("size of x*3: %d\n ", sizeof(pontos)*3);
            printf("size of x: %d\n ", sizeof(pontos));
            
            aux = pontos.pontos;

            //verifiar quantidade de pontuações na lista
            if(pos >= (sizeof(Score)*3)) s =1;
                
                printf("lertodosscores\n ");

                //colocar de volta pro começo do arquivo
                fseek (g, 0, SEEK_SET);

                //comparar nova pontuacao com a lista
                //ler todos os scores dentro do arquivo
                while(1){
                    
                    printf("comparar\n ");
                    //comparar
                    
                    fread(&z, sizeof(Score),1,g);
                    
                    printf("z.pontos: %d\n ", z.pontos);
                    
                    if (z.pontos < aux){ 
                        aux=z.pontos;
                        printf("aux == %d", aux);
                        pos = ftell(g)-sizeof(Score);
                        printf("Nome: %s Score: %d\n",z.nome, z.pontos); 
                       // s = 1;
                       // i = 3;
                    }

                    printf("isto acontece ?\n ");

                    if (feof(g)) break;

                    
                }
                printf("\n\ns!=1 n maior\n ");
               // i=3;
                //if(s!=1) break;
            
        //adicionar para o arquivo
            printf("\nok?\n");
            
            fclose(g);
            if(s==1){
            f = fopen ("highscore.bin","rb+");
            fseek (f , pos, SEEK_SET);
            printf("o lugar certo");
            }
            else f = fopen ("highscore.bin","ab");
            fwrite(&pontos,sizeof(Score),1,f);
            fclose(f);
            
        //}
        
        printf("\npos: %d", pos);
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
        int i = 0, tecla, pos, s =0, aux;

         

        
        //abrir arquivo highscore.bin para adição de dados
        //f = fopen ("highscore.bin","ab");
        //adicionar dados nas struc score
        

       // for(i=0; i<3;i++){
            /*printf("\n%d - Digite o nome: ", i);
            gets(x.nome);
        
            printf("Digite pontos: ");
            scanf("%d",&x.pontos);
            fflush(stdin);
            */
             
        
        

        //abrir arquivo highscore.bin para leitura
        f = fopen ("highscore.bin","rb");
        if(f != NULL){
        printf("\n");

        //ler todos os scores dentro do arquivo
        while(1){
            fread(&x, sizeof(Score),1,f);
            if (feof(f)) break;
        
            printf("Nome: %s Score: %d\n",x.nome, x.pontos); 
	    }
        }
        fclose(f);
        

            

    }

    void salvarJogo(Carro jogador, Carro competidor, int posicao[3], int score){
        FILE * f;
        Save a;
        a.cont = 1;
        a.jogador = jogador.i;
        a.jogadorpos = jogador.j;
        a.competidor = competidor.i;
        a.posicao[0] = posicao[0];
        a.posicao[1] = posicao[1];
        a.posicao[2] = posicao[2];
        a.score = score;

         f = fopen ("save.bin","ab");
         fclose(f);

        f = fopen ("save.bin","rb+");
        fseek (f , 0, SEEK_SET);
        fwrite(&a,sizeof(Save),1,f);

        fclose(f);
    }

    int abrirSave(Carro *jogador, Carro *competidor, int posicao[3] , int *score){
        FILE * f;
        Save a;
        int retorno =0;
        
        f = fopen ("save.bin","ab");
        
        if(f != NULL){

         

        f = fopen ("save.bin","rb+");
        fread(&a, sizeof(Save),1,f);
        if(a.cont == 1){
        jogador->i = a.jogador;
        jogador->j = a.jogadorpos;
        competidor->i = a.competidor;
        posicao[0] = a.posicao[0];
        posicao[1] = a.posicao[1];
        posicao[2] = a.posicao[2];
        *score = a.score;
        
        retorno = a.cont;
        a.cont = 0;
        fseek (f , 0, SEEK_SET);
        fwrite(&a,sizeof(Save),1,f);
        }

        }
        fclose(f);

        return retorno;
    }
    
