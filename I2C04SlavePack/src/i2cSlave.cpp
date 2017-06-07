#include <Arduino.h>
#include <Wire.h>
#include "YaiCommunicator.h"

#define ANSWERSIZE 32
int I2C_CLIENT = 9;
String answer = "{\"DISTANCE\":0.00}";

YaiCommunicator yaiCommunicator;

void receiveEvent(int countToRead) {
	String requestFromMaster = yaiCommunicator.receiveI2CFromMaster();
	Serial.println(" >> " + requestFromMaster);
}

void requestEvent() {
	yaiCommunicator.sendI2CToMaster(answer);
	Serial.println("<< " + answer);
}

void setup() {
	Wire.begin(I2C_CLIENT);
	Wire.onRequest(requestEvent); // data request to slave
	Wire.onReceive(receiveEvent); // data slave received
	Serial.begin(9600);
	Serial.println("I2CPack Slave ready! " + String(ANSWERSIZE) + " Bytes");
}

void loop() {
	delay(500);
}
