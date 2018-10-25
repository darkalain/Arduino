#include <MATRICE_SPI_ABE.h>

MATRICE_SPI_ABE matrice(2) ;
char mat[8][8] = {
 { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 } ,
 { 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 } ,
 { 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0 } ,
 { 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 } ,
 { 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 } ,
 { 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0 } ,
 { 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 } ,
 { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 } 
};

char mat2[8][8] = {
 { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ,
 { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 } ,
 { 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 } ,
 { 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 } ,
 { 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 } ,
 { 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 } ,
 { 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 } ,
 { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } 
};

void setup() 
{
  matrice.Init();
}

void loop() 
{
  while(1)
  {
    matrice.SendMatrix(mat);
    delay(1000);
    matrice.SendMatrix(mat2);
    delay(1000);
  }
  while(1);
}
