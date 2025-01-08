/*  컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�  */
/*                          File  Dato.h                                 */
/*                                                                       */
/*         Dichiarazione dei prototipi per il modulo Dato.c              */
/*  컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�  */


#ifndef _dato_included  /* controlla se la libreria e stata gia inclusa */
#define _dato_included

/* -  Visibilita di altre librerie - */
  #include <stdio.h>
  #include <stdlib.h>

/* Numero Max di elementi da poter mettere in coda */
#define Max_Element 1000
#define INFINITY 0x1FFF
#define MAX_LUN 80
#define nomefile "c:\\poli\\fondam~1\\progra~1\\dati.dat"


typedef enum {E_DISK,E_MEM,E_SINT,FULL,NIL} error;
typedef enum {FALSE,TRUE} boolean; /* Tipo booleano */

                          /*  Tipi definiti di errori standard */


/*  Struttura dati per la memorizzazione dell'ora  */
/*  Formato hh:mm                                  */

typedef struct {
                  int  hh;
                  int  mm;
               } Tipo_ora;

/*  Struttura dati per la memorizzazione del tempo */
/*  Formato gg:hh:mm                               */

typedef struct {
                 int   gg;
                 int   hh;
                 int   mm;
                }  Tipo_durata;


/* Struttura dati generale */

/* Definizine degli aeroporti  */

typedef struct {
                  char             *name;
                  char          sigla[3];
                  int               fuso;
                  int           *adjlist;
                  int           num_link;
                  boolean         visita;
                } Tipo_Aeroporto;


/* Definizine Compagnie aeree */

typedef struct {
                  char             *name;
                  char          sigla[3];
               }  Tipo_Compagnia;


/* Struttura dati per le citta da visitare */
typedef struct {
                  int           citta;
                  Tipo_ora      min_permanenza;

               }  Tipo_Visita;

/* Struttura Dati  voli esistenti */

typedef struct {
                  int               num_volo;
                  int               partenza;
                  int                 arrivo;
                  int             compagnia;
                  Tipo_ora      ora_partenza;
                  Tipo_ora            durata;
               } Tipo_Volo;


/* Dichiarazione dei prototipi del modulo Dato.c */

error carica_dati(char *nomefiles);
error carica_viaggio(void);

#endif