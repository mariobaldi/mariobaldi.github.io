
/*
 *   telBinRi.c
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
void ordina_elenco(abbonato_t dati[], int abb);
int cerca_tel(unsigned long int tel, abbonato_t elenco[], int n_abb);
int cerca_nome(char *nome, abbonato_t elenco[], int n_abb);
int cerca_dic(char *n, abbonato_t el[], int l, int r);

void copia_abbonato(abbonato_t *dest, abbonato_t *sorg);

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
  ordina_elenco(elenco,n_abb);

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

  return (cerca_dic(nome, elenco,0,n_abb-1));
}


int cerca_dic(
  char *n,
  abbonato_t el[],
  int l,
  int r
)
{

  int res,c=(l+r)/2;

  if((res=strcmp(n,el[c].nome))==0) return(c);
  if(l==r) return(-1); /* dato non trovato */
  if (res>0)
     return (cerca_dic(n,el,c+1,r));
  else
     return (cerca_dic(n,el,l,c-1));
}


void copia_abbonato(
   abbonato_t *dest,
   abbonato_t *sorg
)
{
   dest->tel=sorg->tel;
   strcpy(dest->nome,sorg->nome);
}


void ordina_elenco(
   abbonato_t dati[],
   int abb
)
{
   int i,j;
   abbonato_t temp;

   for(i=1;i<abb;i++) {
      j=i;
      copia_abbonato(&temp,&dati[i]);
      while(strcmp(temp.nome,dati[--j].nome)<0) {
	 copia_abbonato(&dati[j+1],&dati[j]);
	 if (j==0) {
	    j--;
	    break;
	 }
      }
      copia_abbonato(&dati[j+1],&temp);
   }
}