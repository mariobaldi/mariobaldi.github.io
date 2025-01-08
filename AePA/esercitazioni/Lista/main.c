/********************************************************************/
/**                            MAIN.C                              **/
/********************************************************************/

#include <stdio.h>

#include "dato.h"
#include "lista.h"

#define MAXC 20

int main (void)
{
  nodo_t *headp;
  dato_t d;
  int fine = 0;
  char riga[MAXC];
  FILE *fp;

  headp = crea_lista_vuota ();

  while (!fine) {

    printf ("(I)ns/(R)ic/(C)anc/(V)isualizza/(S)alva/(L)eggi/(F)ine : ");
    gets (riga);

    switch (tolower (riga[0])) {
      case 'c':
	d = leggi_dato (stdin);
	headp = cancella (headp, d);
	break;
      case 'f':
	fine = 1;
	break;
      case 'i':
	d = leggi_dato (stdin);
	headp = inserisci (headp, d);
	break;
      case 'l':
	printf ("file: ");
	gets (riga);
	fp = fopen (riga, "r");
	if (fp == NULL) {
	  printf ("ERRORE in apertura di %s\n", riga);
	}
	else {
	  headp = leggi_lista (fp);
	}
	break;
      case 'r':
	d = leggi_dato (stdin);
	if (cerca (headp, d) == 1)
	  printf ("Trovato\n");
	else
	  printf ("Non trovato\n");
	break;
      case 's':
	printf ("file: ");
	gets (riga);
	fp = fopen (riga, "w");
	if (fp == NULL) {
	  printf ("ERRORE in apertura di %s\n", riga);
	}
	else {
	  stampa_lista (fp, headp);
	  fclose (fp);
	}
	break;
      case 'v':
	stampa_lista (stdout, headp);
	break;
      default:
	printf ("Opzione sconosciuta\n");
    }

  }

}
