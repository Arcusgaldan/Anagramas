#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Math.h>
#include "arvore.h"

char **listaPalavras;

void emOrdemNo(NoArvore *no){
	if(no == NULL)
		return;
	
	emOrdemNo(no->E);
	printf("%s\n", no->Valor);		
	emOrdemNo(no->D);
}

int carregarArquivo(){
	int contPalavras = 0; 																//Contador de palavras
	char *aux = malloc(48 * sizeof(char)); 												//String auxiliar que ler� as palavras do arquivo
	FILE *arq = fopen("palavras.txt", "r"); 											//Arquivo de palavras
	listaPalavras = (char**)malloc(sizeof(char*)); 										//Lista de palavras
	while(!feof(arq)){ 																	//Enquanto o arquivo n�o chegar ao fim
		listaPalavras = realloc(listaPalavras, sizeof(char*) * (contPalavras+1)); 		//Aumenta o tamanho da lista de palavras
		fgets(aux, 48, arq); 															//L� 48 caracteres ou o pr�ximo \n do arquivo. Perguntar ao Tiago se lista dada para desenvolvimento ser� mesma dada no teste, sen�o tornar tamanho din�mico.
		listaPalavras[contPalavras] = malloc(48 * sizeof(char)); 						//D� o tamanho m�ximo de 47 caracteres + \0 para a palavra a ser guardada na lista.
		strcpy(listaPalavras[contPalavras], aux); 										//Copia o conte�do da string auxiliar para o vetor de palavras.
		listaPalavras[contPalavras][strcspn(listaPalavras[contPalavras], "\n")] = 0; 	//Remove o \n padr�o do fgets.
		contPalavras++; 																//Atualiza o contador de palavras
	}
	return contPalavras;
}

void populaArvorePalavras(Arvore *a, int e, int d){
	if(e == d){																			//Verifica se o E e D s�o iguais, ou seja, subvetor de um �nico elemento.
		ArvoreInserir(a, listaPalavras[e]);												//Insere o valor na �rvore
//		printf("%i eh igual a %i, entrei na condicao\n", e, d);
		return;																			//Termina a execu��o da fun��o para n�o gerar conflitos abaixo
	}
	if(e < 0){																			//Verifica��o de debug, retirar antes do release
//		printf("E eh menor que 0 onde E = %i\n", e);
		exit(EXIT_FAILURE);
	}
	if(d >= 41060){																		//Verifica��o de debug, retirar antes do release
//		printf("D eh maior ou igual a 41060 onde D = %i\n", d);
		exit(EXIT_FAILURE);
	}
	int meio = (int)(e+d) / 2;
	if(meio < 0 || meio >= 41060){														//Verifica��o de debug, retirar antes do release
//		printf("O problema ta no meio onde meio = %i\n", meio);
		exit(EXIT_FAILURE);
	}
	ArvoreInserir(a, listaPalavras[meio]);												//Insere a palavra do meio na �rvore
//	printf("(meio)Inseri a palavra %s\n", listaPalavras[meio]);
	if(meio > e){																		//Se for poss�vel formar um subvetor � esquerda do meio...
		populaArvorePalavras(a, e, meio-1);												//Utiliza a fun��o recursivamente no vetor � esquerda
	}
	if(meio < d){																		//Se for poss�vel formar um subvetor � direita do meio...
		populaArvorePalavras(a, meio+1, d);												//Utiliza a fun��o recursivamente no vetor � direita
	}
}

int main(int argc, char **argv){
	int contPalavras = carregarArquivo();												//Popula a lista de palavras e retorna a quantidade de palavras (tamanho do vetor)
	int x;
	Arvore *a = ArvoreNovo();															//Cria uma nova �rvore
	populaArvorePalavras(a, 0, contPalavras-1);											//Inicia a fun��o recursiva de popular a �rvore
}
