#include "IRremote.h"

IRsend irsend;

void setup() {
  Serial.begin(9600);
  Serial.println("IR Receiver Sender Decode"); 

}

void loop() {
  irsend.sendNEC(0x20DF10EF,32);
  //irsend.sendNEC(0x20DF8877,32);
  Serial.println("Enviado");
  delay(200);

}
