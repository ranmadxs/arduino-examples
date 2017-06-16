// master

#include <SPI.h>
#define CS 2 //D1

void setup (void)
{
	pinMode(CS,OUTPUT);
	Serial.begin(9600);
	digitalWrite(CS,HIGH);
	SPI.begin();
	Serial.println("");
	Serial.println("SPI Master Inicializado");
	 /*Configure the SPI bus as follows
	  1. SPI bus speed = 1 MHz
	  2. Data Out = From MSB bit ---> To LSB bit
	  3. Data Mode = SPI MODE0*/
	SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
	Serial.println("SPI bus speed = 1 MHz, Mode = SPI MODE0");

}  // end of setup

void loop (void)
{
	byte spi_dat1;
	byte spi_dat2;
	byte spi_dat3;
	
	digitalWrite(CS,LOW); 	
	spi_dat1 = SPI.transfer(2);	
	digitalWrite(CS,HIGH);
	delay(10);
	digitalWrite(CS,LOW); 	
	spi_dat2 = SPI.transfer(3);	
	digitalWrite(CS,HIGH);
	delay(10);
	digitalWrite(CS,LOW); 	
	spi_dat3 = SPI.transfer(4);	
	digitalWrite(CS,HIGH);
	
	Serial.print("==================");
    Serial.print("RESP dat1:");
	Serial.println(spi_dat1);
	Serial.print("RESP dat2:");
	Serial.println(spi_dat2);
	Serial.print("RESP dat3:");
	Serial.println(spi_dat3);
	delay(1000);
}  // end of loop