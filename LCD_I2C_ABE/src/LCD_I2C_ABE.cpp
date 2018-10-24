/*************************
** AUTHOR : Alain Béger **
**************************
*** UTILISATION SIMPLE ***
*** D'UN AFFICHEUR LCD ***
****** VIA BUS I2C *******
**************************/
#include "LCD_I2C_ABE.h"



LCD_I2C_ABE::LCD_I2C_ABE(uint8_t add)
{
	Adress_Slave_Lcd = add;
	Wire.begin();
	//Init();
}






void LCD_I2C_ABE::Init()
{
  delayMicroseconds(5000);
  SendOneByteI2C(0x00);
  write4bits(0x30);
  delayMicroseconds(4500);
  write4bits(0x30);
  delayMicroseconds(4500);
  write4bits(0x30);
  delayMicroseconds(150);
  write4bits(0x20);
  commands(0x20|0x08);
  commands(0x08|0x04);
  Clear();
  commands(0x04|0x02);
  delayMicroseconds(1000);
  SetCursorOrigin();
  delayMicroseconds(1000);
}

void LCD_I2C_ABE::SetCursorOrigin()
{
  col = 0;
  lig = 0;
  commands(0x80);
}

void LCD_I2C_ABE::SetCursor(uint8_t ligne , uint8_t colonne)
{
  if(colonne>16) colonne = 16;
  if( ligne == 0 )
  {
    lig = 0;
    col = colonne;
    commands(0x80 | colonne);
  }
  else
  {
    lig = 1;
    col = colonne;
    commands(0x80 | (colonne+0x40) );
  }
}

void LCD_I2C_ABE::Clear()
{
  commands(0x01);
  delayMicroseconds(2000);
}

void LCD_I2C_ABE::PrintString(const char * str)
{
  int size_str = 0;
  int i = 0;
  size_str = strlen(str);
  for(i=0;i<size_str;i++)
    PrintCaractere(str[i]);
}

void LCD_I2C_ABE::PrintCaractere(uint8_t car)
{
  uint8_t tmp1 = car&0xF0;
  uint8_t tmp2 = (car<<4)&0xF0;
  CaracterAdd();
  write4bits(tmp1|0x01);
  write4bits(tmp2|0x01);
}


// private
void LCD_I2C_ABE::commands(uint8_t val)
{
  Send(val , 0);
}

void LCD_I2C_ABE::write4bits(uint8_t val)
{
  SendOneByteI2C(val);
  SendOneByteI2C(val & 0xFB);
  delayMicroseconds(1);
  SendOneByteI2C(val | 0x04); 
  delayMicroseconds(1);
  SendOneByteI2C(val & 0xFB);
  delayMicroseconds(100);
}

void LCD_I2C_ABE::Send(uint8_t val , uint8_t mode)
{
  uint8_t tmp1 = val&0xF0;
  uint8_t tmp2 = (val<<4)&0xF0;
  write4bits(tmp1|mode);
  write4bits(tmp2|mode);
}

void LCD_I2C_ABE::SendOneByteI2C(uint8_t car)
{
  Wire.beginTransmission(Adress_Slave_Lcd);
  Wire.write(car | 0x08);
  Wire.endTransmission();
}


void LCD_I2C_ABE::CaracterAdd()
{
  if( col > 15 )
  {
    col = 0;
    if( lig >= 1 )
    {
      lig = 0;
    }
    else
    {
      lig ++;
    }
    SetCursor( lig , col);
  }
  else
  {
    
  }
  col ++;
}
