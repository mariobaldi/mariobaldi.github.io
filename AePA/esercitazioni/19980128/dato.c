/********************************************************************/
/**                     DATO.C per char *                          **/
/********************************************************************/

#include <stdio.h>
#include "dato.h"



dato_t *leggi_dato (FILE *fp)
{
  dato_t *dato;
  char riga[MAXC];

  dato = malloc(sizeof(dato_t));
  if (dato == NULL) {
    printf ("ERRORE: memoria dinamica insufficiente per dato\n");
    exit (1);
  }
  fgets (riga, MAXC, fp);
  if (riga[strlen(riga)-1]=='\n')
    riga[strlen(riga)-1]='\0'; /* toglie eventuale a-capo */
  dato->nome = malloc ((strlen(riga)+1)*sizeof(char));
  if (dato->nome == NULL) {
    printf ("ERRORE: memoria dinamica insufficiente per stringa\n");
    exit (1);
  }
  strcpy (dato->nome, riga);
  fgets (riga, MAXC, fp);
  sscanf ("%s", &(dato->dnasc));
  fgets (riga, MAXC, fp);
  sscanf ("%d", &(dato->matr));
    
  return dato;
}

void stampa_dato (FILE *fp, dato_t *dato)
{
  fprintf (fp, "%s\n", dato->nome);
  fprintf (fp, "%s\n", dato->dnasc);
  fprintf (fp, "%d\n", dato->matr);
}

int precede (dato_t *d1, dato_t *d2, int chiave)
{
  switch (chiave) {
    case PER_NOME:
      if (strcmp (d1->nome, d2->nome) < 0)
        return 1;
      else
        return 0;
    case PER_MATR:
      return (d1->matr < d2->matr);
  }
}

int uguali (dato_t *d1, dato_t *d2)
{
  switch (chiave) {
    case PER_NOME:
      return (strcmp(d1->nome,d2->nome)==0)
    case PER_MATR:
      return (d1->matr==d2->matr);
  }
}

