#ifndef POSICAO_H
#define POSICAO_H

// PEDRO HENRIQUE DE SOUZA SILVESTRE -- ESTRUTURA DE DADOS 1 -- CIENCIA DA COMPUTAÇÃO - UEL 

// TRABALHO FEITO INDIVIDUALMENTE

//Pode ser usado como a posiçao atual do boneco
struct Posicao {
    int linha;
    int coluna;
    struct Posicao *prox;
};

// manter o histórico de posições
struct Pilha {
    struct Posicao *topo;
    int tamanho;
};

// Protótipos das funções
void inicializarPilha(struct Pilha *pilha);
void empilhar(struct Pilha *pilha, int l, int c);
void desempilhar(struct Pilha *pilha);
void imprimeCoordenadas(struct Pilha *pilha);
//void CriarMatrizAPartirDoTXTTESTE(int *mtam, char matriz[MAX_LINHAS][MAX_COLUNAS]);
void imprimirLabirinto(char **labirinto, int numL, int numC, struct Posicao *personagem);
char** CriarMatrizAPartirDoTXT(int *mtam);
void resolver_labirinto(char **labirinto, int tamanho);

#endif
