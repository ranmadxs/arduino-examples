#include <Arduino.h>
#include "HCSRExample.h"
#include <Wire.h>

#define ANSWERSIZE 32

String answer = "{\"DISTANCE\":0.00}";
HCSRExample hcsr;

void receiveEvent(int countToRead) {
	Serial.print(">> Receive event from master: ");
	  while (1 < Wire.available()) {
	    char c = Wire.read();
	    Serial.print(c);
	  }
	  int x = Wire.read();

	  Serial.println(x);
}

void requestEvent() {
  int lenAnsw = answer.length();
  int difLen = 0;
  
  if(lenAnsw >= ANSWERSIZE){
	lenAnsw = ANSWERSIZE;
  }else{
	  difLen = ANSWERSIZE - lenAnsw;
  }

  
  byte response[ANSWERSIZE];
  for (byte i=0;i<lenAnsw;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  if(difLen > 0){
	  for (byte i=lenAnsw;i<ANSWERSIZE;i++) {
		response[i] = 0x23;
	  }
  }
  
  Wire.write(response,sizeof(response));
  Serial.print("<< Request event to master: ");
  Serial.println(answer);
}

void setup() {
  Wire.begin(9);
  Wire.onRequest(requestEvent); // data request to slave
  Wire.onReceive(receiveEvent); // data slave received
  Serial.begin(9600);
  Serial.println("I2C Slave ready! "+String(ANSWERSIZE) + " Bytes");
}


void loop() {
	delay(500);
	String dist = hcsr.distancia(1, 1);
	answer = dist;
	Serial.println(dist);
}
