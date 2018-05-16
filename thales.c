#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Math.h>
#include "arvore.h"

char **listaPalavras;																	//Vari�vel global que armazena, temporariamente, a lista de palavras v�lidas.
Arvore *validas;																		//Vari�vel global que armazena a �rvore de palavras v�lidas.

void letrasMinusculas(char *palavra){													//Fun��o que transforma todas as letras mai�sculas de uma string em min�sculas
	int i, tam = strlen(palavra);														//Declara��o das duas vari�veis de controle
	for(i = 0; i < tam; i++){															//In�cio de la�o para itera��o de caracteres da string
		if(palavra[i] >= 65 && palavra[i] <= 90){										//Se o caractere for uma letra mai�scula...
			palavra[i] += 32;															//Converte para caractere min�sculo
		}
	}
}

void trocarCaracteres(char *x, char *y)													//Fun��o que troca caracteres de posi��o em uma string
{
    char aux;																			//Auxiliar que guarda o primeiro caractere da entrada temporariamente		
    aux = *x;																			//Armazenamento do primeiro caractere da entrada na vari�vel auxiliar
    *x = *y;																			//Troca de valor entre as duas vari�veis de entrada
    *y = aux;																			//Recebimento de valor guardado na vari�vel auxiliar previamente
}

void anagramas(char *palavra, int e, int d, Arvore *encontradas)						//Fun��o que gera e valida todos os anagramas de uma string
{
	int i;																				//Vari�vel de itera��o
	if (e == d){																		//Se os indicadores se encontraram... (� um anagrama)
		if(ArvoreBuscar(validas, palavra) == 1){										//Se o anagrama gerado for encontrado na �rvore de palavras v�lidas...
	 		if(ArvoreBuscar(encontradas, palavra) == 0){								//Se o anagrama n�o for encontrado na �rvore de anagramas encontrados (para evitar repeti��o)
	 			ArvoreInserir(encontradas, palavra);									//Insere o anagrama na �rvore de anagramas encontrados
			 }
		}
	}
   	else{																				//Se os indicadores n�o se encontraram... (ainda n�o � um anagrama)
	   for (i = e; i <= d; i++)															//La�o de itera��o da substring
	   {
	      trocarCaracteres((palavra+e), (palavra+i));									//Trocam-se caracteres de lugar
	      anagramas(palavra, e+1, d, encontradas);										//Inicia-se o processo de verifica��o de substring sem o primeiro caractere da substring atual (ou seja, com o primeiro caractere fixado)
	      trocarCaracteres((palavra+e), (palavra+i));									//Trocam-se os caracteres de volta a seus lugares
	   }
	}
}



void emOrdemNo(NoArvore *no){															//Fun��o que exibe os elementos de uma �rvore em ordem alfab�tica
	if(no == NULL)																		//Se a �rvore for nula...
		return;																			//Termina-se a execu��o para evitar acesso ilegal de mem�ria
	
	emOrdemNo(no->E);																	//Chama a fun��o recursivamente � sub�rvore da esquerda
	printf("%s\n", no->Valor);															//Imprime o valor do n� atual
	emOrdemNo(no->D);																	//Chama a fun��o recursivamente � sub�rvore da direita
}

int carregarArquivo(){																	//Fun��o que carrega o arquivo de palavras v�lidas do disco para a mem�ria principal
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
	return contPalavras;																//Retorna a quantidade de palavras da lista
}

void populaArvorePalavras(Arvore *a, int e, int d){
	if(e == d){																			//Verifica se o E e D s�o iguais, ou seja, subvetor de um �nico elemento.
		ArvoreInserir(a, listaPalavras[e]);												//Insere o valor na �rvore
		return;																			//Termina a execu��o da fun��o pois n�o h� mais subvetores � esquerda ou direita
	}
	
	int meio = (int)(e+d) / 2;															//Define o meio do subvetor e por consequ�ncia, o pai da sub�rvore
	ArvoreInserir(a, listaPalavras[meio]);												//Insere a palavra do meio na �rvore
	
	if(meio > e){																		//Se for poss�vel formar um subvetor � esquerda do meio...
		populaArvorePalavras(a, e, meio-1);												//Utiliza a fun��o recursivamente no vetor � esquerda
	}
	
	if(meio < d){																		//Se for poss�vel formar um subvetor � direita do meio...
		populaArvorePalavras(a, meio+1, d);												//Utiliza a fun��o recursivamente no vetor � direita
	}
}

int main(int argc, char **argv){
	int contPalavras = carregarArquivo();												//Popula a lista de palavras e retorna a quantidade de palavras (tamanho do vetor)
	validas = ArvoreNovo();																//Instancia a �rvore de palavras v�lidas
	Arvore *encontradas = ArvoreNovo();													//�rvore de palavras v�lidas encontradas a partir de anagramas da palavra fornecida pelo usu�rio
	populaArvorePalavras(validas, 0, contPalavras-1);									//Inicia a fun��o recursiva de popular a �rvore
	free(listaPalavras);																//Libera o vetor de palavras da mem�ria por ser in�til deste ponto em diante
	printf("Insira a palavra a ser analisada: ");										//Pede ao usu�rio para entrar com a palavra a ser analisada
	char entrada[48];																	//Vari�vel de armazenamento da palavra fornecida
	scanf("%s", entrada);																//L� a palavra fornecida pelo usu�rio
	int tamEntrada = strlen(entrada);													//Quantidade de caracteres da palavra fornecida
	letrasMinusculas(entrada);															//Torna todos os caracteres mai�sculos em min�sculos da palavra fornecida
	anagramas(entrada, 0, tamEntrada-1, encontradas);									//Gera e verifica todos os anagramas da palavra fornecida
	printf("\nLista de palavras\n__________________\n");								//Linha para embelezamento do software
	emOrdemNo(encontradas->Raiz);														//Imprime todas as palavras v�lidas encontradas nos anagramas da palavra fornecida
}	
