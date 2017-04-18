#include "YaiConstants.h"
#include "RoverLink.h"
#include <Arduino.h>

//https://www.w3schools.com/code/tryit.asp?filename=FE7CD8RR2VKU
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm

RoverLink::RoverLink(){}

void RoverLink::motorStop(int roverType){
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("RoverLink::motorStop");
  RoverLink::motorHalt2WD();
}

void RoverLink::motorMove(int roverType, int moveType){

  Serial.println("RoverLink::motorMove");
  digitalWrite(LED_BUILTIN, LOW);
  RoverLink::motorHalt2WD();
  if(moveType == ROVER_BODY_MOVE_TYPE_FORWARD){
	 Serial.println("FORWARD");
	 digitalWrite (PinOUTB, HIGH);
	 digitalWrite (PinOUTD, HIGH);
  }
  if(moveType == ROVER_BODY_MOVE_TYPE_BACK){
	 Serial.println("BACK");
	 digitalWrite (PinOUTA, HIGH);
	 digitalWrite (PinOUTC, HIGH);
  }

  if(moveType == ROVER_BODY_MOVE_TYPE_LEFT){
	Serial.println("LEFT");
	digitalWrite (PinOUTB, HIGH);
  }

  if(moveType == ROVER_BODY_MOVE_TYPE_RIGHT){
	Serial.println("RIGHT");
	digitalWrite (PinOUTD, HIGH);
  }
}

void RoverLink::motorHalt2WD(){
	digitalWrite (PinOUTA, LOW);
	digitalWrite (PinOUTB, LOW);
	digitalWrite (PinOUTC, LOW);
	digitalWrite (PinOUTD, LOW);
}
