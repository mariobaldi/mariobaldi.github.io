/********************************************************************/
/**                           LISTA.H                              **/
/********************************************************************/

#ifndef _LISTA_INCLUDED
#define _LISTA_INCLUDED

#include "dato.h"

typedef struct nodo {
  dato_t       val;
  struct nodo *punt;
} nodo_t;

nodo_t *crea_lista_vuota (void);
nodo_t *inserisci (nodo_t *hp, dato_t dato);
void stampa_lista (FILE *fp, nodo_t *hp);
int cerca (nodo_t *hp, dato_t dato);
nodo_t *cancella (nodo_t *hp, dato_t dato);
nodo_t *leggi_lista (FILE *fp);

#endif
