#include "YaiConstants.h"
#include "RoverLink.h"
#include <Arduino.h>

//https://www.w3schools.com/code/tryit.asp?filename=FE7CD8RR2VKU
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm

void RoverLink::laser(boolean active){
  if(active){
    digitalWrite(PinLaser, HIGH);
  }else{
    digitalWrite(PinLaser, LOW);
  }
  
}

void RoverLink::motorStop(int roverType){
  RoverLink::motorHalt2WD();
}


//TODO: Debe generalizarse por movimiento de rueda y no por el sentido,
//es decir que ruedas pertenecn a que tipo de movimiento por tipo de rover
String RoverLink::motorMove(int roverType, int moveType){
  String direction = "None";
  RoverLink::motorHalt2WD();
  if(moveType == ROVER_BODY_MOVE_TYPE_FORWARD){
	 direction = "FORWARD";
	 digitalWrite (PinOUTB, HIGH);
	 digitalWrite (PinOUTD, HIGH);
  }
  if(moveType == ROVER_BODY_MOVE_TYPE_BACK){
	 direction = "BACK";
	 digitalWrite (PinOUTA, HIGH);
	 digitalWrite (PinOUTC, HIGH);
  }

  if(moveType == ROVER_BODY_MOVE_TYPE_LEFT){
	 direction = "LEFT";
	 digitalWrite (PinOUTB, HIGH);
  }

  if(moveType == ROVER_BODY_MOVE_TYPE_RIGHT){
	 direction = "RIGHT";
	 digitalWrite (PinOUTD, HIGH);
  }
  return direction;
}

void RoverLink::motorHalt2WD(){
	digitalWrite (PinOUTA, LOW);
	digitalWrite (PinOUTB, LOW);
	digitalWrite (PinOUTC, LOW);
	digitalWrite (PinOUTD, LOW);
}
