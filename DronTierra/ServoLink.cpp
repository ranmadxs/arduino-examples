#include <Arduino.h> 
#include "ServoLink.h"
#include "YaiConstants.h"

//default speed = 15
// Esto debe hacerse conm thread si no dejo tomado el hilo
String ServoLink::servoMove(int servoType, int servoDirection, int servoMovement, int speed){
  String result = "";
  if (speed == 0){
	  speed =  ServoLink::getSpeed(servoDirection);
  }
  int maxAngle = ServoLink::getMaxAngle(servoType);

  int pos;
  String direction = "None";
  if (servoDirection == SERVO_DIRECTION_HORIZONTAL || servoDirection == SERVO_DIRECTION_ALL){
	  for(pos = posH; pos < maxAngle; pos += 1){
		  //myservo.write(pos);
		  delay(speed);
	  }
  }


  return result;
}

//TODO: Generalizar lo antes posible para sacar los dos if y el ALL debe manejarse con threads
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

