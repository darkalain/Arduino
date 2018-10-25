#include <MATRICE_SPI_ABE.h>

MATRICE_SPI_ABE afficheur(2) ;

void setup() 
{
  afficheur.Init();
}

void loop() 
{
  int i = 0;

  for(;;)
  {
    for( i=0 ; i<101 ; i+=10)
    {
      afficheur.IntensitySet((uint8_t)i);
      afficheur.RowSet( 4 );
      afficheur.LineSet( 3 );
      afficheur.LineSet( 4 );
      afficheur.LedSet( 1,5 );
      afficheur.LedSet( 2,5 );
      afficheur.LedSet( 2,6 );
      afficheur.LedSet( 6,5 );
      afficheur.LedSet( 5,5 );
      afficheur.LedSet( 5,6 );
      delay(1000);
      afficheur.MatrixClear();
      delay(1000);
    }
  }
}





