#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int main (void){
char linha [30];
char *Arq;
int i;
FILE *ponArq;

ponArq = fopen ("palavras.txt", "r");
if (ponArq == NULL){
	printf("Arquivo Corrompido.\n");
	}
	else { printf("Lido com sucesso\n");}
	
	i = 1;
	while (!feof(ponArq)){		
		fgets(linha, 30, ponArq);
		printf("linha %d : %s", i, linha);
		i++;
	}
		fclose (ponArq);
	
	return 1;
}
	
	
