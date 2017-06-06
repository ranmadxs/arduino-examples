#include <Arduino.h>
#include <Wire.h>

int sdaPin = 4;
int sclPin = 5;
byte x = 0;

void setup() {
  Wire.begin(sdaPin,sclPin);
  Wire.setClockStretchLimit(15000);
  Serial.begin(9600);
  Serial.println("I2C Master on NodeMCU ready!");
}

void loop() {
  x = random(0,255);
  Serial.print("<< Write data: ");
  Serial.println(x);
  Wire.beginTransmission(9);
  Wire.write("x es : ");
  Wire.write(x);
  Wire.endTransmission();
  delay(10000);
  Serial.print(">> Receive data: ");
  Wire.requestFrom(9,3);
  String response = "";
  while (Wire.available()) {
      char b = Wire.read();
      response += b;
  }
  Serial.println(response);
  delay(5000);
}
