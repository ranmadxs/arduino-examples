#include <SPI.h>

//#define CS 15
#define CS 2 //D1

void setup(){

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
}

void loop(){
	byte spi_dat;
	char c;
	digitalWrite(CS,LOW);           //Pull CS Line Low
	//SPI.transfer(0x02);             //Send a byte (0x02) to the slave i.e. Arduino UNO
	for (const char * p = "Hello, world!\n" ; c = *p; p++) {
		SPI.transfer(c);
	    //Serial.print(c);
	}
	digitalWrite(CS,HIGH);          //Pull CS Line High

	delayMicroseconds(10);          //Give some time for the slave to process/do something with the recived data

	digitalWrite(CS,LOW);           //Pull CS Line Low
	spi_dat = SPI.transfer(0x00);   //Received the processed data byte from the slave
	digitalWrite(CS,HIGH);          //Pull CS Line High
	Serial.println("Processed Data Recieved from Slave is: ");
	Serial.print(spi_dat);          //UART - Print the data received from the slave
	Serial.println("\r\n");
	delay(1000);                    //Delay of 1s
}
