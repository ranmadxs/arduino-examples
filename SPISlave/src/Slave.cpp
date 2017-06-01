#include <SPI.h>

volatile boolean process_it;                    //Flag for checking if the data is recieved from Master i.e. ESP8266
byte a;                                         //Byte to store the processed data
char buf [100];
volatile byte pos;

void setup (void) {
  Serial.begin (9600);                        	//Set UART baug rate to 115200
  SPCR |= bit (SPE);                            //Configure ATMEGA328P/Arduino in slave mode
  pinMode(MISO, OUTPUT);                        //Configure MISO as output, SlaveOut
  process_it = false;                           //Initialize flag to FALSE
  SPI.attachInterrupt();                        //Enable interrupts for SPI--> You can do that like this too /*SPCR |= bit (SPIE)*/
  Serial.println("SPI Slave inicializado");
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;                                //Grab the data byte from the SPI Data Register (SPDR)
  //a = c;                                        //Put the byte into a temporary variable for processing
  //SPDR = c*2;                                   //process the data byte and put it back into the SPDR for the Master to read it
  //process_it = true;                            //Set the Flag  as TRUE
  if (pos < sizeof buf) {
      buf [pos++] = c;
      if (c == '\n')
      process_it = true;
  }
  SPDR = 0x07;
}

void loop (void) {
  if (process_it)                               //Check if the data has been processed
    {
	    buf [pos] = 0;
	    Serial.println (buf);
	    pos = 0;
	    process_it = false;
    }
}
