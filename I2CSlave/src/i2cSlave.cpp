#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x60
byte x = 0x00;
byte y = 0x01;

void requestEvent() 
{
  Serial.print("Request from Master. Sending: ");
  Serial.println(x, HEX);
 
  Wire.write(x);
  Wire.write(y);
}

void receiveEvent(int bytes)
{
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

void setup()
{
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
}

void loop()
{
  delay(100);
}
