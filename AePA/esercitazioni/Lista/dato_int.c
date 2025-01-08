/********************************************************************/
/**                      DATO.C per int                            **/
/********************************************************************/

#include <stdio.h>
#include "dato.h"
#define MAXC 30

dato_t leggi_dato (FILE *fp)
{
  dato_t dato;
  char riga[MAXC];

  fgets (riga, MAXC, fp);
  sscanf (riga, "%d", &dato);
  return dato;
}

void stampa_dato (FILE *fp, dato_t dato)
{
  fprintf (fp, "%d\n", dato);
}

int precede (dato_t d1, dato_t d2)
{
  if (d1 < d2)
    return 1;
  else
    return 0;
}

int uguali (dato_t d1, dato_t d2)
{
  if (d1 == d2)
    return 1;
  else
    return 0;
}
