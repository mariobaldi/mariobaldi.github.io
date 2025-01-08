/**CFile***********************************************************************

  FileName    [giocoVita.c]

  Synopsis    [Realizza il gioco della vita]

  Description [La configurazione inziale si introduce specificando indice
    di riga e di colonna di ciascun elemento. Indice di riga e/o colonna
    negativi interrompono la fase di input. Indic
    L'evoluzione avviene sino a interrompere il programma.
  ]

  Author      [StQ 01.12.1998]

******************************************************************************/

#include <stdio.h>

#define DIM1    5  /* Righe Mat */
#define DIM2    5  /* Colonne Mat */

char mat[2][DIM1][DIM2];

/* vettori per il calcolo delle coordinate dei vicini */
int a[8] = { 0, 1, 1, 1, 0, -1, -1, -1},
    b[8] = { 1, 1, 0, -1, -1, -1, 0, 1};

/* prototipi */
void update (char flag);
void reset (char flag);
int alive (int x, int y, char flag);
int neighbour (int x, int y, char flag);
void display (char flag);

void
main (
  void
  )
{
  char c, flag=0;
  int x, y;

  printf ("Formato di Input:\n");
  printf ("  IndiceRiga<spazio>IndiceColonna<return>\n");
  printf ("  IndiceRiga = 0..%d\n", DIM1-1);
  printf ("  IndiceColonna = 0..%d\n", DIM2-1);

  /* acquisizione della configurazione iniziale */
  do {
    printf ("IndiceRiga<spazio>IndiceColonna<return> : ");
    scanf ("%d %d", &x, &y);
    if ((x>=0) && (y>=0) && (x<DIM1) && (y<DIM2)) {
      mat[flag][x][y] = 1;
    }
  } while ( (x>=0) && (y>=0) && (x<DIM1) && (y<DIM2) );

  display (0);

  /* ciclo infinito (di evoluzione) */
  while (1) {
    update (flag);
    display (!flag);
    printf ("\nBatti RETURN per continuare \n");
    c = getchar ();
    flag = !flag;
  }

  return;
}

/*
calcola di una nuova generazione
*/
void
update (
  char flag
  )
{
  int i, j, n;

  for (i=0; i<DIM1; i++) {
    for (j=0; j<DIM2; j++) {
      n = neighbour( i, j, flag);
      if ( alive (i, j, flag) ) {
	 if ( (n == 2) || (n == 3) )
	    mat[!flag][i][j] = 1;
      } else {
	if ( (n == 3) )
	  mat[!flag][i][j] = 1;
      }
    }
  }

  reset (flag);

  return;
}

/*
azzera la matrice relativa alla generazione futura
preparandola a contenere nuovi dati
*/
void
reset (
  char flag
  )
{
  int i, j;

  for (i=0; i<DIM1; i++)
    for (j=0; j<DIM2; j++)
      mat[flag][i][j] = 0;

  return;
}


/*
determina se una casella e' viva
*/
int
alive (
  int x,
  int y,
  char flag
  )
{
if ( mat[flag][x][y] )
   return (1);
else
   return (0);
}

/*
calcola il numero di vicini vivi all'elemento x, y
*/
int
neighbour (
  int x,
  int y,
  char flag
  )
{
  int i, xx, yy, count=0;

  for (i=0; i<8; i++) {
    xx = x + a[i];
    yy = y + b[i];
    if ( xx >= 0 && xx < DIM1 && yy >= 0 && yy < DIM2 )
      if ( alive( xx, yy, flag) )
	count++;
  }

  return (count);
}

/*
visualizza una generazione 
*/
void
display (
  char flag
  )
{
  int i, j;

  printf ("\n");
  for (i=0; i<DIM1+2; i++)
    printf ("#");
  printf ("\n#");

  for (i=0; i<DIM1; i++) {
    for (j=0; j<DIM2; j++)
      if ( mat[flag][i][j])
	 printf ("*");
      else
	 printf (" ");

    printf ("#\n#");
  }

  for (i=0; i<DIM1+1; i++)
    printf ("#");

  return;
}

