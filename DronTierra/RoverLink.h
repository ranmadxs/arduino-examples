#include <Arduino.h> 


#define ROVER_TYPE_2WD					"2WD"

#define ROVER_BODY_MOVE_TYPE_LEFT		"LEFT"
#define ROVER_BODY_MOVE_TYPE_RIGHT		"RIGHT"
#define ROVER_BODY_MOVE_TYPE_FORWARD	"FORWARD"
#define ROVER_BODY_MOVE_TYPE_BACK		"BACK"

class RoverLink {
  public:

        //Constructor de la clase
    RoverLink();
 
    //Funcion blinking: enciende el led 'pin', espera 'time' segundos y lo apaga
    String getIndex();
  
  private:
};
