/*********************************
****** AUTHOR : Alain Béger ******
**********************************
******* UTILISATION SIMPLE *******
*** D'UN AFFICHEUR MATRICIELLE ***
********** VIA BUS SPI ***********
*********************************/

#include "MATRICE_SPI_ABE.h"





MATRICE_SPI_ABE::MATRICE_SPI_ABE(uint8_t cs)
{
	PIN_CS = cs;	// définit la broche du Chip Select
	SPI.setBitOrder(MSBFIRST);	// définit que le bit de poids fort est envoyé en premier jusqu'au LSB
	SPI.begin();	// Démarre la liaison SPI
	pinMode( PIN_CS , OUTPUT);	// passage de la broche Chip Select en Sortie
	digitalWrite( PIN_CS , HIGH);	// Mise à '1' par défaut de la ligne CS
	RazMatrix();	// Remise à zéro de la matrice logicielle en RAM
}



// Initialisation de l'afficheur matricielle
void MATRICE_SPI_ABE::Init(void)
{
	SPISend( 0x0C , 0x01 ); // Normal operation
	SPISend( 0x0B , 0x07 );	// On active les 8 digits (colonne)
	SPISend( 0x09 , 0x00 );	// On ne souhaite pas de décodage BCD, on travail en matrice
	MatrixClear();			// On efface la matrice
}


// Permet d'envoyer un tableau deux dimensions (matrice) avec '1' pour allumer et '0' pour éteindre
void MATRICE_SPI_ABE::SendMatrix( char m[8][8])
{
	int i = 0; 
	int j = 0;
	for ( i=0 ; i<8 ; i++ )
		for ( j=0 ; j<8 ; j++ )
			if( MATRIX[i][j] != m[i][j] )
				if( m[i][j] == 1 )
					LedSet(i,j);
				else
					LedClear(i,j);
}


// Permet de configurer l'intensité (la puissance) de l'afficheur matriciel
void MATRICE_SPI_ABE::IntensitySet( uint8_t percentage )
{
	float tmp = 0;
	uint8_t per = 0;
	tmp = (float)percentage / 16.6;
	per = (uint8_t) tmp;
	SPISend( 0x0A , per );
}


// Permet d'effacer l'afficheur matriciel
void MATRICE_SPI_ABE::MatrixClear( void )
{
	uint8_t i = 0;
	for( i=0 ; i<8 ; i++ )
		SPISend( i+1 , 0 );
	RazMatrix();
}


// Permet d'effacer une led de l'afficheur matriciel
void MATRICE_SPI_ABE::LedClear( uint8_t line , uint8_t row )
{
	int i = 0;
	uint8_t tmp = 0x00;
	
	if( (line<0) || (line>7) || (row<0) || (row>7) ) return;
	if( MATRIX[line][row] == 0 ) return;
	for( i=0 ; i<8 ; i++ )
		if( MATRIX[i][row] != 0 )
			tmp = tmp + (1<<i);
	tmp = tmp - (1<<line);
	MATRIX[line][row] = 0 ;
	SPISend( row+1 , tmp);
}


// Permet d'allumer une led de l'afficheur matriciel
void MATRICE_SPI_ABE::LedSet( uint8_t line , uint8_t row )
{
	int i = 0;
	uint8_t tmp = 0x00;
	
	if( (line<0) || (line>7) || (row<0) || (row>7) ) return;
	if( MATRIX[line][row] == 1 ) return;
	for( i=0 ; i<8 ; i++ )
		if( MATRIX[i][row] != 0)
			tmp = tmp + (1<<i);
	tmp = tmp + (1<<line);
	MATRIX[line][row] = 1;
	SPISend( row+1 , tmp);
}


// Permet d'allumer une colonne
void MATRICE_SPI_ABE::RowSet(uint8_t row)
{
	int i = 0;
	for( i=0 ; i<8 ; i++ )
		LedSet( i , row );
}


// Permet d'allumer une ligne
void MATRICE_SPI_ABE::LineSet( uint8_t line)
{
	int i = 0;
	for( i=0 ; i<8 ; i++ )
		LedSet( line , i );
}





// private
void MATRICE_SPI_ABE::RazMatrix(void)
{
	int i = 0;
	int j = 0;
	for( i=0 ; i<8 ; i++ )
		for( j=0 ; j<8 ; j++ )
			MATRIX[i][j] = 0;
}

void MATRICE_SPI_ABE::SPISend( uint8_t ByteH , uint8_t ByteL )
{
	uint16_t tmp = 0x0000;
	tmp = ByteH;
	tmp = tmp<<8;
	tmp = tmp | ((uint16_t)ByteL&0x00FF);
	digitalWrite( PIN_CS , LOW );
	SPI.transfer16( tmp );
	digitalWrite( PIN_CS , HIGH );
}





