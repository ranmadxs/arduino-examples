#include <Arduino.h> 

//Derecha
static int PinOUTA   = 5; // (D1)
static int PinOUTB   = 4; // (D2)

//Izquierda
static int PinOUTC   = 0; // (D3)
static int PinOUTD   = 2; // (D4)

class RoverLink {
  public:

    //Constructor de la clase
    RoverLink();

    //Detiene el Rover

    void motorStop(int roverType);

    void motorMove(int roverType, int moveType);
  
  private:

    void motorHalt2WD();
};
