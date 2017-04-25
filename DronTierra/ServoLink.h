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
	  speed = 15;
	  maxAngle = 0;
	};

    String servoMove(int servoType, int servoDirection, int servoMovement, int speed);

    String servoAngle(int servoType, int servoDirection, int angle);

    int getMaxAngle(int servoType){
    	return maxAngle;
    };
    int getSpeed(int servoDirection){
    	return speed;
    };

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

    String moveContinuous(int servoType, int servoDirection, int servoMovement, int speedDelay){
    	String direction = "None";
    	int posCurrent = getPosition(servoDirection);
    	int maxPos = getMaxAngle(servoType);
    	int pos;
    	if (servoMovement == SERVO_CLOCKWISE){
    		for(pos = posCurrent; pos < maxPos; pos += 1) {
    			write(servoDirection, pos);
    			delay(speedDelay);
    		}
    	}
    	if (servoMovement == SERVO_COUNTER_CLOCKWISE){
    		for(pos = posCurrent; pos>=1; pos-=1){
    			write(servoDirection, pos);
    			delay(speedDelay);
    		}
    	}
    	//while()
    	return direction;
    };

  private:
  
  protected:
    Servo servoH;
    Servo servoV;
    int speed;
    int maxAngle;
    int posH;
    int posV;
  
};
