#include <Arduino.h>
#include <Wire.h>
#include "YaiCommunicator.h"

byte x = 0;
int I2C_CLIENT = 9;
String exampleCommand = "SERIAL,100003,true,None,None,None,None,None,None";
String response;
YaiCommunicator yaiCommunicator;

void setup() {
	Wire.begin(I2C_MASTER_SDA_PIN, I2C_MASTER_SCL_PIN);
	Wire.setClockStretchLimit(15000);
	Serial.begin(9600);
	Serial.println(
			"I2C MasterPack on NodeMCU ready! " + String(MAX_I2C_COMAND)
					+ " Bytes");
	delay(2000);
}

void loop() {
	yaiCommunicator.sendI2CCommand(exampleCommand, I2C_CLIENT);
	delay(500);
	response = yaiCommunicator.receiveCommand(I2C_CLIENT);
	Serial.println(">> " + response);
	delay(5500);

}
