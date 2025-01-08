/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  */
/*                        Politecnico di Torinio                            */
/*                        Ingegneria Infomatica                             */
/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  */
/*              Fondamenti di informatica II                                */
/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  */
/*             Prova di programmazione in C del 24/09/95                    */
/*                                                                          */
/*  Realizzato da : Fiume                 Antonino  Matr. 90030             */
/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  */


/* ÄÄ  Inclusione delle Librerie per la gestione modulare  ÄÄÄ */

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <string.h>
#include "dato.h"

/* Puntatore alla struttura dati degli aeroporti */
   extern Tipo_Aeroporto  *Data_Aeroporto;
 /* Puntatore alla struttura dati delle compagnie aeree */
   extern Tipo_Compagnia  *Data_Compagnia;
 /* Puntatore alla struttura dati dei voli  */
   extern Tipo_Volo       *Data_Volo;
 /* Puntatore alla struttura del viaggio  */
   extern Tipo_Visita     *Data_Viaggio;

/*  struttura dati per la gestione della soluzione ottima */

   extern int   num_A;     /* numero di aeroporti */
   extern int   num_C;     /* numero di Compagnie */
   extern int   num_V;     /* numero di Voli      */
   extern int   count_A;   /* Contatori per i tre vettori */
   extern int   count_C;
   extern int   count_V;
   extern int   num_citta;



/* ÄÄ   Definizioni delle variabili globali al main ÄÄ */

   int  *voli_effettuati;
   int  *Viaggio_Ottimo;

/*   strutture per dati per il controllo del programma */
   int   n_visite=0;
   int   citta_visitate;
   Tipo_durata   durata_viaggio;
   Tipo_durata   durata;



/*  ----------------------------------------------------------- */
/*  ----     Somma un tempo in formato hh:mm              ----- */
/*  ----------------------------------------------------------- */

Tipo_durata somma(Tipo_durata Volo, Tipo_ora  durata)
  {  Tipo_durata  Temp;

     Temp.hh=Volo.hh+(Volo.mm+durata.mm)/60;
     Temp.mm=(Volo.mm+durata.mm) % 60;
     Temp.gg=Volo.gg+(Temp.hh+durata.hh)/24;
     Temp.hh=(Volo.hh+durata.hh) % 24;
     return(Temp);
  }

/*  ----------------------------------------------------------- */
/*  ----     Sottrae un tempo in formato hh:mm            ----- */
/*  ----------------------------------------------------------- */
Tipo_durata sottrai(Tipo_durata Volo, Tipo_ora  durata)
  {   Tipo_durata  Temp;

      Temp.gg=Volo.gg;
      Temp.mm=Volo.mm-durata.mm;
      Temp.hh=Volo.hh-durata.hh;
      if (Temp.mm<0)
	 {  Temp.hh--;  Temp.mm=Temp.mm+60;  }
      if (Temp.hh<0)
	 {  Temp.gg--;  Temp.hh=Temp.hh+24;  }
   return(Temp);
  }


/*  ----------------------------------------------------------- */
/*   ----     Fornisce la permanenza nella citt…         ------ */
/*  ----------------------------------------------------------- */
Tipo_ora Calcola_perm(int volo1, int volo2)
 {
   Tipo_durata Temp;
   Tipo_ora  value;
   Tipo_ora Fuso;
   Fuso.mm=0;

   Temp.gg=0;
   Temp.hh=Data_Volo[volo1].ora_partenza.hh;
   Temp.mm=Data_Volo[volo1].ora_partenza.mm;
   Temp=somma(Temp,Data_Volo[volo1].durata);
   Fuso.hh=Data_Aeroporto[Data_Volo[volo1].partenza].fuso-Data_Aeroporto[Data_Volo[volo1].arrivo].fuso;
   if (Fuso.hh<0)
      { Fuso.hh=Fuso.hh*(-1);
	Temp=sottrai(Temp,Fuso);
      }
  else
      Temp=somma(Temp,Fuso);

  if ((Temp.gg==0) && ((Temp.hh<Data_Volo[volo2].ora_partenza.hh) ||
		       ((Temp.hh==Data_Volo[volo2].ora_partenza.hh) &&
			 (Temp.mm<Data_Volo[volo2].ora_partenza.mm))))
       {
	value.hh=Temp.hh; value.mm=Temp.mm;
	Temp.hh=Data_Volo[volo2].ora_partenza.hh;
	Temp.mm=Data_Volo[volo2].ora_partenza.mm;
	}
  else
      {
	value.hh=Data_Volo[volo2].ora_partenza.hh;
	value.mm=Data_Volo[volo2].ora_partenza.mm;
	Temp.gg++;
    }
      Temp=sottrai(Temp,value);

  value.hh=Temp.hh;
  value.mm=Temp.mm;
  return(value);
 }

/*  ----------------------------------------------------------- */
/*  -----  Procedura recursiva per la visita delle citt…  ----- */
/*  ----------------------------------------------------------- */

void Visita(int citta, int volo)
  {  int k,j;
     int n_volo;
     boolean  visitare;
     Tipo_ora permanenza;

     if (citta==Data_Viaggio[0].citta)   /* sto arrivando o partendo ? */
       {
	 if (Data_Aeroporto[citta].visita==FALSE)   /* partenza */
	    {
	       durata.mm=0; durata.hh=0; durata.gg=0;
	       voli_effettuati[n_visite++]=citta;
	       Data_Aeroporto[citta].visita=TRUE;
	       for (k=0; k<Data_Aeroporto[citta].num_link; k++)
		{
		  n_volo=Data_Aeroporto[citta].adjlist[k];
		  Visita(Data_Volo[n_volo].arrivo,n_volo); /* Visito la prossima citta */
		}
	      Data_Aeroporto[citta].visita=FALSE;
	      n_visite--;
	     return;
	    }
	 else     /* arrivo */
	   {   /* controllo se Š la soluzione ottima */

	 for (j=0; j<num_citta; j++)   /*  Ho visitato tutte le citta */
	   if (Data_Aeroporto[Data_Viaggio[j].citta].visita==FALSE)
		     return;

	     durata=somma(durata,Data_Volo[volo].durata);
	     if ( (durata.gg<durata_viaggio.gg) ||  /* SOLUZIONE OTTIMA ? */
		  ( (durata.gg==durata_viaggio.gg) &&
		    (durata.hh<durata_viaggio.hh)) ||
		  ( (durata.gg==durata_viaggio.gg) &&
		    (durata.hh==durata_viaggio.hh) &&
		    (durata.mm<durata_viaggio.mm) ) )
	      {
		durata_viaggio=durata;
		citta_visitate=n_visite;
		for (k=0; k<n_visite; k++)
		    Viaggio_Ottimo[k]=voli_effettuati[k];
	      }
	     durata=sottrai(durata,Data_Volo[volo].durata);
	     return;
	   }
       }
    else  /* citt… di passagio */
      { /*  controllo se la citt… Š gia stata visitata */
	if (Data_Aeroporto[citta].visita==TRUE) return;

	Data_Aeroporto[citta].visita=TRUE;

       /* controllo se Š una delle citt… da visitare */
	 for (j=1,visitare=FALSE; ((j<num_citta) && (visitare==FALSE)); j++)
	   if (Data_Viaggio[j].citta==citta) visitare=TRUE;
	for (k=0; k<Data_Aeroporto[citta].num_link; k++)
	     {   n_volo=Data_Aeroporto[citta].adjlist[k];
		 permanenza=Calcola_perm(volo,n_volo);

		    /* considero tutti i vincoli sulla permanenza in una citt… */
		if (((visitare==FALSE) && (permanenza.hh>=1)) ||  /* citt… non in lista per. > 1h */
		   ((visitare==TRUE) &&  /* citt… da visitare */
		   ( (permanenza.hh>Data_Viaggio[j-1].min_permanenza.hh) ||
		    ( (permanenza.hh==Data_Viaggio[j-1].min_permanenza.hh) &&
		      (permanenza.mm>=Data_Viaggio[j-1].min_permanenza.mm) ) ) ) )
		    {

		       voli_effettuati[n_visite++]=citta;
		       durata=somma(durata,Data_Volo[volo].durata);
		       durata=somma(durata,permanenza);
		       /* Itero alla prossima citt… */
		       Visita(Data_Volo[n_volo].arrivo,n_volo); /* Visito la prossima citt… */
		       /* ripristino variavile globali di recursione */
		       durata=sottrai(durata,Data_Volo[volo].durata);
		       durata=sottrai(durata,permanenza);
		       n_visite--;
		    }
	     }
       Data_Aeroporto[citta].visita=FALSE;
       return;
      }
  }

/*  ----------------------------------------------------------- */
/* -----            Procedura attiva Visita             --------*/
/*  ----------------------------------------------------------- */
error Attiva(void)
 {  int k;
    /* Riservo lo spazio per tenere traccia della soluzione ottima
    trovata */
    if  ((voli_effettuati=(int *)malloc(num_A*sizeof(int)))==NULL)
	return(E_MEM);
    if  ((Viaggio_Ottimo=(int *)malloc(num_A*sizeof(int)))==NULL)
	return(E_MEM);

    durata_viaggio.gg=INFINITY;
    durata_viaggio.hh=INFINITY;
    durata_viaggio.gg=INFINITY;
    citta_visitate=INFINITY;
    Visita(Data_Viaggio[0].citta,0);
    if (citta_visitate==INFINITY)
      printf("\nNon esiste soluzione al problema dato.");
    else
      {
	 for (k=0; k<citta_visitate; k++)
	   printf("\n%s",Data_Aeroporto[Viaggio_Ottimo[k]].name);
	   printf("\n%s",Data_Aeroporto[Viaggio_Ottimo[0]].name);
	   printf (" \n\n La durate totola Š : %d gg - %d hh - %d mm ",
						      durata_viaggio.gg,
						      durata_viaggio.hh,
						      durata_viaggio.mm);
    }

   return(NIL);
 }


/*  ----------------------------------------------------------- */
/*  -----------   Gestione degli errori               --------- */
/*  ----------------------------------------------------------- */
void Error(error punt)
 {  switch (punt) {
     case E_MEM  : {
		     printf("\nErrore di allocazione in memoria");
		     exit(-1);
		   } break;
     case E_DISK  : {
		     printf("\nErrore di apertura file");
		     exit(-1);
		    } break;
		 }
 }

/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  */
/*  Programma Principale per la gestione del programma     */
/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  */
void main (void)
 { int k;
	    Error(carica_dati(nomefile));
	    Error(carica_viaggio());
	    Error(Attiva());
 }