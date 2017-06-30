#ifndef RoverLink_h
#define RoverLink_h

//#include <Arduino.h> 
#include "YaiCommons.h"

//Derecha
static int PinOUTA = 4; // (D1)
static int PinOUTB = 5; // (D2)

//Izquierda
static int PinOUTC = 6; // (D3)
static int PinOUTD = 7; // (D5)

//Laser
static int PinLaser = 12; // (D6)

class RoverLink {
public:

	//Constructor de la clase
	RoverLink() {
		pinMode(PinOUTA, OUTPUT);
		pinMode(PinOUTB, OUTPUT);
		pinMode(PinOUTC, OUTPUT);
		pinMode(PinOUTD, OUTPUT);
		pinMode(PinLaser, OUTPUT);
	}
	;

	//Detiene el Rover
	void motorStop(int roverType) {
		motorHalt2WD();
	}

	YaiCommand motorMove(String roverType, String moveType) {
		YaiCommand yaiResp;
		String directionName = String(YAI_COMMAND_TYPE_NONE);
		motorHalt2WD();
		if (moveType == String(ROVER_BODY_MOVE_TYPE_FORWARD)) {
			directionName = "FORW";
			digitalWrite(PinOUTB, HIGH);
			digitalWrite(PinOUTD, HIGH);
		}
		if (moveType == String(ROVER_BODY_MOVE_TYPE_BACK)) {
			directionName = "BACK";
			digitalWrite(PinOUTA, HIGH);
			digitalWrite(PinOUTC, HIGH);
		}

		if (moveType == String(ROVER_BODY_MOVE_TYPE_LEFT)) {
			directionName = "LEFT";
			digitalWrite(PinOUTB, HIGH);
		}

		if (moveType == String(ROVER_BODY_MOVE_TYPE_RIGHT)) {
			directionName = "RIGH";
			digitalWrite(PinOUTD, HIGH);
		}

		yaiResp.p2 = directionName;
		return yaiResp;
	}

	void laser(boolean active) {
		if (active) {
			digitalWrite(PinLaser, HIGH);
		} else {
			digitalWrite(PinLaser, LOW);
		}

	}

private:

	void motorHalt2WD() {
		digitalWrite(PinOUTA, LOW);
		digitalWrite(PinOUTB, LOW);
		digitalWrite(PinOUTC, LOW);
		digitalWrite(PinOUTD, LOW);
	}

};

#endif
