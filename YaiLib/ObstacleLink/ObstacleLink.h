#ifndef ObstacleLink_h
#define ObstacleLink_h

#include <Arduino.h>

//HC-SR04
int PinTriger = 9;   // triger
int PinEcho = 8;      // echo

class ObstacleLink{

	public:
		ObstacleLink(){
			pinMode(PinTriger, OUTPUT);
			pinMode(PinEcho, INPUT);
			tipo = 0;
		};

		//Retorna distancia en cms
		String distancia(int _tipo, int directionId){
			long tiempo;
			tipo = _tipo;
			float distancia;
			digitalWrite(PinTriger,LOW);
			delayMicroseconds(5);
			digitalWrite(PinTriger, HIGH);
			delayMicroseconds(10);
			tiempo=pulseIn(PinEcho, HIGH);
			distancia= int(0.017*tiempo);
			String resp = "{\"DISTANCE\":" + String(distancia) + "}";
			return resp;
		};

	private:
		int tipo;
};

#endif
