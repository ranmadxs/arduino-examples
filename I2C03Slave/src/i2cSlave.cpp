#include <Arduino.h>
#include <Wire.h>

#define ANSWERSIZE 3

String answer = "PAM";

void receiveEvent(int countToRead) {
	Serial.print(">> Receive event: ");
	  while (1 < Wire.available()) { // loop through all but the last
	    char c = Wire.read(); // receive byte as a character
	    Serial.print(c);         // print the character
	  }
	  int x = Wire.read();    // receive byte as an integer

	  Serial.println(x);         // print the integer
}

void requestEvent() {
  byte response[ANSWERSIZE];
  for (byte i=0;i<ANSWERSIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  Wire.write(response,sizeof(response));
  Serial.print("<< Request event: ");
  Serial.println(answer);
}

void setup() {
  Wire.begin(9);
  Wire.onRequest(requestEvent); // data request to slave
  Wire.onReceive(receiveEvent); // data slave received
  Serial.begin(9600);
  Serial.println("I2C Slave ready!");
}


void loop() {
  delay(15000);
}
