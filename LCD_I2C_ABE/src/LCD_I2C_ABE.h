


#ifndef	_LCD_I2C_ABE_H
#define	_LCD_I2C_ABE_H
#include <inttypes.h>
#include <string.h>
#include <Arduino.h>
#include <Wire.h>
//#include "Print.h"

class LCD_I2C_ABE 
{
	public :
		LCD_I2C_ABE(uint8_t add = 0x27);
		void Init();
		void SetCursorOrigin();
		void SetCursor(uint8_t ligne , uint8_t colonne);
		void Clear();
		void PrintString(const char * str);
		void PrintCaractere(uint8_t car);
		
	private :
		void write4bits(uint8_t val);
		void Send(uint8_t val , uint8_t mode);
		void SendOneByteI2C(uint8_t car);
		void CaracterAdd();
		void commands(uint8_t val);
		
		int col;
		int lig;
		uint8_t Adress_Slave_Lcd;
};

#endif
