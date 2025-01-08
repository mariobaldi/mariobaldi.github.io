/********************************************************************/
/**                     DATO.H per char *                          **/
/********************************************************************/

#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

typedef char *dato_t;

dato_t leggi_dato (FILE *fp);
void stampa_dato (FILE *fp, dato_t dato);
int precede (dato_t d1, dato_t d2);
int uguali (dato_t d1, dato_t d2);

#endif
