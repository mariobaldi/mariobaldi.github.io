/* camminid.h: dichiarazioni per il file caminid.c */

#ifndef _CAMMINID_H_
#define _CAMMINID_H_

typedef enum {FALSE = 0, TRUE = 1} BOOL;

int trovapercorso(int n, int percorso[], int profondcorr, BOOL visitati[],
	int matrad[], int nodocorr, int nododest);
void invertipercorso(int n, int percorso[], int matrad[], int nododest);
int camminidistinti(int n, int matrad[], int sorg, int dest);

#endif
