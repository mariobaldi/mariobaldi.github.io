/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  */
/*                          File  Dato.c                                  */
/*    Gestione di tutte le procedure di manipolazione, salvataggio e      */
/*    acquisizione dati da dispositivi esterni (Tastiera o File)          */
/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  */

/* -  Visibilita di altre librerie - */
  #include "dato.h"
  #include <stdio.h>
  #include <string.h>
  #include <conio.h>
  #include <ctype.h>

 /* Puntatore alla struttura dati degli aeroporti */
   Tipo_Aeroporto  *Data_Aeroporto;
 /* Puntatore alla struttura dati delle compagnie aeree */
   Tipo_Compagnia  *Data_Compagnia;
 /* Puntatore alla struttura dati dei voli  */
   Tipo_Volo       *Data_Volo;
 /* Puntatore alla struttura del viaggio  */
   Tipo_Visita     *Data_Viaggio;

/*  struttura dati per la gestione della soluzione ottima */

   int   num_A=0;     /* numero di aeroporti */
   int   num_C=0;     /* numero di Campagnie */
   int   num_V=0;     /* numero di Voli      */
   int   count_A=0;   /* Contatori per i tre vettori */
   int   count_C=0;
   int   count_V=0;
   int   num_citta;

    /*  --------------------------------------------- */
    /*  Dichiarazioen delle strutture dati utilizzate */
    /*  --------------------------------------------- */


/**************************************************************/
/*     Procedura la ricerca  nell'Hash dell'indice            */
/*            dell'aeroporto richiesto                        */
/***************************************************************/
int ricerca(char *sigla)
 { int k;

   for (k=(sigla[0]+sigla[1]) % num_A;
        ( (strcmp(Data_Aeroporto[k].sigla,sigla)!=0) && (strcmp(Data_Aeroporto[k].sigla,"")));
          k=(k+1) % num_A );
  return k;
 }


/**************************************************************/
/*     Procedura per il caricamento dell'ora                 */
/**************************************************************/
Tipo_ora carica_ora(char *stringa)
 {
    char hh[3],mm[3];
    Tipo_ora Temp;

    strncpy(hh,stringa,2);  hh[2]='\0';
    strcpy(mm,stringa+3);   mm[2]='\0';
    Temp.hh=atoi(hh);
    Temp.mm=atoi(mm);

    return Temp;
 }



/**************************************************************/
/*     Procedura per il caricamento dei Dati da File          */
/**************************************************************/
error carica_dati(char *nomefiles)

{  FILE *fin;

   int   k,j;
   char  sigla[3];

   /*   Stringhe temporanee utilizzate nel caricamento dei dati */
   char stringa[MAX_LUN], stringa1[MAX_LUN], stringa2[MAX_LUN];

   /*  Apertura del File */
   if ((fin=fopen(nomefiles, "r")) == NULL)
   {
      printf ("Errore in apertura file %s\n", nomefile);
      return(E_DISK);
   }

      /*  Stabilisco il numero di aeroporti */
     strcpy(stringa,"");
     while ((strcmp(stringa,"\n")!=0) && (!feof(fin)))
      {
         fgets(stringa,MAX_LUN,fin);
         if (strcmp(stringa,"\n")!=0) num_A++;   /* Incremento contatore Aeroporto */
       }
     while (!feof(fin))
     {
        fgets(stringa,MAX_LUN,fin);
        if(strcmp(stringa,"\n")!=0) num_C++;    /* Incremento contatore Compagnia */
        while ((strcmp(stringa,"\n")!=0) && (!feof(fin)))
           {
              fgets(stringa,MAX_LUN,fin);
              if (strcmp(stringa,"\n")!=0) num_V++;
            }
     }

   /* Alloco in memoria la struttura dati necessaria  */

   if ((Data_Aeroporto=(Tipo_Aeroporto *)malloc(num_A*sizeof(Tipo_Aeroporto)))==NULL)
      return(E_MEM);

   if ((Data_Compagnia=(Tipo_Compagnia *)malloc(num_C*sizeof(Tipo_Compagnia)))==NULL)
      return(E_MEM);

   if ((Data_Volo=(Tipo_Volo *)malloc(num_V*sizeof(Tipo_Volo)))==NULL)
      return(E_MEM);



   /* Mi riporto alla testa del File */

   rewind(fin);

    /*  Carico il numero di aeroporti */

     for (k=0; k<num_A; k++)   /* Azzero la key dell'hash */
       strcpy(Data_Aeroporto[k].sigla,"");

     strcpy(stringa,"");
     while ((strcmp(stringa,"\n")!=0) && (!feof(fin)))
      {
           fgets(stringa,MAX_LUN,fin);
           if (strcmp(stringa,"\n")!=0)
            {
             strncpy(sigla,stringa,2);
             sigla[2]='\0';

             /* ----  Inserisco l'elemento in un Hash  ---- */

             count_A=ricerca(sigla);
             strcpy(Data_Aeroporto[count_A].sigla,sigla);
             strncpy(stringa1,&stringa[3],strlen(stringa)-7);
             stringa1[strlen(stringa)-7]='\0';
             if ((Data_Aeroporto[count_A].name=(char *)malloc((strlen(stringa1)+1)*sizeof(char)))==NULL)
                   return(E_MEM);
             strcpy(Data_Aeroporto[count_A].name,stringa1);
             sscanf(&(stringa[strlen(stringa)-3]),"%d",&(Data_Aeroporto[count_A].fuso));
             Data_Aeroporto[count_A].num_link=0;
            }
       }

     while (!feof(fin))
     {
        fgets(stringa,MAX_LUN,fin);
        if(strcmp(stringa,"\n")!=0)  /* Carico la Compagnia aerea */
           {
              strncpy(Data_Compagnia[count_C].sigla,stringa,2);
              Data_Compagnia[count_C].sigla[2]='\0';
              strcpy(stringa1,&stringa[3]); stringa[strlen(stringa1)]='\0';

              if ((Data_Compagnia[count_C].name=(char *)malloc((strlen(stringa1)+1)*sizeof(char)))==NULL)
                     return(E_MEM);
             strcpy(Data_Compagnia[count_C].name,stringa1);
             Data_Compagnia[count_C].name[strlen(stringa1)-1]='\0';

             count_C++;    /* Incremento contatore Compagnia */
           }
        while ((strcmp(stringa,"\n")!=0) && (!feof(fin)))
           {
              fgets(stringa,MAX_LUN,fin);
              if (strcmp(stringa,"\n")!=0)
                 {
                  sscanf(stringa,"%d",&(Data_Volo[count_V].num_volo));
                  /* Link all'aeroporto di partenza */
                  strcpy(stringa,strstr(stringa," ")+1);
                  strncpy(sigla,stringa,2);
                  sigla[2]='\0';
                  Data_Volo[count_V].partenza=ricerca(sigla);
                  Data_Aeroporto[ricerca(sigla)].num_link++;

                  /* Link all'aeroporto di arrivo */
                  strcpy(stringa,strstr(stringa," ")+1);
                  strncpy(sigla,stringa,2);
                  sigla[2]='\0';
                  Data_Volo[count_V].arrivo=ricerca(sigla);

                  /* Link compagnia */
                  Data_Volo[count_V].compagnia=count_C-1;

                  strcpy(stringa,strstr(stringa," ")+1);

                  strcpy(stringa1,stringa+6); /* stringa durata volo  */
                  stringa[6]='\0';            /* stringa partenza     */

                  Data_Volo[count_V].ora_partenza=carica_ora(stringa);
                  Data_Volo[count_V].durata=carica_ora(stringa1);
                  count_V++;
                 }
             }
     }
   close(fin);

 /*   Creo la lista di adiacenza di ogni aeroporto con gli altri */
 for (k=0; k<num_A; k++)
   {
   if ((Data_Aeroporto[k].adjlist=(int *)malloc(Data_Aeroporto[k].num_link*sizeof(int)))==NULL)
     return (E_MEM);
   Data_Aeroporto[k].num_link=0;
   Data_Aeroporto[k].visita=FALSE;
   }

  /*  Costruisco la lista di adiacenza */
  for (k=0; k<num_V; k++)
    {
      Data_Aeroporto[Data_Volo[k].partenza].adjlist[Data_Aeroporto[Data_Volo[k].partenza].num_link++]=k;
    }
 return(NIL);
}

/**************************************************************/
/*     Procedura per il caricamento del viaggio da tastiera   */
/**************************************************************/

error carica_viaggio(void)
{
   int   k,j;
   char  sigla[3];
   char stringa[MAX_LUN], stringa1[MAX_LUN], stringa2[MAX_LUN];

   /*  Apertura del File */
   printf("\nInserisci il numero di citta da visitare : ");
   scanf("%d%*c",&num_citta);

    if ((Data_Viaggio=(Tipo_Visita *)malloc(num_citta*sizeof(Tipo_Visita)))==NULL)
       return(E_MEM);

   for (k=0; k<num_citta; k++)
    {
      if (k==0)
        {
           printf("\n Sigla %dø Citta <__>",k);
           gets(stringa);
           stringa[2]='\0';
           Data_Viaggio[k].citta=ricerca(stringa);
        }
      if (k!=0)
        {
           printf("\n Sigla %dø Citta <__> Durata Volo <hh:mm> \n",k);
           gets(stringa);
           strncpy(sigla,stringa,2); sigla[2]='\0';
           Data_Viaggio[k].citta=ricerca(sigla);
           strcpy(stringa,stringa+3);
           Data_Viaggio[k].min_permanenza=carica_ora(stringa);
        }
    }
  return(NIL);
 }