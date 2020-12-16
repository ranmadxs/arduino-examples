#include <Arduino.h>

int counter = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Hola counter:");
  Serial.println(counter);
  counter = counter + 1;
  if (counter > 100) {
    counter = 0;
  }
  delay(1000);
}