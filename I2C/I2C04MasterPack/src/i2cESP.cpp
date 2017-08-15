#include <Arduino.h>
#include <Wire.h>
#include "YaiCommunicator.h"

int I2C_CLIENT = 3;
String exampleCommand = "I2C,100002,1001,0,None,None,None,None,None";
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

String cmd1;
String request1;
String cmdRec;

void loop() {
/*
	cmd1 = exampleCommand.substring(0, MAX_I2C_COMAND);
	request1 = yaiCommunicator.buildI2Cpackage(cmd1, 2, 1);
	yaiCommunicator.sendI2Cpackage(request1, I2C_CLIENT);

	delay(100);
	Serial.print(">> Receive data from slave: ");

	cmdRec = yaiCommunicator.receiveCommand(I2C_CLIENT);

	Serial.print("(" + String(cmdRec.length()) + " num chars) :: ");
	Serial.println(cmdRec);

	cmd1 = exampleCommand.substring(MAX_I2C_COMAND);
	request1 = yaiCommunicator.buildI2Cpackage(cmd1, 2, 2);
	yaiCommunicator.sendI2Cpackage(request1, I2C_CLIENT);
	delay(100);
	Serial.print(">> Receive data from slave Part2: ");

	cmdRec = yaiCommunicator.receiveCommand(I2C_CLIENT);
	Serial.print("(" + String(cmdRec.length()) + " num chars) :: ");
	Serial.println(cmdRec);
*/

	cmdRec = yaiCommunicator.sendI2CCommand(exampleCommand, I2C_CLIENT);
	Serial.print("(" + String(cmdRec.length()) + " num chars) :: ");
	Serial.println(cmdRec);
	delay(5500);

}
