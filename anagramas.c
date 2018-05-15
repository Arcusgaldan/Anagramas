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
	char *aux = malloc(48 * sizeof(char)); 												//String auxiliar que lerá as palavras do arquivo
	FILE *arq = fopen("palavras.txt", "r"); 											//Arquivo de palavras
	listaPalavras = (char**)malloc(sizeof(char*)); 										//Lista de palavras
	while(!feof(arq)){ 																	//Enquanto o arquivo não chegar ao fim
		listaPalavras = realloc(listaPalavras, sizeof(char*) * (contPalavras+1)); 		//Aumenta o tamanho da lista de palavras
		fgets(aux, 48, arq); 															//Lê 48 caracteres ou o próximo \n do arquivo. Perguntar ao Tiago se lista dada para desenvolvimento será mesma dada no teste, senão tornar tamanho dinâmico.
		listaPalavras[contPalavras] = malloc(48 * sizeof(char)); 						//Dá o tamanho máximo de 47 caracteres + \0 para a palavra a ser guardada na lista.
		strcpy(listaPalavras[contPalavras], aux); 										//Copia o conteúdo da string auxiliar para o vetor de palavras.
		listaPalavras[contPalavras][strcspn(listaPalavras[contPalavras], "\n")] = 0; 	//Remove o \n padrão do fgets.
		contPalavras++; 																//Atualiza o contador de palavras
	}
	return contPalavras;
}

void populaArvorePalavras(Arvore *a, int e, int d){
	if(e == d){																			//Verifica se o E e D são iguais, ou seja, subvetor de um único elemento.
		ArvoreInserir(a, listaPalavras[e]);												//Insere o valor na árvore
//		printf("%i eh igual a %i, entrei na condicao\n", e, d);
		return;																			//Termina a execução da função para não gerar conflitos abaixo
	}
	if(e < 0){																			//Verificação de debug, retirar antes do release
//		printf("E eh menor que 0 onde E = %i\n", e);
		exit(EXIT_FAILURE);
	}
	if(d >= 41060){																		//Verificação de debug, retirar antes do release
//		printf("D eh maior ou igual a 41060 onde D = %i\n", d);
		exit(EXIT_FAILURE);
	}
	int meio = (int)(e+d) / 2;
	if(meio < 0 || meio >= 41060){														//Verificação de debug, retirar antes do release
//		printf("O problema ta no meio onde meio = %i\n", meio);
		exit(EXIT_FAILURE);
	}
	ArvoreInserir(a, listaPalavras[meio]);												//Insere a palavra do meio na árvore
//	printf("(meio)Inseri a palavra %s\n", listaPalavras[meio]);
	if(meio > e){																		//Se for possível formar um subvetor à esquerda do meio...
		populaArvorePalavras(a, e, meio-1);												//Utiliza a função recursivamente no vetor à esquerda
	}
	if(meio < d){																		//Se for possível formar um subvetor à direita do meio...
		populaArvorePalavras(a, meio+1, d);												//Utiliza a função recursivamente no vetor à direita
	}
}

int main(int argc, char **argv){
	int contPalavras = carregarArquivo();												//Popula a lista de palavras e retorna a quantidade de palavras (tamanho do vetor)
	int x;
	Arvore *a = ArvoreNovo();															//Cria uma nova árvore
	populaArvorePalavras(a, 0, contPalavras-1);											//Inicia a função recursiva de popular a árvore
}
