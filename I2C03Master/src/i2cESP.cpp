#include <Arduino.h>
#include <Wire.h>

int sdaPin = 4;
int sclPin = 5;
byte x = 0;
#define ANSWERSIZE 32

void setup() {
  Wire.begin(sdaPin,sclPin);
  Wire.setClockStretchLimit(15000);
  Serial.begin(9600);
  Serial.println("I2C Master on NodeMCU ready! "+String(ANSWERSIZE) + " Bytes");
}

void loop() {
  x = random(0,255);
  Serial.print("<< Write data to slave: ");
  Serial.println(x);
  Wire.beginTransmission(9);
  char xd = x;
  String cmdEnv = "SERIAL,100001,1001,0,0,10003,None,None,None";
  char copyStr[64];
  cmdEnv.toCharArray(copyStr, 64);
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
}
