#include <Arduino.h>
#include <Wire.h>
#include "YaiCommunicator.h"

int I2C_CLIENT = 9;
String answer = "{\"DISTANCE\":0.00}";

#define ANSWERSIZE 32
YaiCommunicator yaiCommunicator;
boolean receiveFull = false;
String commandI2C = "";
String answerOk = "OK";
boolean receive = false;
String respToMaster;
boolean reciveFullI2C = false;
String masterCmd = "";
String requestI2C = "";

void receiveEvent(int countToRead) {
	/*
	YaiBufferCommand yaiBuffer = yaiCommunicator.receiveEvent(masterCmd);
	masterCmd = yaiBuffer.content;
	reciveFullI2C = yaiBuffer.recibeFull;
	*/

	requestI2C = "";
	while (0 < Wire.available()) {
		char c = Wire.read();
		requestI2C += c;
	}

	Serial.print("requestI2C::");
	Serial.println(requestI2C);
	String part = requestI2C.substring(4, 5);
	Serial.print(part);
	String total = requestI2C.substring(5, 6);
	Serial.print("/");
	Serial.println(total);
	masterCmd = masterCmd + requestI2C.substring(6);
	receive = true;
	if (part == total) {
		reciveFullI2C = true;
	}

}

void requestEvent() {

	int lenAnsw = answer.length();
	int difLen = 0;

	if (lenAnsw >= ANSWERSIZE) {
		lenAnsw = ANSWERSIZE;
	} else {
		difLen = ANSWERSIZE - lenAnsw;
	}

	byte response[ANSWERSIZE];
	for (byte i = 0; i < lenAnsw; i++) {
		response[i] = (byte) answer.charAt(i);
	}
	if (difLen > 0) {
		for (byte i = lenAnsw; i < ANSWERSIZE; i++) {
			response[i] = 0x23;
		}
	}
	Wire.write(response, sizeof(response));

	//yaiCommunicator.requestEvent(answer);
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
		receive = false;
		Serial.println("<< " + masterCmd);
		//masterCmd = "";
	}

	if (reciveFullI2C) {
		reciveFullI2C = false;
		masterCmd.replace("#", "");
		Serial.println("<< [I2C] " + masterCmd);
		masterCmd = "";
	}
}
