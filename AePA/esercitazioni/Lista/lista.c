/********************************************************************/
/**                           LISTA.C                              **/
/********************************************************************/

#include <stdio.h>

#include "dato.h"
#include "lista.h"

static nodo_t *alloca (void);


nodo_t *crea_lista_vuota (void)
{
  return NULL;
}

int cerca (nodo_t *hp, dato_t dato)
{
  nodo_t *p;

  for (p = hp; (p != NULL)&&(precede (p->val, dato)); p = p->punt);

  if ((p != NULL)&&(uguali (p->val, dato)))
    return 1;
  else  
    return 0;
}

nodo_t *cancella (nodo_t *hp, dato_t dato)
{
  nodo_t *p, *q0, *q1;

  /* Lista vuota */
  if (hp == NULL) {
    printf ("ATTENZIONE: dato inesistente\n");
    return hp;
  }
  /* Cancella in testa */
  if (uguali (dato, hp->val)) {
    p = hp->punt;
    free (hp);
    return p;
  }  

  /* Cancella in mezzo o in coda. Percorrimento con doppio puntatore:
     q0 e q1 puntano a due nodi consecutivi, al momento dell'inserimento
     q0 punta al nodo precedente, q1 al nodo da cancellare
   */
  q0 = hp; q1 = hp->punt;   
  /* cerca posizione - eventualmente fine lista (q1 == NULL) */
  while ((q1 != NULL)&&(precede (q1->val, dato))) {
    q0 = q1;
    q1 = q1->punt;
  }
  if ((q1 != NULL)&&(uguali (q1->val, dato))) {
    /* cancella */
    q0->punt = q1->punt;
    free (q1);
  }
  else  
    printf ("ATTENZIONE: dato inesistente\n");

  /* hp non viene modificato */
  return hp;
}

nodo_t *inserisci (nodo_t *hp, dato_t dato)
{
  nodo_t *p, *q0, *q1;

  p = alloca ();
  p->val = dato;

  /* Lista vuota */
  if (hp == NULL) {
    p->punt = NULL;
    return p;
  }
  /* Inserimento in testa */
  if (precede (dato, hp->val)) {
    p->punt = hp;
    return p;
  }  
  /* Inserimento in mezzo o in coda. Percorrimento con doppio puntatore:
     q0 e q1 puntano a due nodi consecutivi, al momento dell'inserimento
     q0 punta al nodo precedente, q1 al successivo 
   */
  q0 = hp; q1 = hp->punt;   
  /* cerca posizione - eventualmente fine lista (q1 == NULL) */
  while ((q1 != NULL)&&(precede (q1->val, dato))) {
    q0 = q1;
    q1 = q1->punt;
  }
  /* inserisce */
  q0->punt = p;
  p->punt = q1;
  
  /* hp non viene modificato */
  return hp;
}

void stampa_lista (FILE *fp, nodo_t *hp)
{
  while (hp != NULL) {
    stampa_dato (fp, hp->val);
    hp = hp->punt;
  }
}

nodo_t *leggi_lista (FILE *fp)
{
  nodo_t *p, *hp, *tp;
  dato_t d;

  hp = tp = NULL;

  while (!feof (fp)) {

    /* acquisisci dato */
    d = leggi_dato (fp);
    p = alloca ();
    p->val = d;
    p->punt = NULL;
    
    /* inserisci in coda */
    if (tp == NULL)
      hp = tp = p;
    else {
      tp->punt = p;
      tp = p;
    }

  }

  return hp;
}



static nodo_t *alloca (void)
{
  nodo_t *p;

  p = (nodo_t *) malloc (sizeof (nodo_t));
  if (p == NULL) {
    printf ("ERRORE: memoria dinamica insufficiente\n");
    exit (1);
  }

  return p;
}    


