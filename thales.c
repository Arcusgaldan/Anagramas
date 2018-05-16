#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Math.h>
#include "arvore.h"

char **listaPalavras;																	//Variável global que armazena, temporariamente, a lista de palavras válidas.
Arvore *validas;																		//Variável global que armazena a árvore de palavras válidas.

void letrasMinusculas(char *palavra){													//Função que transforma todas as letras maiúsculas de uma string em minúsculas
	int i, tam = strlen(palavra);														//Declaração das duas variáveis de controle
	for(i = 0; i < tam; i++){															//Início de laço para iteração de caracteres da string
		if(palavra[i] >= 65 && palavra[i] <= 90){										//Se o caractere for uma letra maiúscula...
			palavra[i] += 32;															//Converte para caractere minúsculo
		}
	}
}

void trocarCaracteres(char *x, char *y)													//Função que troca caracteres de posição em uma string
{
    char aux;																			//Auxiliar que guarda o primeiro caractere da entrada temporariamente		
    aux = *x;																			//Armazenamento do primeiro caractere da entrada na variável auxiliar
    *x = *y;																			//Troca de valor entre as duas variáveis de entrada
    *y = aux;																			//Recebimento de valor guardado na variável auxiliar previamente
}

void anagramas(char *palavra, int e, int d, Arvore *encontradas)						//Função que gera e valida todos os anagramas de uma string
{
	int i;																				//Variável de iteração
	if (e == d){																		//Se os indicadores se encontraram... (é um anagrama)
		if(ArvoreBuscar(validas, palavra) == 1){										//Se o anagrama gerado for encontrado na árvore de palavras válidas...
	 		if(ArvoreBuscar(encontradas, palavra) == 0){								//Se o anagrama não for encontrado na árvore de anagramas encontrados (para evitar repetição)
	 			ArvoreInserir(encontradas, palavra);									//Insere o anagrama na árvore de anagramas encontrados
			 }
		}
	}
   	else{																				//Se os indicadores não se encontraram... (ainda não é um anagrama)
	   for (i = e; i <= d; i++)															//Laço de iteração da substring
	   {
	      trocarCaracteres((palavra+e), (palavra+i));									//Trocam-se caracteres de lugar
	      anagramas(palavra, e+1, d, encontradas);										//Inicia-se o processo de verificação de substring sem o primeiro caractere da substring atual (ou seja, com o primeiro caractere fixado)
	      trocarCaracteres((palavra+e), (palavra+i));									//Trocam-se os caracteres de volta a seus lugares
	   }
	}
}



void emOrdemNo(NoArvore *no){															//Função que exibe os elementos de uma árvore em ordem alfabética
	if(no == NULL)																		//Se a árvore for nula...
		return;																			//Termina-se a execução para evitar acesso ilegal de memória
	
	emOrdemNo(no->E);																	//Chama a função recursivamente à subárvore da esquerda
	printf("%s\n", no->Valor);															//Imprime o valor do nó atual
	emOrdemNo(no->D);																	//Chama a função recursivamente à subárvore da direita
}

int carregarArquivo(){																	//Função que carrega o arquivo de palavras válidas do disco para a memória principal
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
	return contPalavras;																//Retorna a quantidade de palavras da lista
}

void populaArvorePalavras(Arvore *a, int e, int d){
	if(e == d){																			//Verifica se o E e D são iguais, ou seja, subvetor de um único elemento.
		ArvoreInserir(a, listaPalavras[e]);												//Insere o valor na árvore
		return;																			//Termina a execução da função pois não há mais subvetores à esquerda ou direita
	}
	
	int meio = (int)(e+d) / 2;															//Define o meio do subvetor e por consequência, o pai da subárvore
	ArvoreInserir(a, listaPalavras[meio]);												//Insere a palavra do meio na árvore
	
	if(meio > e){																		//Se for possível formar um subvetor à esquerda do meio...
		populaArvorePalavras(a, e, meio-1);												//Utiliza a função recursivamente no vetor à esquerda
	}
	
	if(meio < d){																		//Se for possível formar um subvetor à direita do meio...
		populaArvorePalavras(a, meio+1, d);												//Utiliza a função recursivamente no vetor à direita
	}
}

int main(int argc, char **argv){
	int contPalavras = carregarArquivo();												//Popula a lista de palavras e retorna a quantidade de palavras (tamanho do vetor)
	validas = ArvoreNovo();																//Instancia a árvore de palavras válidas
	Arvore *encontradas = ArvoreNovo();													//Árvore de palavras válidas encontradas a partir de anagramas da palavra fornecida pelo usuário
	populaArvorePalavras(validas, 0, contPalavras-1);									//Inicia a função recursiva de popular a árvore
	free(listaPalavras);																//Libera o vetor de palavras da memória por ser inútil deste ponto em diante
	printf("Insira a palavra a ser analisada: ");										//Pede ao usuário para entrar com a palavra a ser analisada
	char entrada[48];																	//Variável de armazenamento da palavra fornecida
	scanf("%s", entrada);																//Lê a palavra fornecida pelo usuário
	int tamEntrada = strlen(entrada);													//Quantidade de caracteres da palavra fornecida
	letrasMinusculas(entrada);															//Torna todos os caracteres maiúsculos em minúsculos da palavra fornecida
	anagramas(entrada, 0, tamEntrada-1, encontradas);									//Gera e verifica todos os anagramas da palavra fornecida
	printf("\nLista de palavras\n__________________\n");								//Linha para embelezamento do software
	emOrdemNo(encontradas->Raiz);														//Imprime todas as palavras válidas encontradas nos anagramas da palavra fornecida
}	
