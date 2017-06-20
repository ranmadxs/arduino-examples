#ifndef ObstacleLink_h
#define ObstacleLink_h

#include <Arduino.h>
#include "YaiCommons.h"

//HC-SR04
int PinTriger = 9;   // triger
int PinEcho = 8;      // echo

class ObstacleLink {

public:
	ObstacleLink() {
		pinMode(PinTriger, OUTPUT);
		pinMode(PinEcho, INPUT);
		tipo = 0;
		directionFlagF = false;
	}

	void callbackObstacleRead(){
		if(directionFlagF){
			int dirID = OBSTACLE_SENSOR_FRONT;
			distanceRead = getDistanceObstacle(dirID);
		}
	}

	//Retorna distancia en cms
	YaiCommand distancia(int _tipo, int directionId) {
		YaiCommand yaiResp;
		tipo = _tipo;
		float distancia = getDistanceObstacle(directionId);
		//String resp = "{\"DISTANCE\":" + String(distancia) + "}";
		yaiResp.p2 = String(distancia);
		return yaiResp;
	}

	float getDistanceObstacle(int directionId){
		long tiempo;
		float distancia;
		digitalWrite(PinTriger, LOW);
		delayMicroseconds(5);
		digitalWrite(PinTriger, HIGH);
		delayMicroseconds(10);
		tiempo = pulseIn(PinEcho, HIGH);
		distancia = int(0.017 * tiempo);
		return distancia;
	}

private:
	int tipo;
	boolean directionFlagF;
	float distanceRead;
};

#endif
