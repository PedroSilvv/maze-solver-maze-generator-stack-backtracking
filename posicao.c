#include "posicao.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

// PEDRO HENRIQUE DE SOUZA SILVESTRE -- ESTRUTURA DE DADOS 1 -- CIENCIA DA COMPUTAÇÃO - UEL 

// TRABALHO FEITO INDIVIDUALMENTE

// Inicializa a pilha
void inicializarPilha( struct Pilha *pilha) {
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

// famoso push
void empilhar(struct Pilha *pilha, int l, int c) {
    struct Posicao *nova = (struct Posicao*)malloc(sizeof(struct Posicao));
   
    nova->linha = l;
    nova->coluna = c;
   
    nova->prox = pilha->topo;
   
    pilha->topo = nova;
   
    pilha->tamanho += 1;
}

// famoso pop
void desempilhar(struct Pilha *pilha) {
    if(pilha->tamanho < 1 ){
        printf("Pilha vazia");
    }
   
    struct Posicao *pos_topo = pilha->topo;
   
    pilha->topo = pos_topo->prox;
    pilha->tamanho = pilha->tamanho - 1;
    free(pos_topo);
   
}

// **cordenadas que compõem o caminho ate a chegada, com as coordenadas inuteis ja desempilhadas
void imprimeCoordenadas(struct Pilha *pilha){
   
    struct Posicao *atual = pilha->topo;
   
    //printf("(%d,%d)\n", atual->linha, atual->coluna);
   
    //atual = atual -> prox;
   
    while(atual != NULL){
        printf("(%d,%d)\n", atual->linha, atual->coluna);
        atual = atual->prox;
    }
}

// function para imprimir o labirinto
void imprimirLabirinto(char **labirinto, int numL, int numC, struct Posicao *personagem) {

    system("cls");     
    printf("%dx%d\n", numL, numC);

    for (int i = 0; i < numL; i++) {
        for (int j = 0; j < numC; j++) {
            if (i == personagem->linha && j == personagem->coluna) {
                printf("P ");
            } else {
                printf("%c ", labirinto[i][j]);
            }
        }
        printf("\n");
    }
}

// Le a matriz do txt e ja converte os caracteres de acordo com os que eu escolhi
// Aloca a memoria dinamicamente para a matriz, scaneia a primeira linha e atribui o tamanho da matriz para o ponteiro *mtam
char** CriarMatrizAPartirDoTXT(int *mtam) {
    FILE *arquivo = fopen("labirinto.txt", "r");

    if (arquivo == NULL) {
        return NULL;
    }
    
    int tamanho;
    fscanf(arquivo, "%d", &tamanho);
    *mtam = tamanho;

    char **matriz = (char **)malloc(tamanho * sizeof(char *));

    for (int i = 0; i < tamanho; i++)
    {
        matriz[i] = (char *)malloc(tamanho * sizeof(char));
    }


    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            char caractere;
            fscanf(arquivo, " %c", &caractere);

            // Aplicar as substituições
            switch (caractere) {
                case '1':
                    matriz[i][j] = '#';
                    break;
                case '2':
                    matriz[i][j] = '2';
                    break;
                case '0':
                    matriz[i][j] = ' ';
                    break;
                case '3':
                    matriz[i][j] = '3';
                    break;
                default:
                    matriz[i][j] = caractere;
                    break;
            }
        }
    }

    fclose(arquivo);

    return(matriz);
}


//funcao principal do programa, onde o labirinto e resolvido.
void resolver_labirinto(char **labirinto, int tamanho) {
    struct Pilha personagem;
    inicializarPilha(&personagem);
   
    int linha_inicial = 0;
    int coluna_inicial = 0;
   
    for(int x = 0; x < tamanho; x++){
        for(int y = 0; y < tamanho; y++){
            if(labirinto[x][y] == '2'){
                linha_inicial = x;
                coluna_inicial = y;
                empilhar(&personagem, linha_inicial, coluna_inicial);
                break;
            }
        }
    }
    
    labirinto[linha_inicial][coluna_inicial] = '.';
    
    while (1) {
        imprimirLabirinto(labirinto, tamanho, tamanho, personagem.topo);
   
        int moveu = 0;
        int venceu = 0;

        // Verifica para onde o personagem pode se mover
        // Direita = 1
        // Baixo = 2
        // Esquerda = 3
        // Cima = 4

        int mover_para = 0;
   
        //labirinto[personagem.topo->linha][personagem.topo->coluna] = '.';
   
        // Verifica chegada para direita
        if (labirinto[personagem.topo->linha][personagem.topo->coluna + 1] == '3') {
            labirinto[personagem.topo->linha][personagem.topo->coluna + 1] = 'P';
            moveu = 1;
            venceu = 1;
            mover_para = 1;
        }
        // Verifica chegada para baixo
        else if (labirinto[personagem.topo->linha + 1][personagem.topo->coluna] == '3') {
            labirinto[personagem.topo->linha + 1][personagem.topo->coluna] = 'P';
            moveu = 1;
            venceu = 1;
            mover_para = 2;
        }
        // Verifica chegada para a esquerda
        else if (labirinto[personagem.topo->linha][personagem.topo->coluna - 1] == '3') {
            labirinto[personagem.topo->linha][personagem.topo->coluna - 1] = 'P';
            moveu = 1;
            venceu = 1;
            mover_para = 3;
        }
        // Verifica chegada para cima
        else if (labirinto[personagem.topo->linha - 1][personagem.topo->coluna] == '3') {
            labirinto[personagem.topo->linha - 1][personagem.topo->coluna] = 'P';
            moveu = 1;
            venceu = 1;
            mover_para = 4;
        }

        if (!venceu) {
            // Verifica se tem algum caminho disponivel
            if (labirinto[personagem.topo->linha][personagem.topo->coluna + 1] == ' ' || labirinto[personagem.topo->linha][personagem.topo->coluna + 1] == '3') {
                mover_para = 1;
                moveu = 1;
            } else if (labirinto[personagem.topo->linha + 1][personagem.topo->coluna] == ' ' || labirinto[personagem.topo->linha + 1][personagem.topo->coluna] == '3') {
                mover_para = 2;
                moveu = 1;
            } else if (labirinto[personagem.topo->linha][personagem.topo->coluna - 1] == ' ' || labirinto[personagem.topo->linha][personagem.topo->coluna - 1] == '3') {
                mover_para = 3;
                moveu = 1;
            } else if (labirinto[personagem.topo->linha - 1][personagem.topo->coluna] == ' ' || labirinto[personagem.topo->linha - 1][personagem.topo->coluna] == '3') {
                mover_para = 4;
                moveu = 1;
            }
        }
   
        if (moveu) {
            if(mover_para == 1){empilhar(&personagem, personagem.topo->linha, personagem.topo->coluna + 1);}
            else if(mover_para == 2){empilhar(&personagem, personagem.topo->linha + 1, personagem.topo->coluna);}
            else if(mover_para == 3){empilhar(&personagem, personagem.topo->linha, personagem.topo->coluna - 1);}
            else if(mover_para == 4){empilhar(&personagem, personagem.topo->linha - 1, personagem.topo->coluna );}

            labirinto[personagem.topo->linha][personagem.topo->coluna] = '.';

            #ifdef _WIN32
                Sleep(500);  // Se for Windows, use Sleep()
            #else
                usleep(500000);  // Se for Unix/Linux, use usleep() (microssegundos)
            #endif

            if (venceu) {
                imprimirLabirinto(labirinto, tamanho, tamanho, personagem.topo);
                for( int i = 0; i < tamanho; i++)
                {
                    for (int j = 0; j < tamanho; j++)
                    {
                        if(labirinto[i][j] == '*'){
                            labirinto[i][j] = ' ';
                        }
                    }  
                }
                break;
            }
        } else {

            #ifdef _WIN32
                Sleep(500);  // Se for Windows, use Sleep()
            #else
                usleep(500000);  // Se for Unix/Linux, use usleep() (microssegundos)
            #endif

            labirinto[personagem.topo->linha][personagem.topo->coluna] = '*'; 
            desempilhar(&personagem);
        }
    }
    
    #ifdef _WIN32
        Sleep(500);  // Se for Windows, use Sleep()
    #else
        usleep(500000);  // Se for Unix/Linux, use usleep() (microssegundos)
    #endif
    imprimirLabirinto(labirinto, tamanho, tamanho, personagem.topo);
    imprimeCoordenadas(&personagem);
    printf("Foi preciso %d coordenadas para completar o labirinto!!", personagem.tamanho);
}


