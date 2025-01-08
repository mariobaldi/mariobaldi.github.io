/********************************************************************/
/**                     DATO.C per char *                          **/
/********************************************************************/

#include <stdio.h>
#include "dato.h"
#define MAXC 60

dato_t leggi_dato (FILE *fp)
{
  dato_t dato;
  char riga[MAXC];

  fgets (riga, MAXC, fp);
  dato = (char *) malloc ((strlen(riga)+1)*sizeof(char));
  if (dato == NULL) {
    printf ("ERRORE: memoria dinamica insufficiente per stringa\n");
    exit (1);
  }
  /* filtra eventuale carattere a-capo */
  if (riga[strlen(riga)-1] == '\n')
    riga[strlen(riga)-1] = '\0';
  strcpy (dato, riga);
  return dato;
}

void stampa_dato (FILE *fp, dato_t dato)
{
  fprintf (fp, "%s\n", dato);
}

int precede (dato_t d1, dato_t d2)
{
  if (strcmp (d1, d2) < 0)
    return 1;
  else
    return 0;
}

int uguali (dato_t d1, dato_t d2)
{
  if (strcmp (d1, d2) == 0)
    return 1;
  else
    return 0;
}

