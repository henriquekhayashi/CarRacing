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
    
    //desenha os inimigos na matriz
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

    //retorna posições aleatorias para os inimigos
    void random(int (*posicao)[3]){
        int i;
        for(i=0; i<3; i++)
            if(rand()%2 == 1)
                (*posicao)[i] = COLUMNS-3;
            else
                (*posicao)[i] = 2;
        
    }

    //verifica colisão
    int collisionCheck(Carro barra, char matrix[ROWS][COLUMNS]){
        if(matrix[barra.i-3][barra.j+1] == (char)PIXEL)
            return 1;
        
        else return 0;
    }     

    //verifica colisão
    int collisionCheckSides(Carro barra, char matrix[ROWS][COLUMNS], int direcao){
         switch(direcao){
        case TECLA_AUP: 
        case TECLA_A:        
        case LEFT:
            if(matrix[ROWS-1][2] == (char)PIXEL)
            return 1;
            else return 0;
        case TECLA_DUP: 
        case TECLA_D:            
        case RIGHT:
            if(matrix[ROWS-1][8] == (char)PIXEL)
            return 1;
            else return 0;
                
        
         }
    }   

    //fim de jogo, salva o nome e score em um arquivo
    void gameOver(Score pontos){
        Score z;
        FILE *f, *g;
        int i = 0, pos, s =0, aux;

        //criar arquivo
        f = fopen ("highscore.bin","ab");
         fclose(f);

        //mostar o nome e pontos ao fim do jogo
        printf("\n\n\n\t\t\t\tFIM DE JOGO\n");
        
        printf("\n\n\t\t\t\tScore: %d\n", pontos.pontos*50);
        
        getch();

        //abrir arquivo
        g = fopen ("highscore.bin","rb");
        
        //ver o tamanho    
            
            fseek (g, 0, SEEK_END);
            pos=ftell(g);
            aux = pontos.pontos;

            //verifiar quantidade de pontuações na lista
            if(pos >= (sizeof(Score)*5)){ s =1;
            
            }
                //colocar de volta pro começo do arquivo
                fseek (g, 0, SEEK_SET);

                //comparar nova pontuacao com a lista
                //ler todos os scores dentro do arquivo
                for(i=0;i<5;i++){
                                        
                    //comparar
                    fread(&z, sizeof(Score),1,g);
                                        
                    if (z.pontos < aux){ 
                        aux=z.pontos;
                        pos = ftell(g)-sizeof(Score);
                    }

                    if (feof(g)) break;
                }
               
               
               
            
        //adicionar para o arquivo
                    
            fclose(g);

            if(s==1){
            f = fopen ("highscore.bin","rb+");
            fseek (f , pos, SEEK_SET);
           
            }
            else f = fopen ("highscore.bin","ab");
            fwrite(&pontos,sizeof(Score),1,f);
            fclose(f);
            
    }

    
    void menu(int *game){
        char matriz[3][19], str[19];
        int i, j = 0, tecla = 1;
        
        ShowConsoleCursor(0);
                 
       strcpy(matriz[0], "      Novo Jogo\n");
       strcpy(matriz[1], "      High Scores\n");
       strcpy(matriz[2], "      Sair\n");


        while(*game !=1){
            
           //inicializa cursor
            matriz[j][2] = '*';

            //recebe tecla
        if(kbhit()){
            matriz[j][2] = ' ';
            tecla = getch();
            
            }
        
        gotoxy(0,0);
        printf("\n\n");
        //printa matriz do menu
        for(i=0;i<3;i++){
            printf("\n\t\t\t");
            printf("%s", matriz[i]);  
            printf("\n");
        }     

        //movimentação cursor
        switch(tecla){
            case ARROWS: 

                if(kbhit()) 
                tecla = getch();

                    switch(tecla){

                        //mover para cima
                        case UP:
                            if(j==0)
                                j=2;
                            else 
                                j--;
                        break;

                        //mover para baixo
                        case DOWN: 
                            if(j==2)
                                j=0;
                            else    
                                j++;
                        break;
                    }
            break;

            //selecionar opção
            case ENTER:

                //novo jogo
                if(j==0){
                    *game = 1;
                    return;
                } 

                //mostrar lista de pontuação
                else if(j==1){
                    score();
                }

                //sair do programa
                else{
                    exit(0);
                }
                break;
                   
            }
        }
      
        getch();

    }

    //ordena e mostra a lista de pontuação
    void score(){
        FILE *f;
        Score x[5], z;
        int i ,j, cont;

        //abrir arquivo highscore.bin para leitura
        f = fopen ("highscore.bin","rb");
        if(f != NULL){
        printf("\n");

        //ler todos os scores dentro do arquivo
        
        for(i=0;i<5;i++){
            fread(&x[i], sizeof(Score),1,f);
            if (feof(f)) break;
        }

        if(ftell(f)>sizeof(Score)){
            
            for(j =0; j<i-1; j++)
                for(cont=0;cont<i-j-1;cont++)
                    if(x[cont].pontos< x[cont+1].pontos){
                    
                            z = x[cont];
                            x[cont] = x[cont+1];
                            x[cont+1] = z;
                    }
        }
        
        
        printf("\t\t\t\t\t\thigh score\n");
        printf("\t\t____________________________________________________________\n");
            
        for(j =0; j<i; j++){
          
            printf("\t\t|%s",x[j].nome ); 
            gotoxy(48, (GetCursorPosition().Y));
            
            printf("|Score: %d", x[j].pontos*50);
            gotoxy(75, (GetCursorPosition().Y));
            printf("|\n");
        }
        }
        fclose(f);
        

            

    }

    //Salva a posição dos jogadores, pontuação e fase
    void salvarJogo(Carro jogador, Carro competidor, int posicao[3], Score score, int contfase){
        FILE * f;
        Save a;

        
        a.cont = 1;

        //posição do jogador e inimigos
        a.jogador = jogador.i;
        a.jogadorpos = jogador.j;
        a.competidor = competidor.i;
        a.posicao[0] = posicao[0];
        a.posicao[1] = posicao[1];
        a.posicao[2] = posicao[2];

        //score
        a.score = score;

        //fase
        a.contfase = contfase;

        //criar arquivo
        f = fopen ("save.bin","ab");
        fclose(f);

        //salvar dados
        f = fopen ("save.bin","rb+");
        fseek (f , 0, SEEK_SET);
        fwrite(&a,sizeof(Save),1,f);

        fclose(f);
    }

    int abrirSave(Carro *jogador, Carro *competidor, int posicao[3] , Score *score, int *contfase){
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
        *contfase = a.contfase;
        
        retorno = a.cont;
        a.cont = 0;
        fseek (f , 0, SEEK_SET);
        fwrite(&a,sizeof(Save),1,f);
        }

        }
        fclose(f);

        return retorno;
    }
    
