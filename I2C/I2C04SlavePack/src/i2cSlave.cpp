#include <Arduino.h>
#include <Wire.h>
#include "YaiCommunicator.h"

int I2C_CLIENT = 9;
String answer = "{\"DISTANCE\":0.00}";

YaiCommunicator yaiCommunicator;
boolean receive = false;
String commandI2C = "";

void receiveEvent(int countToRead) {
	YaiBufferCommand requestFromMaster = yaiCommunicator.receiveI2CFromMaster();
	if(requestFromMaster.status == String(STATUS_OK)){
		receive = true;
		commandI2C = requestFromMaster.content;
		Serial.print(" >> ");
		Serial.println(commandI2C);
	}
}

void requestEvent() {
	if(receive){
		yaiCommunicator.sendI2CToMaster(answer);
		receive = false;
		Serial.println("<< " + answer);
	}	
}

void setup() {
	Wire.begin(I2C_CLIENT);
	Wire.onRequest(requestEvent); // data request to slave
	Wire.onReceive(receiveEvent); // data slave received
	Serial.begin(9600);
	Serial.println("I2CPack Slave ready! " + String(MAX_I2C_COMAND) + " Bytes");
}

void loop() {
	//if(receive){
	//	Serial.print(" >> ");
	//	Serial.println(commandI2C);		
	//}
}
