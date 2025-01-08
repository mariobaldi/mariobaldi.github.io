/*
 *   tel.c
 *   
 *   Il programma legge un elenco di persone e relativi
 *   numeri di telefono dal file tel.txt.
 *   Effettua successivanemte richerche sull'elenco
 *   sia per numero di telefono che per nome.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXRIGA 50
#define MAXDATI 50
#define FILEIN "tel.txt"

typedef struct {
  char nome[MAXRIGA];
  unsigned long int tel;
} abbonato_t;

int leggi_elenco(abbonato_t dati[], FILE *fp);
int cerca_tel(unsigned long int tel, abbonato_t elenco[], int n_abb);
int cerca_nome(char *nome, abbonato_t elenco[], int n_abb);

void main(void)
{
  FILE *el;
  char riga[MAXRIGA+1];
  abbonato_t elenco[MAXDATI];
  int n_abb;
  int fine=0, i;

  el = fopen(FILEIN, "r");
  if (el == NULL) {
    printf("errore in apertura di %s\n", FILEIN);
    return;
  }

  n_abb = leggi_elenco(elenco,el);

  while (!fine) {
    printf ("nome o numero (\"fine\" per terminare): ");
    fgets(riga,MAXRIGA,stdin);
    if (riga[strlen(riga)-1]=='\n')
      riga[strlen(riga)-1]='\0';
    if (strcmp(riga, "fine") == 0)
      fine = 1;
    else {
      if (isdigit(riga[0]))
	i = cerca_tel((unsigned long int) atoi(riga),elenco,n_abb);
      else
	i = cerca_nome(riga,elenco,n_abb);
      if (i < 0)
	printf("Non trovato !\n");
      else
	printf("Nome : %s\nTel  : %u\n",
	       elenco[i].nome, elenco[i].tel);
    }
  }

}

int leggi_elenco(
  abbonato_t dati[],
  FILE       *fp
)
{
  int i;
  char riga[MAXRIGA+1];

  for (i=0; (fgets(riga,MAXRIGA,fp)!=NULL); i++) {
    if (i>=MAXDATI) {
      printf("errore: troppi dati nel file\n");
      printf("dati in eccesso trascurati\n");
      break;
    }
    if (riga[strlen(riga)-1]=='\n')
      riga[strlen(riga)-1]='\0';
    strcpy(dati[i].nome,riga);
    if (fgets(riga,MAXRIGA,fp)==NULL) {
      printf("errore: numero di telefono mancante\n");
      i--;
      break;
    }
    sscanf(riga, "%lu", &(dati[i].tel));
  }
  return (i);
}

int cerca_tel(
  unsigned long int tel,
  abbonato_t  elenco[],
  int         n_abb
)
{
  int i;

  for (i=0; i<n_abb; i++) {
    if (tel == elenco[i].tel)
      return(i);
  }
  return (-1); /* dato non trovato */
}

int cerca_nome(
  char       *nome,
  abbonato_t  elenco[],
  int         n_abb
)
{
  int i;

  for (i=0; i<n_abb; i++) {
    if (strcmp(nome,elenco[i].nome)==0)
      return(i);
  }
  return (-1); /* dato non trovato */
}

