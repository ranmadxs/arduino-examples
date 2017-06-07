#include <Arduino.h>
#include <Wire.h>
#include "YaiCommunicator.h"

#define ANSWERSIZE 32

String answer = "{\"DISTANCE\":0.00}";

void receiveEvent(int countToRead) {
	Serial.print(">> Receive event from master: ");
	  while (0 < Wire.available()) {
	    char c = Wire.read();
	    Serial.print(c);
	  }
	  Serial.println("");
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
  
  //Wire.write(response,sizeof(response));
  String respOk = "Ok";
  char copyStr[ANSWERSIZE];
  respOk.toCharArray(copyStr, ANSWERSIZE);
  Wire.write(copyStr);
  Serial.print("<< Request event to master: ");
  Serial.println(respOk);
}

void setup() {
  Wire.begin(9);
  Wire.onRequest(requestEvent); // data request to slave
  Wire.onReceive(receiveEvent); // data slave received
  Serial.begin(9600);
  Serial.println("I2CPack Slave ready! "+String(ANSWERSIZE) + " Bytes");
}


void loop() {
	delay(500);
}
