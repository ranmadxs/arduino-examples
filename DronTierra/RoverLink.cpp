#include "RoverLink.h"

//https://www.w3schools.com/code/tryit.asp?filename=FE7CD8RR2VKU
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm

RoverLink::RoverLink(){}

void RoverLink::motorStop(int roverType){

  Serial.println("RoverLink::motorStop");
  Serial.println("roverType=" + roverType);
  digitalWrite (PinOUTA, LOW);
  digitalWrite (PinOUTB, LOW);
  digitalWrite (PinOUTC, LOW);
  digitalWrite (PinOUTD, LOW);
}

