#include <Arduino.h>
#include <Wire.h>
#include "YaiCommunicator.h"

int I2C_CLIENT = 9;
String answer = "{\"DISTANCE\":0.00}";

YaiCommunicator yaiCommunicator;
boolean receiveFull = false;
String commandI2C = "";
String answerOk = "OK";
boolean receive = true;

void receiveEvent(int countToRead) {
	YaiBufferCommand requestFromMaster = yaiCommunicator.receiveI2CFromMaster();
	receive = true;
	if(requestFromMaster.status == String(STATUS_OK)){
		receiveFull = true;
		commandI2C = requestFromMaster.content;
	}
	//	commandI2C = requestFromMaster.content;
	//	answerOk = commandI2C;
	//}else{
	answerOk = "p"+String(requestFromMaster.part)+"/"+String(requestFromMaster.total);
		//receive = true;
	//}
}

void requestEvent() {
	//if(receiveFull){
	//	yaiCommunicator.sendI2CToMaster(answer);
	//	receiveFull = false;
	//	Serial.println("<< " + answer);
	//}
	//if(receive){
	yaiCommunicator.sendI2CToMaster(answerOk);
	//	Serial.println(answerOk);
	//	receive = false;
	//}
}

void setup() {
	Wire.begin(I2C_CLIENT);
	Wire.onRequest(requestEvent); // data request to slave
	Wire.onReceive(receiveEvent); // data slave received
	Serial.begin(9600);
	Serial.println("I2CPack Slave ready! " + String(MAX_I2C_COMAND) + " Bytes");
}

int i = 0;
void loop() {
	if(receive){
		Serial.print(" >> ");
		Serial.println(answerOk);
		receive = false;
	}
	if(receiveFull){
		Serial.print(" Full >> ");
		Serial.println(commandI2C);
		receiveFull = false;
	}
	i++;
	if(i == 200){
		Serial.println("live");
		i = 0;
	}
}
