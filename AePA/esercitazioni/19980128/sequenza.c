/********************************************************************/
/**                          SEQUENZA.C                            **/
/**             soluzione compito del 28/1/98: es. 2               **/
/********************************************************************/
/*
Il valore S dipende dall'ordine degli importi.
Si richiede di trovare l'ordine in grado di fornire il minimo per S.
Essendo Ci = C0+(somma dei primi i importi), Ci-C0 risulta
indipendente da C0. Per semplicita' si supporra' quindi nella soluzione C0=0.
La soluzione proposta usa un approccio recursivo in grado di
percorrere tutti i possibili ordinamenti, di costo O(N!). Si adotta
come ottimizzazione l'abbandono di una strada qualora (in un passo 
intermedio) questa risulti gia' peggiore del minimo provvisorio.
Non si propone programmazione dinamica (approccio possibile) per la 
difficolta' di caratterizzare i sottoproblemi (tutti i possibili 
sotto-insiemi di N numeri).
Sono possibili approcci di tipo greedy, che, pur se di costo 
inferiore, non garantiscono, in generale, la soluzione ottima.
Si utilizzano variabili globali.
*/

#include <stdio.h>

#define MAX     100	/* max numero movimenti */
#define PRESO   10000	/* un intero fuori dagli importi ammessi */

int   leggi_dati(char *file)
void  solve (int posizione);
void 	salva_soluzione (void);

int curr_S, best_S, cassa, n_movimenti;
int	vett[MAX], solut[MAX], best_solut[MAX];

void main (char **argv, int argc)
{
  n_movimenti = leggi_file(argv[1]);
  solve(0);
  stampa_soluzione();
}

int leggi_dati(char *file)
{
  int i;
  FILE *fp;

  fp = fopen(file,"r");
  if (fp == NULL) return 0;
  for (i=0; (fscanf("%d", &vett[i])>0); i++);
  fclose(fp);
  return i;
}
void 	salva_soluzione (void)
{
  int i;
  for(i=0;i<n_movimenti;i++)
    best_solut[i]=solut[i];
}
void 	stampa_soluzione (void)
{
  int i;
  for(i=0;i<n_movimenti;i++)
    printf("%d\n", best_solut[i]);
}

void solve (int posizione)
{
   int	i, importo;

   if(posizione > n_movimenti) {
     if (curr_S < best_S) {
       best_S = curr_S;
       salva_soluzione();
       return;
     }
   }
   for (i=0; i<n_movimenti; i++) {
     if (vett[i] != PRESO) {
       /* prova tutti i movimenti non ancora presi */
       importo = solut[posizione] = vett[i];
       vett[i] = PRESO;
       cassa += importo;
       curr_S += cassa*cassa;
       /* recursione solo se c'e' speranza di migliorare */
       if (curr_S < best_S)
         solve(posizione+1);
       /* riporta curr_S, cassa e vett[i] ai valori precedenti */
       curr_S -= cassa*cassa;
       cassa -= importo; 
       vett[i] = solut[posizione]; 
    }
   }
}