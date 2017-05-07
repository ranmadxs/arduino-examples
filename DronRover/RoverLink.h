#include <Arduino.h> 

//Derecha
static int PinOUTA   = 4; // (D1)
static int PinOUTB   = 5; // (D2)

//Izquierda
static int PinOUTC   = 6; // (D3)
static int PinOUTD   = 7; // (D5)  

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

    String motorMove(String roverType, String moveType);

    void laser(boolean active);
  
  private:

    void motorHalt2WD();
};
