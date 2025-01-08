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

void ordina (char *v, int n);

void main (
  void
  )
{
  FILE *fpR, *fpW;
  int i, n;
  char fileNameR[MAX_LINE];
  char fileNameW[MAX_LINE];
  char stringa[MAX_LINE];
  char *vett, *temp;

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

  vett = (char *) malloc (n * MAX_LINE * sizeof (char));
  if (vett == NULL)  {
    fclose (fpR);
    return;
  }

  i = 0;
  while (fscanf (fpR, "%s", stringa) != EOF && i<n)
    strcpy (&vett[MAX_LINE * i++], stringa);

  /* Nuovo valore di n nel caso ci fossero meno di
     n elementi da ordinare */
  n = i;

  fclose(fpR);

  /* Ordinamento */
  ordina (vett, n);

  /* Scrittura file */
  fprintf (stdout, "Nome file output = ");
  scanf("%s", fileNameW);

  fpW = fopen (fileNameW, "w");
  if (fpW==NULL) {
    fprintf (stderr, "Errore di apertura file output.\n");
    return;
  }

  fprintf (fpW, "%d\n", n);
  for (temp=vett; temp<vett+n*MAX_LINE; temp+=MAX_LINE) {
    fprintf (fpW, "%s\n", temp);
  }

  fclose (fpW);

  /* Free memoria */
  free (vett);

  return;
}

/*
 *  Insertion Sort con stringhe ...
 */

void
ordina (
  char *v,
  int n
  )
{
  int i, j;
  char stringa[MAX_LINE];

  for (i=1; i<n; i++) {
    strcpy (stringa, &v[i*MAX_LINE]);

    j = i;
    while ( --j>=0 && strcmp (stringa, &v[j*MAX_LINE])<0 ) {
      strcpy (&v[(j+1)*MAX_LINE], &v[j*MAX_LINE]);
    }

    strcpy (&v[(j+1)*MAX_LINE], stringa);
  }

  return;
}
