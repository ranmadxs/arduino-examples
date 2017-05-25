#include "YaiCommons.h"
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
String RoverLink::motorMove(String roverType, String moveType){
  String directionName = "None";
  RoverLink::motorHalt2WD();
  if(moveType == String(ROVER_BODY_MOVE_TYPE_FORWARD)){
	 directionName = "FORWARD";
	 digitalWrite (PinOUTB, HIGH);
	 digitalWrite (PinOUTD, HIGH);
   return "FORWARD";
  }
  if(moveType == String(ROVER_BODY_MOVE_TYPE_BACK)){
	 directionName = "BACK";
	 digitalWrite (PinOUTA, HIGH);
	 digitalWrite (PinOUTC, HIGH);
  }

  if(moveType == String(ROVER_BODY_MOVE_TYPE_LEFT)){
	 directionName = "LEFT";
	 digitalWrite (PinOUTB, HIGH);
  }

  if(moveType == String(ROVER_BODY_MOVE_TYPE_RIGHT)){
	 directionName = "RIGHT";
	 digitalWrite (PinOUTD, HIGH);
  }
  return directionName;
}

void RoverLink::motorHalt2WD(){
	digitalWrite (PinOUTA, LOW);
	digitalWrite (PinOUTB, LOW);
	digitalWrite (PinOUTC, LOW);
	digitalWrite (PinOUTD, LOW);
}
