/*bibliotecas padrao*/
#include <stdio.h>/* printf(), scanf()*/
#include <stdlib.h>/* NULL, malloc(), sizeof() */
#include <math.h>/*pow()*/

/*bibliotecas do usuario*/
#include "conio_v3.2.4.h"/*gotoxy, clrscr()*/
#include "console_v1.5.4.h"
#include "funcoes.h"/* prototipos das funcoes*/



/*--------------------------FUNCOES------------------*/

/*maximiza e posiciona a janela*/
void Setup()
{
	COORD resolucao;
	
	resolucao = MaxDimensaoJanela();
	setPosicaoJanela(0,0);
	setDimensaoJanela(resolucao.X, resolucao.Y);
	clrscr();
}



/* retorna o numero de digitos de um numero*/
int numDig(int dado)
{
	int cont = 0;
	
	if(dado == 0)
		cont = 1;
	else
	{
		while(dado != 0)
		{
			cont = cont +1;
			labs(dado = dado / 10);
		}
	}
	return cont;
}

/*retorna o maior ente dois numeros*/
int maior(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

/*desenha um quadrado em volta do numero*/
void desenhaquadro(int elemento, int x, int y)
{
	int numDigitos = numDig(elemento), i;
	
	if(elemento < 0) /* caso o numero seja negativo adicina um ao nimero de digitos*/
		numDigitos = numDigitos + 1;
	
	gotoxy(x, y);/* vai para a posiçao correta */
	
	/*desenha um quadro com simbolos da tebela ascii contendo o dado em seu centro*/ 
	printf("%c", 218);
	
	for(i = 1; i <= numDigitos; i++)
		printf("%c", 196);
	
	printf("%c\n", 191);
	gotoxy(x, y + 1);
	printf("%c%d%c\n", 179, elemento,179);
	gotoxy(x,y+2);
	printf("%c", 192);
	
	for(i=1; i<= numDigitos; i++)
		printf("%c", 196);
	printf("%c\n", 217);
} 


/*-------------------------------FUNCOES DA ARVORE-------------------------------------------*/



/*cria uma arvore vazia*/
Pno criaArv()
{
	/* Aloca espaço de memoria para um novo no*/
    Pno raiz = (Pno) malloc(sizeof(No));
    if(raiz != NULL)
       raiz = NULL;
    return raiz;
}

/*cria um novo no*/
Pno criaNO(int dado, Pno esq, Pno dir) 
{
	/*aloca um espaco de memoria para o novo noh*/
	Pno novo = (Pno) malloc (sizeof(No));
	novo->dado = dado;
	novo->bal = 0; /*altura do novo noh 0*/
	novo->esq = esq;
	novo->dir = dir;
	return novo;
}


/*desenha a arvore se baseando na altura de cada noh para determinar a posicao*/
void mostra(Pno raiz, int x, int y)
{
	/*caso o no nao seja null*/
	if (raiz != NULL) 
	{
		/*desenha a arvore emOrdem*/
		mostra((raiz->esq), x - pow(2,(raiz->bal))*2, y+4);
		desenhaquadro(raiz->dado,x, y);
		mostra((raiz->dir),x + pow(2,(raiz->bal))*2, y+4); 
	}
  
}

Pno sucessor(Pno raiz)
{
	if(raiz->esq == NULL && raiz->dir == NULL)
		return raiz;
	else
		return(sucessor(raiz->esq));
}

/*retorna a altura de um noh*/
int alturaNo(Pno raiz )
{
	int h;
	if(raiz == NULL)
		return -1; /* caso o no nao exista*/
	else
		h = raiz->bal;
	return h; /* retorna a altura armazenada na estrurura da arvore*/
}

/* fator balanceamento*/
int fatBal(Pno raiz)
{
	/*altura da sub-arvore da direita - altura da sub arvore da esquerda*/
	return labs(alturaNo(raiz->dir) - alturaNo(raiz->esq));
}

/*rotacao simples a esquerda*/
void rotEsq(PPno raiz) 
{
	Pno a, b;/*variaveis temporarias*/
	
	a = (*raiz)->esq; /* "a" recebe o noh a esquerda da raiz*/
	b = a->dir; /* "b" recebe o noh a direita de "a"*/
	a->dir = *raiz; /* noh direito de "a" recebe a raiz*/
	(*raiz)->esq = b;/* noh esquerdo da raiz recebe "b"*/
	
	/*atualiza as alturasa dos nos*/
	(*raiz)->bal = maior(alturaNo((*raiz)->esq),alturaNo((*raiz)->dir))+1;
	a->bal = maior(alturaNo(a->esq),alturaNo(a->dir))+1;
	
	*raiz = a; /* a nova raiz da sub arvore recebe "a" */
}

/*rotacao simples a direita*/
void rotDir(PPno raiz) 
{
	Pno a, b; /*variaveis temporarias*/
	
	a = (*raiz)->dir; /* "a" recebe o noh a direita da raiz*/
	b = a->esq; /* "b" recebe o noh a esquerda de "a"*/
	a->esq = *raiz; /* noh esquerdo de "a" recebe a raiz*/
	(*raiz)->dir = b; /* noh direito da raiz recebe "b"*/
	
	/*atualiza as alturasa dos nos*/
	(*raiz)->bal = maior(alturaNo((*raiz)->esq),alturaNo((*raiz)->dir))+1;
	a->bal = maior(alturaNo(a->esq),alturaNo(a->dir))+1;
	
	*raiz = a; /* a nova raiz da sub arvore recebe "a" */
}

/*rotacao dupla a direita*/ 
void rotEsqDir(PPno raiz) 
{
	/*uma rotacao simples a direita no noh a esquerda*/
	rotDir(&(*raiz)->esq);
	/*realiza uma rotaçao a direita no noh*/
	rotEsq(raiz);
}

/*rotacao dupla a esquerda*/
void rotDirEsq(PPno raiz) 
{
	/*uma rotacao simples a esquerda no noh a direita*/
	rotEsq(&(*raiz)->dir);
	/*realiza uma rotaçao a direita no noh*/
	rotDir(raiz);
}


/* insere um no*/
int inserir(PPno raiz, int novoValor)
{
	int ok; /* confirma se a inserçao foi feita*/
	Pno atual = *raiz; /* armazena o dado atual*/
	/* arvore vazia*/
    if(*raiz == NULL)
	{
		/*cria um novo no*/
        *raiz = criaNO (novoValor, NULL, NULL);
		printf("\n Valor %d Inseirdo!!\n", novoValor);
        return 1;/* alocado com sucesso*/
    }

    
    if(novoValor < atual->dado)/*caso o novo dado seja menor que o dado pai insere recursivamente a esquerda*/
	{
        if((ok = inserir(&(atual->esq), novoValor))	 == 1)
		{
            if(fatBal(atual) >= 2)/*verifica se a arvore ficou desbanceada*/
			{
                if(novoValor < (*raiz)->esq->dado )/* verifica qual a rotação necessaria*/
				{
					
					printf("Rotacao simples a direita no noh %d... \n", (*raiz)->dado);
                    rotEsq(raiz);/*rotação simples a direita*/
                }
				else
				{				
					printf("Rotacao dupla a direita no noh %d... \n", (*raiz)->dado);
                    rotEsqDir(raiz);/*rotação dupla a direita*/
				
                }
            }
        }
    }
	else
	{
        if(novoValor > atual->dado)/*caso novo dado seja maior que o dado pai inserir recursivamente a direita*/
		{
            if((ok = inserir(&(atual->dir), novoValor)) == 1)
			{
                if(fatBal(atual) >= 2)
				{
                    if((*raiz)->dir->dado < novoValor)
					{
						printf("Rotacao simples a esquerda no noh %d... \n", (*raiz)->dado);
                        rotDir(raiz);/* rotação simples a esquerda*/	
						
                    }
					else
					{					
						printf("Rotacao dupla esquerda no noh %d... \n", (*raiz)->dado);
                        rotDirEsq(raiz);/* rotação dupla a esquerda*/
						
                    }
                }
            }
        }
		else/* caso o dado ja exista na arvore*/
			if(novoValor == atual->dado)
				{ 
					return 0;
				}
    }
	
	
    atual->bal = maior(alturaNo(atual->esq),alturaNo(atual->dir)) + 1;/*atualiza bal do no atual*/
    return ok;/* retorna se foi inserido*/
}

/*busca um valor*/
int busca(Pno raiz, int dado)
{
	
	if(raiz == NULL) /*se o no estiver vazio o valor nao existe*/
		return 0;
	
	if(dado == raiz->dado) /* se o valor for encontrado retorna 1*/
		return 1;
	else
	{
		if(dado > raiz->dado)/* se o valor for maior que o no busca recursivamente a direita*/
			return busca(raiz->dir, dado);
		else/*senao busca recursivamente a esquerda*/
			return busca(raiz->esq, dado);
	}
	return 0;
}

/* remove um no*/
int remover(PPno raiz, int valor)
{
	int ok;
	Pno aux;/*auxlilar*/
	
	if(*raiz == NULL)/* valor nao exite*/
		return 0;
		
	if(valor < (*raiz)->dado)/*caso o valor procurado seja menor que o atual procura a esquerda*/
	{
		if((ok = remover(&(*raiz)->esq, valor) == 1))/* remove o valor usando recursividade*/
		{
			if(fatBal(*raiz) >= 2)/* confere o balanceamento*/
			{
				/* caso esteja debalanceado aplica a rotaçaõ nescessaria*/
				if(alturaNo((*raiz)->dir->esq) <= alturaNo((*raiz)->dir->dir))
				{
					printf("Rotacao simples a direita no noh %d... \n", (*raiz)->dado);
					rotDir(raiz);
				}
				else
				{
					printf("Rotacao dupla a direita no noh %d... \n", (*raiz)->dado);
					rotEsqDir(raiz);	
				}
			}
		}
	}
	if(valor > (*raiz)->dado)/*caso o valor procurado seja menor que o atual procura a direita*/
	{
		if((ok = remover(&(*raiz)->dir, valor) == 1))/* remove o valor usando recursividade*/
		{
			if(fatBal(*raiz) >= 2)/* confere o balanceamento*/
			{
				/* caso esteja debalanceado aplica a rotaçao nescessaria*/
				if(alturaNo((*raiz)->esq->dir) <= alturaNo((*raiz)->esq->esq))
				{
					printf("Rotacao simples a esquerda no noh %d... \n", (*raiz)->dado);
					rotEsq(raiz);
				}
				else
					printf("Rotacao dupla a esquerda no noh %d... \n", (*raiz)->dado);
					rotDirEsq(raiz);	
			}
		}
	}
	if(valor == (*raiz)->dado)
	{
		if((*raiz)->esq == NULL || (*raiz)-> dir == NULL)/* noh com 1 ou 0 filhos*/
		{
			aux = (*raiz);/* variavel auxiliar para liberar o noh*/
			
			if((*raiz)->esq != NULL)/* ocupa o lugar do antigo noh*/
				*raiz = (*raiz)->esq;
			else
				*raiz = (*raiz)->dir;
			free(aux);/* libera o noh*/
		}
		else/* noh com 2 filhos*/
		{
			aux = sucessor((*raiz)->dir);/*procura o sucessor para substituir o noh*/
			
			(*raiz)->dado = aux->dado;/*troca o valor atual pelo valor do sucessor*/
			remover(&(*raiz)->dir, (*raiz)->dado);/*remove o noh atual*/
			
			if(fatBal(*raiz) >= 2)/* confere o balanceamento*/
			{
				/* caso esteja debalanceado aplica a rotaçao nescessaria*/
				if(alturaNo((*raiz)->esq->dir) <= alturaNo((*raiz)->esq->esq))	
				{
					printf("Rotacao simples a esquerda no noh %d... \n", (*raiz)->dado);
					rotEsq(raiz);
				}
				else
				{
					printf("Rotacao dupla a esquerda no noh %d... \n", (*raiz)->dado);
					rotDirEsq(raiz);
				}
				
			}
		}
	
	if (*raiz != NULL)
		/*atualiza as alturas*/
        (*raiz)->bal = maior(alturaNo((*raiz)->esq),alturaNo((*raiz)->dir)) + 1;
		
	return 1;/* caso removido com sucesso*/
		
	}
	/*atualiza as alturas*/
	(*raiz)->bal = maior(alturaNo((*raiz)->esq),alturaNo((*raiz)->dir)) + 1;
	
	return ok;
}

/* libera o espaco da memoria ocupado pela arvore*/
void liberaArv(Pno raiz)
{
	if (raiz)
	 {
		 /* liver os nos recursivamento em PreOrdem*/
	     liberaArv(raiz->esq);
	     liberaArv(raiz->dir);		 
		 free(raiz);
	 }
}

void menu(){/* imprime um menu*/
	
	printf("\nMENU\n\n");
	printf("1 - Inserir valor\n");
	printf("2 - Remover\n");
	printf("3 - Buscar\n");
	printf("0 - Sair\n");
	printf("Digite sua opcao: ");
	
}