/********************************************************************/
/**                     DATO.H per char *                          **/
/********************************************************************/

/*
   per matricola si usano interi. E' equivalente l'uso di stringhe.
*/

#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#define MAXC 60
#define LDNASC 9

/* selezione chiave di ricerca */
#define PER_NOME      0
#define PER_MATRICOLA 1

typedef struct {
  char *nome;
  char dnasc[LDNASC+1]; 
  int matr;
} dato_t;

dato_t *leggi_dato (FILE *fp);
void stampa_dato (FILE *fp, dato_t *dato);
int precede (dato_t *d1, dato_t *d2, int chiave);
int uguali (dato_t *d1, dato_t *d2, int chiave);

#endif
