#include <Arduino.h> 
#include "ServoLink.h"


//default speed = 15
// creo dos thread uno que haga move simepre que no este stop y el otro que haga el stop.
String ServoLink::servoMove(int servoType, int servoDirection, int servoMovement, int speedDeplay){
  String result = "";
  ServoLink::setServoType(servoType, servoDirection);
  ServoLink::setSpeedDelay(servoDirection, speedDeplay);
  int pos;
  String direction = "None";
  if (SERVO_DIRECTION_HORIZONTAL == servoDirection){
	direction = "HORIZONTAL";
	directionFlagH = true;
	movementServoH = servoMovement;
  }
  if (SERVO_DIRECTION_VERTICAL == servoDirection){
	direction = "VERTICAL";
	directionFlagV = true;
	movementServoV = servoMovement;
  }
  return "{\"ACTION\":\"MOVE\", \"DIRECTION\":\""+direction+"\"}";
}

String ServoLink::servoStop(int servoType, int servoDirection){
	ServoLink::setServoType(servoType, servoDirection);
	String directionName = "None";
	if (SERVO_DIRECTION_HORIZONTAL == servoDirection){
		directionName = "\"HORIZONTAL\"";
		directionFlagH = false;
	}
	if (SERVO_DIRECTION_VERTICAL == servoDirection){
		directionName = "\"VERTICAL\"";
		directionFlagV = false;
	}
	if(SERVO_DIRECTION_ALL == servoDirection){
		directionName = "[\"VERTICAL\", \"HORIZONTAL\"]";
		directionFlagV = false;
		directionFlagH = false;
	}

	return "{\"ACTION\":\"STOP\", \"DIRECTION\":"+directionName+"}";
}

String ServoLink::servoAngle(int servoType, int servoDirection, int angle){
  ServoLink::setServoType(servoType, servoDirection);
  int maxAngle = ServoLink::getMaxAngle(servoType);
  String directionName = "None";
  if(angle > maxAngle){
	  angle = maxAngle;
  }
  if(SERVO_DIRECTION_ALL == servoDirection){
    ServoLink::setPosition(SERVO_DIRECTION_HORIZONTAL, angle);
    ServoLink::setPosition(SERVO_DIRECTION_VERTICAL, angle);
    directionName = "[";
    directionName += "\"" + ServoLink::write(SERVO_DIRECTION_HORIZONTAL, angle) + "\", ";
    directionName += "\"" + ServoLink::write(SERVO_DIRECTION_VERTICAL, angle) + "\"";
    directionName += "]";
  }else{
    ServoLink::setPosition(servoDirection, angle);   
    directionName = "\"" + ServoLink::write(servoDirection, angle) + "\"";
  }
 
  String result = "{ \"DIRECTION\":"+directionName+", \"ANGLE:\":"+String(angle)+"}";
  return result;
  
}

