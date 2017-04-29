#include <Arduino.h> 
#include "ServoLink.h"
#include "YaiConstants.h"

//default speed = 15
// Esto debe hacerse conm thread si no dejo tomado el hilo,
// creo dos thread uno que haga move simepre que no este stop y el otro que haga el stop.
String ServoLink::servoMove(int servoType, int servoDirection, int servoMovement, int speedDeplay){
  String result = "";

  int pos;
  String direction = "None";
  if (SERVO_DIRECTION_HORIZONTAL == servoDirection){
	direction = "HORIZONTAL";
	moveFlagH = true;
  }
  if (SERVO_DIRECTION_VERTICAL == servoDirection){
	direction = "VERTICAL";
	moveFlagV = true;
  }
  return "{\"action\":\"move\", \"direction\":\""+direction+"\"}";
}

String ServoLink::servoStop(int servoType, int servoDirection){
	String direction = "None";
	if (SERVO_DIRECTION_HORIZONTAL == servoDirection){
		direction = "HORIZONTAL";
		Serial.println(" STOP Horizontal !! ");
		moveFlagH = false;
	}
	if (SERVO_DIRECTION_VERTICAL == servoDirection){
		direction = "VERTICAL";
		Serial.println(" STOP Vertical !! ");
		moveFlagV = false;
	}

	return "{\"action\":\"stop\", \"direction\":\""+direction+"\"}";
}

//TODO: Generalizar lo antes posible para sacar los dos if
//TODO: Implementar all despues
String ServoLink::servoAngle(int servoType, int servoDirection, int angle){
  int maxAngle = ServoLink::getMaxAngle(servoType);
  if(angle > maxAngle){
	  angle = maxAngle;
  }
  ServoLink::setPosition(servoDirection, angle);
  String direction = ServoLink::write(servoDirection, angle);
  String result = "{ \"direction\":\""+direction+"\", \"angle:\":"+String(angle)+"}";
  return result;
  
}

