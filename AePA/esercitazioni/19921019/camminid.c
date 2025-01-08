/* camminid.c: libreria implementante l'algoritmo trattato */

#include <stdlib.h>
#include "camminid.h"

int trovapercorso(int n, int percorso[], int profondcorr, BOOL visitati[],
	int matrad[], int nodocorr, int nododest)
{
	int i;
	BOOL b = FALSE;

	percorso[profondcorr] = nodocorr; /* segna sul percorso */
	visitati[nodocorr] = TRUE; /* e sui nodi gi… visitati */
	if (nodocorr == nododest) return TRUE; /* trovato! */

	for (i = 0; (i < n) && (!b); i++) /* altrimenti cerca sugli adiacenti */
	{
		/* nodo i Š adiacente e non visitato? */
		if ((matrad[i + n * nodocorr] == 1) && (visitati[i] == FALSE))
		{
			b = trovapercorso(n, percorso, profondcorr + 1,
				visitati, matrad, i, nododest);
		}
	}
	return b;
}

void invertipercorso(int n, int percorso[], int matrad[], int nododest)
{
	int da; /* proposizione semplice ;) */
	for (da = 0; percorso[da] != nododest; da++)
	{
		/* inserisce un nodo inverso e toglie quello originale */
		matrad[percorso[da] * n + percorso[da + 1]] = 0;
		matrad[percorso[da + 1] * n + percorso[da]] = 1;
	}
}

int camminidistinti(int n, int matrad[], int sorg, int dest)
{
	int i, j;
	int *percorso;
	BOOL *visitati;

	percorso = malloc(n * sizeof (int));
	visitati = malloc(n * sizeof (BOOL));

	/* pura inizializzazione */
	j = 0;
	for (i = 0; i < n; i++)	visitati[i] = FALSE;

	/* metodo di ford-fulkerson per il nostro caso */
	while (trovapercorso(n, percorso, 0, visitati,
		matrad, sorg, dest))
	{
		j++;
		invertipercorso(n, percorso, matrad, dest);
		for (i = 0; i < n; i++)
			visitati[i] = FALSE;
	}
	free(visitati);
	free(percorso);
	return j;
}
