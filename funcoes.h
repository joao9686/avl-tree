
#ifndef _FUNCOES_LIB_
#define _FUNCOES_LIB_FUNCOES_LIB_

typedef struct no {
  int dado; /* numero inteiro armazenado no noh*/
  int bal;   /* fator balanceamento hdir - hesq */
  struct no *esq, *dir; /* ponteiro para o noh da esquerda e da direita*/
} No, *Pno, **PPno;/* tipo noh, ponteiro para o noh, e ponteiro para ponteiro para o no*/

Pno criaArv();/*cria uma arvore vazia*/
void mostra(Pno raiz, int x, int y);/*mostra a arvore*/
int inserir(PPno raiz, int nun);/*insere um novo dado na arvore*/
void menu();/* Escreve um menu*/
int busca(Pno raiz, int nun);/* busca um valor na arvore*/
int remover(PPno raiz, int valor);/*remove um valor da arvore*/
void Setup();/* maximiza a janela*/
void liberaArv(Pno raiz);/* libera a arvore*/




#endif /* FUNCOES_LIB  */
