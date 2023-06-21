/* Deseenvolvedor Joao Victor Simiao da Silva */
/* Data 26/09/2019							  */
/* Descrição:                                 */
/* o programa cria e desenha uma arvore AVL   */
/*grafica									  */
/* Ultima modifição: 18/11/2019               */

/*para compilar */
/*gcc -o main.exe main.c conio_v3.2.4.c console_v1.5.4.c funcoes.c -Wall -pedantic -Wextra */

/*Bibliotecas padrao*/
#include <stdio.h> /*printf()*/

/*Bibliotecas do usuario*/
#include "conio_v3.2.4.h"/* clrscr(), gotoxy()*/
#include "console_v1.5.4.h"/*tamanhoJanelaConsole()*/
#include "funcoes.h"/*inserir(), mostra(), remover(), busca()*/ 

int main(int argc, char **argv) 
{
	/*declaração de variaveis*/
	int nun, ok, x, y, opcao;
	Pno arv;
	COORD tam;
	
	/* Silenciar o warning relativo aos parämetros não usados da função main() */
	argc = argc;
	argv = argv;
	
	/*inicializacao das variaveis*/
	arv = criaArv();/* cria uma arvore vazia*/
	Setup();
  
	tam = tamanhoJanelaConsole();/*tamanhon da janela*/
	x = tam.X/2; /*posicao da raiz*/
	y = 2;

  
	do{
		
		gotoxy(1,1);
		menu(); /*Escreve o menu*/
		scanf("%d", &opcao);
		switch(opcao){

			case 1:
			
				/*recebe o numero a ser inserido*/
				clrscr();
				printf("Digite um numero a ser inserido: ");
				scanf("%d", &nun);
				
				clrscr();
				gotoxy(1,1);
				menu();
				printf("\n\n >Ocorencias< ");
				ok = inserir(&arv, nun);
				
				if(ok == 0)
				{
					printf("\nNao inserido!! \nValor repetido!!");
			    }
				mostra(arv, x, y);
                      

			break;
			case 2:
				clrscr();
				printf("Digite um numero a ser removido: ");
				scanf("%d", &nun);
				
				clrscr();
				gotoxy(1,1);
				menu();
				printf("\n\n >>Ocorencias<<\n ");
				ok = remover(&arv, nun);
				if(ok == 0)
				{
					printf("Valor inexistente!!");
			    }
				
				mostra(arv, x, y);
			break;
			case 3:
			
				clrscr();
				printf("Digite um valor a ser buscado: ");
				scanf("%d", &nun);
				ok = busca(arv, nun);
				
				/*valor encotrado*/
				if (ok)
				{
					printf("Valor %d encontrado!! ", nun );
					mostra(arv, x, y);
					getch();
				}
				/*valor nao encotrado*/
				else
				{
					printf("Valor %d nao encontrado!!", nun);
					mostra(arv, x, y);
					getch();
				}
				clrscr();
			break;
			
			case 0:
				break;
			
			default :

			printf("opcao nao existe! tente novamente");

			break;
		}

	}while(opcao);
	
	liberaArv(arv);/*libera a arvore e encerra*/
	clrscr();


	return 0;
}