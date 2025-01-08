/*
 *  StQ 01.12.2001
 *  Matrici e allocazione dinamica:
 *    ordinamento di stringhe da file a file mediante matrice dinamica
 *    Il file contiene sulla prima riga il numero di stringhe la cui lunghezza
 *    e' limitata a 100 ctr
 */

#include <stdio.h>
#include <string.h>

#define   MAX_LINE   100

void ordina (char **mat, int n);

void main (
  void
  )
{
  FILE *fpR, *fpW;
  int i, n;
  char fileNameR[MAX_LINE];
  char fileNameW[MAX_LINE];
  char stringa[MAX_LINE];
  char **mat;

  fprintf (stdout, "Nome file input = ");
  scanf("%s", fileNameR);

  /* Lettura file */
  fpR = fopen (fileNameR, "r");
  if (fpR==NULL) {
    fprintf (stderr, "Errore di apertura file input.\n");
    return;
  }

  if (fscanf (fpR, "%d", &n) == EOF) {
    fclose (fpR);
    return;
  }

  mat = (char **) malloc (n * sizeof (char *));
  if (mat == NULL)  {
    fclose (fpR);
    return;
  }

  i = 0;
  while (fscanf (fpR, "%s", stringa) != EOF && i<n) {
    mat[i] = (char *) malloc ((strlen(stringa)+1) * sizeof (char));
    if (mat[i] == NULL)  {
      fclose (fpR);
      return;
    }
    strcpy (mat[i], stringa);
    i++;
  }

  /* Nuovo valore di n nel caso ci fossero meno di
     n elementi da ordinare */
  n = i;

  fclose(fpR);

    /* Ordinamento */
  ordina (mat, n);

  /* Scrittura file */
  fprintf (stdout, "Nome file output = ");
  scanf("%s", fileNameW);

  fpW = fopen (fileNameW, "w");
  if (fpW==NULL) {
    fprintf (stderr, "Errore di apertura file output.\n");
    return;
  }

  fprintf (fpW, "%d\n", n);
  for (i=0; i<n; i++) {
    fprintf (fpW, "%s\n", mat[i]);
  }


  fclose (fpW);

  /* Free memoria */
  for (i=0; i<n; i++) {
    free (mat[i]);
  }
  free (mat);

  return;
} 

/*
 *  Insertion Sort con puntatori a stringhe ...
 */

void
ordina (
  char **mat,
  int n
  )
{
  int i, j;
  char *stringa;

  for (i=1; i<n; i++) {
    stringa=mat[i];

    j = i;
    while ( --j>=0 && strcmp (stringa, mat[j])<0 )
      mat[j+1]=mat[j];

    mat[j+1]=stringa;
  }

  return;
}
