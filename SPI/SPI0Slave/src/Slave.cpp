#include <SPI.h>

volatile boolean process_it;                    //Flag for checking if the data is recieved from Master i.e. ESP8266
byte a;                                         //Byte to store the processed data
char buf [100];
volatile byte pos;
volatile char bufRet [20] = "Bye, world!";
volatile byte posRet;
int flag;

void setup (void) {
  flag = 0;
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
	  SPDR = 0x05;
	  return;
  }

  if(flag == 0){
	  SPDR = 0x03;
  }
  if(flag == 1){
	  SPDR = 0x04;
  }
}

void loop (void) {
  if (process_it && digitalRead(SS) == HIGH)    //Check if the data has been processed y el paquete es para este micro
    {
	    buf [pos] = 0;
	    Serial.println (buf);
	    pos = 0;
	    process_it = false;
    }else{
    	if (flag == 0){
    		flag = 1;
    	}else{
    		flag = 0;
    	}
    }
}
