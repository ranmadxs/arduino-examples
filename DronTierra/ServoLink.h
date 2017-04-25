#include <Arduino.h> 

class ServoLink{
  public:
    ServoLink();

    String servoMove(int servoType, int servoDirection, int servoMovement);
    
  private:
  
};
