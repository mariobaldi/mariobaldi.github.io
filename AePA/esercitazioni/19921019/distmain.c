/* distmain.c: file principale del programma */

#include <stdio.h>
#include <stdlib.h>
#include "camminid.h"

#define BUFFERSIZE	100

int main(int argc, char *argv[])
{
	int n, i, j, destinazione, sorgente;
	FILE *fp;
	int *matrad; /* matrice memorizzata per righe nel vettore */
	char buffer[BUFFERSIZE]; /* buffer di uso generale */

	if (argc < 3)
	{
		printf("Errore nei parametri\n");
		return -1;
	}
	strcpy(buffer, argv[1]);
	sorgente = atol(argv[2]);
	destinazione = atol(argv[3]);

	if ((fp = fopen(buffer, "r")) == NULL)
	{
		printf("Errore nell'apertura del file\n");
		return -1;
	}

	fscanf(fp, "%d", &n);
	matrad = malloc(n * n * sizeof (int)); /* alloco la matrice */

	for (i = 0; i < n; i++)
	{
		fscanf(fp, "%s", buffer); /* leggo la riga */
		for (j = 0; j < n; j++) /* ciascun carattere della riga... */
			matrad[j + i * n] = buffer[j] - '0'; /* nella corrispettiva... */
	}	/* ...cella della matrice */
	fclose(fp);
	/* richiamo la funzione creata */
	i = camminidistinti(n, matrad, sorgente - 1, destinazione - 1);
	printf("\nesiste/ono %d cammino/i distinti\n", i);

	free(matrad);
	return 0;
}
