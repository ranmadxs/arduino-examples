#include <Arduino.h> 
#include "ServoLink.h"

ServoLink::ServoLink(){}

//Derecha
static int PinOUTA   = 13; // (D7)
static int PinOUTB   = 15; // (D8)

String ServoLink::servoMove(int servoType, int servoDirection, int servoMovement){
  String result = "{}";
  return result;
}

