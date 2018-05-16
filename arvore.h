#include <stdlib.h>
#include <string.h>

typedef struct NoArvore
{
	char *Valor;
	struct NoArvore *E, *D;
}NoArvore;

typedef struct Arvore
{
	NoArvore *Raiz;
	int Quantidade;
}Arvore;

Arvore* ArvoreNovo(void)
{
	Arvore *a = (Arvore*)malloc(sizeof(Arvore));
	a->Quantidade = 0;
	a->Raiz = NULL;
	
	return a;
}

int ArvoreInserir(Arvore *a, char *Valor)
{
	if(a == NULL)
		return 0;
	
	NoArvore *no = (NoArvore*)malloc(sizeof(NoArvore));
	
	if(no == NULL)
		return 0;
	
	no->Valor = malloc(strlen(Valor) * sizeof(char));
	strcpy(no->Valor, Valor);
	no->E = NULL;
	no->D = NULL;
	
	NoArvore *atual = a->Raiz;
	NoArvore *pai = a->Raiz;
	
	while(atual != NULL)
	{
		pai = atual;
		
		if(strcmp(Valor, atual->Valor) < 0)
		{
			atual = atual->E;
		}
		else
		{
			atual = atual->D;
		}
	}
	
	if(pai == atual)
	{
		a->Raiz = no;
	}
	else
	{
		if(strcmp(Valor, pai->Valor) < 0)
		{
			pai->E = no;
		}
		else
		{
			pai->D = no;
		}
	}
	
	a->Quantidade++;
	
	return 1;
}

int ArvoreBuscar(Arvore *a, char *Valor){
	if(a == NULL)
		return -1;
		
	NoArvore *atual = a->Raiz;
	while(atual != NULL){		
		if(strcmp(Valor, atual->Valor) < 0){
			atual = atual->E;
		}else if(strcmp(Valor, atual->Valor) > 0){
			atual = atual->D;
		}else{
			return 1;
		}
	}
	return 0;
}

//int ArvoreRemover(Arvore *a, char *Valor)
//{
//	if(a == NULL || a->Quantidade == 0)
//		return 0;
//		
//	NoArvore *atual = a->Raiz; //aponta para o elemento a ser removido
//	NoArvore *pai = NULL; //aponta para o pai do elemento a ser removido
//	
//	while(atual != NULL && strcmp(Valor, atual->Valor) != 0)
//	{
//		pai = atual;
//		
//		if(strcmp(Valor, atual->Valor) < 0)
//		{
//			atual = atual->E;
//		}
//		else
//		{
//			atual = atual->D;
//		}
//	}
//	
//	if(atual == NULL)
//		return 0;
//	
//	if(atual->E == NULL && atual->D == NULL)
//	{
//		remoção de nó folha		
//		if(pai == NULL)
//		{
//			a->Raiz = NULL;
//		}
//		else if(Valor < pai->Valor)
//		{
//			pai->E = NULL;
//		}
//		else
//		{
//			pai->D = NULL;
//		}		
//	}
//	
//	else if(atual->E != NULL && atual->D == NULL)
//	{
//		remoção de nó com filho à esquerda
//		
//		if(pai == NULL)
//		{
//			a->Raiz = atual->E;
//		}
//		else if(strcmp(Valor, pai->Valor) < 0)
//		{
//			pai->E = atual->E;	
//		}
//		else
//		{
//			pai->D = atual->E;
//		}
//	}
//	
//	else if(atual->E == NULL && atual->D != NULL)
//	{
//		remoção de nó com filho à direita
//		
//		if(pai == NULL)
//		{
//			a->Raiz = atual->D;
//		}
//		else if(strcmp(Valor, pai->Valor) < 0)
//		{
//			pai->E = atual->D;
//		}
//		else
//		{
//			pai->D = atual->D;
//		}
//	}
//	
//	else
//	{
//		remoção de nó com ambos os filhos		
//		NoArvore *substituto = atual->E; //nó que irá substituir o nó removido
//		NoArvore *paiSubstituto = atual;
//		
//		while(substituto->D != NULL)
//		{
//			paiSubstituto = substituto;
//			substituto = substituto->D;
//		}
//		
//		if(paiSubstituto != atual)
//		{		
//			paiSubstituto->D = substituto->E;
//			substituto->E = atual->E;
//		}
//
//		substituto->D = atual->D;
//		
//		if(pai == NULL)
//		{
//			a->Raiz = substituto;
//		}
//		else if(strcmp(Valor, pai->Valor) < 0)
//		{
//			pai->E = substituto;
//		}
//		else
//		{
//			pai->D = substituto;
//		}
//	}
//	
//	free(atual);
//	atual = NULL;
//	a->Quantidade--;
//	
//	return 1;
//}







