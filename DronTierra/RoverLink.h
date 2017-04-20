#include <Arduino.h> 

//Derecha
static int PinOUTA   = 5; // (D1)
static int PinOUTB   = 4; // (D2)

//Izquierda
static int PinOUTC   = 0; // (D3)
static int PinOUTD   = 2; // (D4)  <- Este es el que apaga el Lolin

//Laser
static int PinLaser = 14; // (D5)

class RoverLink {
  public:

    //Constructor de la clase
    RoverLink();

    //Detiene el Rover

    void motorStop(int roverType);

    String motorMove(int roverType, int moveType);

    void laser(boolean active);
  
  private:

    void motorHalt2WD();
};
