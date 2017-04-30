#include <Arduino.h> 
#include <Servo.h>
#include "YaiConstants.h"

//Servo pins
static int PinServoH   = 13; // (D7)
static int PinServoV   = 15; // (D8)

class ServoLink{

  public:

	ServoLink(){
	  servoH.attach(PinServoH);
	  servoV.attach(PinServoV);
	  posH = 0;
	  posV = 0;
	  speedDelayServoH = 15;
	  speedDelayServoV = 15;
	  maxAngle = 180;
	  //parte detenido
	  directionFlagH = false;
	  directionFlagV = false;

	  //Horario antihorario
	  movementServoH = 0;
	  movementServoV = 0;

	  typeServo = 0;
	};

    void callBackMovement(){
      String direction = "None";
      String movement = "None";
      int servoDirection = 0;
      int servoMovement = 0;
      String result = "";
      int speed;
      int servoType = typeServo;
      if(directionFlagH){
        direction = "HORIZONTAL";
        speed = speedDelayServoH;
        servoDirection = SERVO_DIRECTION_HORIZONTAL;
        servoMovement = movementServoH;
        movement = moveContinuous(servoType, servoDirection, servoMovement);
        result = "{\"direction\":\""+direction+"\", \"speed\":"+String(speed)+", "+movement+"}";
        Serial.println(result);

      }
      if(directionFlagV){
    	  direction = "VERTICAL";
    	  speed = speedDelayServoV;
    	  servoDirection = SERVO_DIRECTION_VERTICAL;
    	  servoMovement = movementServoV;
    	  movement = moveContinuous(servoType, servoDirection, servoMovement);
        result = "{\"direction\":\""+direction+"\", \"speed\":"+String(speed)+", "+movement+"}";
        Serial.println(result);
      }
    }

    String servoMove(int servoType, int servoDirection, int servoMovement, int speedDelay);

    String servoAngle(int servoType, int servoDirection, int angle);

    String servoStop(int servoType, int servoDirection);

  private:

    Servo servoH;
    Servo servoV;
    int speedDelayServoH;
    int speedDelayServoV;
    int maxAngle;
    int posH;
    int posV;
    boolean directionFlagH;
    boolean directionFlagV;
    int movementServoH;
    int movementServoV;
    int typeServo = 0;

  protected:

    // El tipo de servo depende de su direccion
    void setServoType(int _type, int _direction){
    	typeServo = _type;
    }

    int getMaxAngle(int servoType){
    	return maxAngle;
    };
    int getSpeedDelay(int servoDirection){
    	int speedDelayServo = 0;
    	if (SERVO_DIRECTION_HORIZONTAL == servoDirection){
    		speedDelayServo = speedDelayServoH;
    	}
    	if (SERVO_DIRECTION_VERTICAL == servoDirection){
    		speedDelayServo = speedDelayServoV;
    	}

    	return speedDelayServo;
    };
    void setSpeedDelay(int servoDirection, int _speedDelay){
    	if (SERVO_DIRECTION_HORIZONTAL == servoDirection){
    		speedDelayServoH = _speedDelay;
    	}
    	if (SERVO_DIRECTION_VERTICAL == servoDirection){
    		speedDelayServoV = _speedDelay;
    	}

    }

    int getPosition(int servoDirection){
    	int pos = 0;
    	if (SERVO_DIRECTION_HORIZONTAL == servoDirection){
    		pos = posH;
    	}
    	if (SERVO_DIRECTION_VERTICAL == servoDirection){
    		pos = posV;
    	}
    	return pos;
    }

    void setPosition(int servoDirection, int angle){
    	int pos = 0;
    	if (SERVO_DIRECTION_HORIZONTAL == servoDirection){
    		posH = angle;
    	}
    	if (SERVO_DIRECTION_VERTICAL == servoDirection){
    		posV = angle;
    	}
    }

    String write(int servoDirection, int angle){
    	String direction = "None";
    	if (SERVO_DIRECTION_HORIZONTAL == servoDirection){
    		direction = "HORIZONTAL";
    		servoH.write(angle);
    	}
    	if (SERVO_DIRECTION_VERTICAL == servoDirection){
    		direction = "VERTICAL";
    		servoV.write(angle);
    	}
    	return direction;
    }

    String moveContinuous(int servoType, int servoDirection, int servoMovement){
    	String movement = "None";
    	int posCurrent = getPosition(servoDirection);
        int pos = -1;
        int maxPos = getMaxAngle(servoType);
        int minPos = 0;

        if (servoMovement == SERVO_CLOCKWISE){
        	movement = "HORARIO";
        	pos = posCurrent + 1;
        	if(pos > maxPos){
        		pos = maxPos;
        	}
        	write(servoDirection, pos);
          setPosition(servoDirection, pos);
        }

    	if (servoMovement == SERVO_COUNTER_CLOCKWISE){
    		movement = "ANTI_HORARIO";
    		pos = posCurrent - 1;
    		if (pos < minPos){
    			pos = 0;
    		}
   			write(servoDirection, pos);
        setPosition(servoDirection, pos);
    	}
    	String resutlt = "\"movement\":\""+movement+"\", \"angle\":"+String(pos);

    	return resutlt;
    };

};
