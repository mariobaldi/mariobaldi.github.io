/*****************************************************************************

				8regine.C

PROBLEMA DELLE 8 REGINE

*******************************************************************************/
#include <stdio.h>

int	queen[8];
char 	row[8],
	dia[15],
	revdia[15];

int muovi( int);
void setqueen( int, int);
void removequeen( int, int);

main()
{
int	i;

   if( muovi( 0))
      for( i=0; i<8; i++)
         printf( "%d ", queen[i]);
}


int muovi( int n)
{
int i;

   if( n == 8)
      return( 1);
   for( i=0; i<8; i++)
      if( !row[i] && !dia[n+i] && !revdia[n-i+7])
      {
         setqueen( n, i);
         if( muovi( n+1))
            return( 1);
         removequeen( n, i);
      }        
   return( 0);
}

void setqueen( int n, int i)
{
         queen[n] = i;
         row[i] = 255;
         dia[n+i] = 255;
         revdia[n-i+7] = 255;
}



void removequeen( int n, int i)
{
         queen[n] = 0;
         row[i] = 0;
         dia[n+i] = 0;
         revdia[n-i+7] = 0;
}


