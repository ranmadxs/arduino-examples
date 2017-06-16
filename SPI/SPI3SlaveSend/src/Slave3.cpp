#include <SPI.h>

// Slave

void setup (void)
{
  SPCR |= bit (SPE);                            //Configure ATMEGA328P/Arduino in slave mode
  pinMode(MISO, OUTPUT);                        //Configure MISO as output, SlaveOut
  SPI.attachInterrupt();                        //Enable interrupts for SPI--> You can do that like this too /*SPCR |= bit (SPIE)*/
}  // end of setup

// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR; 

  if (c == 2)  // starting new sequence?
    {
	SPDR = 0x02;
    return;
    }
  if (c == 3)  // starting new sequence?
    {
	SPDR = 0x03;
    return;
    }

  if (c == 4)  // starting new sequence?
    {
	SPDR = 0x04;
    return;
    }
	
  if (c == 'a')  // starting new sequence?
    {
	SPDR = 0x07;
    return;
    }	
	
  SPDR = 0x01;
}  // end of interrupt service routine (ISR) SPI_STC_vect

void loop (void)
{

}  // end of loop