#include <stdio.h>
#include <string.h>
#define MAXSTR 26

int main() {
	char linha[MAXSTR];
	int contador[MAXSTR], i;
	for(i=0;i<MAXSTR;i++) {
		contador[i]=0;
	}
	while (fgets(linha, MAXSTR, stdin) != NULL) {
		linha[strlen(linha)-1] = '\0';
		contador[strlen(linha)] += 1;
	}
	printf("Numero de letras --> Numero de palavras\n");
	for(i=1;i<MAXSTR;i++) {
		printf("%16d --> %5d\n", i, contador[i]);
	}
	return 0;
}
