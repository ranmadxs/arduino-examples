#include <Arduino.h> 

//Derecha
static int PinOUTA   = 5; // (D1)
static int PinOUTB   = 4; // (D2)

//Izquierda
static int PinOUTC   = 0; // (D3)
static int PinOUTD   = 14; // (D5)  

//Laser
static int PinLaser = 12; // (D6)

class RoverLink {
  public:

    //Constructor de la clase
	RoverLink(){
		pinMode(PinOUTA, OUTPUT);
		pinMode(PinOUTB, OUTPUT);
		pinMode(PinOUTC, OUTPUT);
		pinMode(PinOUTD, OUTPUT);
		pinMode(PinLaser, OUTPUT);
	};

    //Detiene el Rover

    void motorStop(int roverType);

    String motorMove(int roverType, int moveType);

    void laser(boolean active);
  
  private:

    void motorHalt2WD();
};
