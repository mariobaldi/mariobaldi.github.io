/*

  Soluzione compito FI2-SI del 13/5/94

  E' dato un file testo contenente un elenco di corsi, di richieste per
  lezioni in orario e di aule disponibili, nel seguente formato.

  Prima riga del file: due interi indicanti numero di corsi e di aule.
  Per ogni corso: una riga col nome del corso, una riga per anno accademico
  (1..5) codice del corso e numero di lezioni in orario richieste.
  Per ogni lezione: una riga con giorno (2 caratteri iniziali) e orario
  (dalle 8:30 alle 18:30, lezioni di due ore, nel formato hh:mm-hh:mm).
  Per ogni aula una riga con il nome o codice dell'aula;

  Si richiede un programma che, letto il file, verifichi la compatibilita' 
  tra le richieste e assegni le aule ai corsi, cercando di mantenere nella
  stessa aula corsi consecutivi dello stesso anno accademico.
  Non e' ammessa la contemporaneita' di corsi diversi per lo stesso
  anno accademico.

  Si stampi poi l'oriario su un file di uscita.

*/


#include <stdio.h>

#define GIORNI 5
#define ORE    5
#define ANNI   5
#define CODL   10

#define VUOTA -1
#define PIENA 1

#define MAXAULE ANNI

#define MAXRIGA 40


struct lezione {
  int materia;
  int aula;
};

char giorni[GIORNI][3] = {"LU","MA","ME","GI","VE"};
char ore[ORE][12] = {"8:30-10:30","10:30-12:30","12:30-14:30",
		     "14:30-16:30","16:30-18:30"};

void svuota_orario (struct lezione orario[ANNI][GIORNI][ORE]);
void assegna_aule (struct lezione orario[ANNI][GIORNI][ORE], int naule);
void stampa_orario (FILE *fp, struct lezione orario[ANNI][GIORNI][ORE],
		    char **corsi, char aule[ANNI][CODL]);
void converti_richiesta (char *riga, int *pg, int *po);


int main (void)
{
  char riga[MAXRIGA];
  char **corsi;
  char aule[MAXAULE][CODL];
  struct lezione orario[ANNI][GIORNI][ORE];
  int i, anno, nrich, giorno, ora, ncorsi, naule;
  FILE *fp;

  printf ("file con richieste: ");
  gets (riga);

  fp = fopen (riga, "r");
  if (fp == NULL) {
    printf ("errore in apertura di %s\n", riga);
    return (1);
  }

  fgets (riga, MAXRIGA, fp);
  sscanf (riga, "%d %d", &ncorsi, &naule);
  if (naule > MAXAULE) {
    printf ("Numero di aule superiore a %d.", MAXAULE);
    printf ("Si useranno solo le  prime\n");
    naule = MAXAULE;
  }

  corsi = (char **) malloc (ncorsi * sizeof (char *));
  if (corsi == NULL) {
    printf ("memoria dinamica insufficiente");
    return (1);
  }

  svuota_orario (orario);

  for (i=0; i<ncorsi; i++) {
    fgets (riga, MAXRIGA, fp);
    corsi[i] = (char *) malloc (sizeof (char) * (strlen (riga)+1));
    if (corsi[i] == NULL) {
      printf ("memoria dinamica insufficiente");
      return (1);
    }
    if (riga[strlen(riga)-1] == '\n')
      riga[strlen(riga)-1] = '\0';
    strcpy (corsi[i], riga);
    fgets (riga, MAXRIGA, fp);
    sscanf (riga, "%d %*s %d", &anno, &nrich);

    for (; nrich>0; nrich--) {
      fgets (riga, MAXRIGA, fp);
      converti_richiesta (riga, &giorno, &ora);
      if (orario[anno-1][giorno][ora].materia != VUOTA) /* gia' assegnata */
	printf ("richiesta non soddisfacibile: %s. Viene ignorata\n", riga);
      else
	orario[anno-1][giorno][ora].materia = i;
    }
  }

  for (i=0; i<naule; i++)
    fgets (aule[i], MAXRIGA, fp);

  fclose (fp);

  assegna_aule (orario, naule);

  printf ("file per orario: ");
  gets (riga);

  fp = fopen (riga, "w");
  if (fp == NULL) {
    printf ("errore in apertura di %s\n", riga);
    return (1);
  }

  stampa_orario (fp, orario, corsi, aule);

  fclose(fp);

}

void svuota_orario (struct lezione orario[ANNI][GIORNI][ORE])
{
  int i, j, k;

  for (i=0; i<ANNI; i++)
    for (j=0; j<GIORNI; j++)
      for (k=0; k<ORE; k++) {
	orario[i][j][k].materia = VUOTA;
	orario[i][j][k].aula = VUOTA;
      }
}

void assegna_aule (struct lezione orario[ANNI][GIORNI][ORE], int naule)
{
  int i, j, k, l;
  int aula[MAXAULE];

  for (j=0; j<GIORNI; j++) {
    for (k=0; k<ORE; k++) {
      for (i=0; i<naule; i++)
	aula[i] = VUOTA;
      if (k>0)
	for (i=0; i<ANNI; i++)
	  if ((orario[i][j][k-1].materia != VUOTA) &&
              (orario[i][j][k].materia != VUOTA)) {
	    orario[i][j][k].aula = orario[i][j][k-1].aula;
            aula[orario[i][j][k].aula] = PIENA;
          }
      for (i=0; i<ANNI; i++)
	if ((orario[i][j][k].materia != VUOTA) &&
	    (orario[i][j][k].aula == VUOTA)) {
	  for (l=0; l<naule; l++)
	    if (aula[l] == VUOTA) {
	      aula[l] = PIENA;
	      orario[i][j][k].aula = l;
	      break;
	    }
	  if (l >= naule)
	    printf ("impossibile trovare un'aula!\n");
	}
    }
  }

}

void stampa_orario (FILE *fp, struct lezione orario[ANNI][GIORNI][ORE],
		    char **corsi, char aule[ANNI][CODL])
{
  int i, j, k, l;

  for (i=0; i<ANNI; i++) {
    fprintf (fp, "************** ANNO %d **************\n", i);
    for (j=0; j<GIORNI; j++) {
      fprintf (fp, "giorno: %s\n", giorni[j]);
      for (k=0; k<ORE; k++) {
	if (orario[i][j][k].materia != VUOTA)
	  fprintf (fp, "[%s] <%20s> aula %s\n",
	    ore[k], corsi[orario[i][j][k].materia],
		    aule[orario[i][j][k].aula]);
      }
    }
  }

}

void converti_richiesta (char *riga, int *pg, int *po)
{
  int i;

  for (i=0; i<GIORNI; i++)
    if (strncmp (riga, giorni[i], strlen(giorni[i])) == 0)
      break;
  *pg = i;
  for (i=0; i<ORE; i++)
    if (strncmp (&riga[3], ore[i], strlen(ore[i])) == 0)
      break;
  *po = i;
  if ((*pg >= GIORNI) || (*po >= ORE)) {
    printf ("formato scorretto per la richiesta: %s\n", riga);
    exit (1);
  }
}

