#include <Arduino.h>
#include <Wire.h>
#include "YaiCommunicator.h"

int I2C_CLIENT = 9;
String answer = "{\"DISTANCE\":0.00}";

YaiCommunicator yaiCommunicator;

void receiveEvent(int countToRead) {
	YaiBufferCommand requestFromMaster = yaiCommunicator.receiveI2CFromMaster();
	//if(requestFromMaster.status == String(STATUS_OK)){
		//Serial.print(" >> ");
		//requestFromMaster.print();
	//}else{
	//	Serial.println(" >> Y_Y   " + requestFromMaster.content);
	//}
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
	Serial.println("I2CPack Slave ready! " + String(MAX_I2C_COMAND) + " Bytes");
}

void loop() {
	delay(500);
}
