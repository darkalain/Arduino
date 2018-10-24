
#ifndef _MATRICE_SPI_ABE_H
	#define	_MATRICE_SPI_ABE_H
	#include <inttypes.h>
	#include <Arduino.h>
	#include <SPI.h>
	
	class MATRICE_SPI_ABE
	{
		public : 
			MATRICE_SPI_ABE(uint8_t cs);
			void Init(void);
			void SendMatrix( char m[8][8]) ;
			void IntensitySet( uint8_t percentage);
			void MatrixClear(void);
			void LedClear(uint8_t line, uint8_t row);
			void LedSet( uint8_t line , uint8_t row);
			void RowSet(uint8_t row);
			void LineSet(uint8_t line);
		
		private : 
			void RazMatrix(void);
			void SPISend(uint8_t ByteH , uint8_t ByteL);
		
			int PIN_CS;
			uint8_t MATRIX[8][8];
	};
#endif