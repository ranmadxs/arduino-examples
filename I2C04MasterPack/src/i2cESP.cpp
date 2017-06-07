#include <Arduino.h>
#include <Wire.h>
#include "YaiCommunicator.h"

int sdaPin = 4;
int sclPin = 5;
byte x = 0;
#define ANSWERSIZE 32

YaiCommunicator yaiCommunicator;

void setup() {
  Wire.begin(sdaPin,sclPin);
  Wire.setClockStretchLimit(15000);
  Serial.begin(9600);
  Serial.println("I2C MasterPack on NodeMCU ready! "+String(ANSWERSIZE) + " Bytes");
  delay(2000);
  Serial.println("Build commands");
  YaiI2CCommand i2cCommands[2];
  String exampleCommand = "SERIAL,100003,true,None,None,None,None,None,None";
  yaiCommunicator.sendI2CCommand(exampleCommand);
  delay(500);
  Serial.print(">> Receive data from slave: ");
  Wire.requestFrom(9,ANSWERSIZE);
  String response = "";
  int countChars = 0;
  while (0 < Wire.available()) {
      char b = Wire.read();
      Serial.print( b );
      countChars++;
  }
  Serial.println("("+String(countChars)+" chars)");
  /*
  for (int i = 0; i < 2; i++) {
	  Serial.println(String(i)+")Send:");
	  Wire.beginTransmission(9);
	  Serial.println(i2cCommands[i].content);
	  char copyStr[ANSWERSIZE];
	  i2cCommands[i].content.toCharArray(copyStr, ANSWERSIZE);
	  Wire.write(copyStr);
	  Wire.endTransmission();
  }
  */
}

void loop() {
	/*
  x = random(0,255);
  Serial.print("<< Write data to slave: ");
  Serial.println(x);
  Wire.beginTransmission(9);
  char xd = x;
  String cmdEnv = "SERIAL,100001,1001,0,0,10003,None,None,None:";
  char copyStr[ANSWERSIZE];
  cmdEnv.toCharArray(copyStr, ANSWERSIZE);
  Wire.write(copyStr);
  Wire.endTransmission();
  delay(100);
  Serial.print(">> Receive data from slave: ");
  Wire.requestFrom(9,ANSWERSIZE);
  String response = "";
  int countChars = 0;
  while (Wire.available()) {
      char b = Wire.read();
      response += b;
      countChars++;
  }
  Serial.print("("+String(countChars)+" chars)");
  Serial.println(response);
  delay(5500);
  */
}
