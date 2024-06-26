#include<lpc214x.h>
#include<stdio.h>
#include<string.h>
#include "lcd.h"
#include "i2c.h"void LCD_PRINT_LINE(char* msg)
{
	LCD_CHAR(0x01, 0);   
	LCD_CHAR(0x80, 0);   
	LCD_STRING(msg);
	delay_ms(1000);
	LCD_CHAR(0x01, 0);   
	LCD_CHAR(0x80, 0);   
}
char bcdToAsciiLow(unsigned char bcd)
{
	
  char result;
	result = (char) ((bcd & 0x0f) + 48);
  return result;
}
char bcdToAsciiUp(unsigned char bcd)
{
	
	char result;
	result = (char) (((bcd & 0xf0) >> 4) + 48);
	return result;
}

void setTime(void){
	
	I2C_WRITE(0xD0, 0x00, 0x00);	 
	I2C_WRITE(0xD0, 0x01, 0x31);	 
	I2C_WRITE(0xD0, 0x02, 0x18);	 
	I2C_WRITE(0xD0, 0x03, 0x01);	 
	I2C_WRITE(0xD0, 0x04, 0x04);	
	I2C_WRITE(0xD0, 0x05, 0x09);	
	I2C_WRITE(0xD0, 0x06, 0x20)
}
int main(void){
	char sec[2], min[2], hrs[2];
	char time[16];
	LCD_INIT();	
	I2C_INIT();
	while(1)
	{
sec[0] = I2C_READ(0xD0, 0x00);
min[0] = I2C_READ(0xD0, 0x01);
	hrs[0] = I2C_READ(0xD0, 0x02);
	sec[1] = bcdToAsciiUp(sec[0]);
	sec[0] = bcdToAsciiLow(sec[0]);
	min[1] = bcdToAsciiUp(min[0]);
	min[0] = bcdToAsciiLow(min[0]);
	hrs[1] = bcdToAsciiUp(hrs[0]);
	hrs[0] = bcdToAsciiLow(hrs[0]);
	snprintf(time, 16, "%c%c:%c%c:%c%c",hrs[1],hrs[0],min[1],min[0],sec[1],sec[0]);
	LCD_PRINT_LINE(time);
	}
  return 0;
}
