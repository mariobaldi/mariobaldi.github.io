/********************************************************************/
/**                           RICERCA.C                            **/
/**             soluzione compito del 28/1/98: es. 1               **/
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "dato.h"

/*
   Funzione leggi_dati.
   Acquisisce un vettore di dati da un file.
   Ritorna due vettori di puntatori ai dati (by reference), 
   tali da poter essere ordinati secondo due criteri diversi.
   Il valore ritornato e' il numero di dati letti;
*/
int leggi_dati(
  char *file, /* nome del file */
  dato_t ***p1,
  dato_t ***p2
)
{
  int i, ndati;
  dato_t *d;
  FILE *fp;
  char riga[MAXC];

  /* conteggio righe del file */
  fp = fopen(file,"r");
  if (fp == NULL) return 0;
  for (i=0; fgets(riga,MAXC,fp)!=NULL; i++);
  ndati=i/3;
  fclose(fp);
  
  /* alloca vettori */
  *p1 = malloc(sizeof(dato_t *)*ndati);
  *p2 = malloc(sizeof(dato_t *)*ndati);
  if (p1 == NULL)||(p2 == NULL)) return 0;

  /* lettura dati */
  fp = fopen(file,"r");
  if (fp == NULL) return 0;
  for (i=0; i<ndati; i++) {
    p1[i] = p2[i] = leggi_dato(fp);
    if (p1[i] == NULL) return(i);
  }
  fclose(fp);

  return ndati;
}

int ricerca_dicotomica(dato_t **vet, dato_t *dato, int i, int j, int chiave)
{
  /* ricerca dicotomica di dato all'interno di vet */  
}

void main (char **argv, int argc)
{
dato_t **dati_per_nome,
       **dati_met_matr;
dato_t cerca_dato;
int ndati, fine=0;

/*
  ...
*/

ndati = leggi_dati(argv[1], &dati_per_nome, &dati_per_matr);

qsort_mio(dati_per_nome,ndati,PER_NOME);
qsort_mio(dati_per_matr,ndati,PER_MATR);

while (!fine) {
/*
  scelta opzione di ricerca
  assegna campo da cercare a cerca_dato
*/

  /* ricerca per nome */
  i = ricerca_dicotomica(dati_per_nome,
        cerca_dato,0,ndati-1,PER_NOME);
  stampa_dato(stdout,dati_per_nome[i]);

}
}




}