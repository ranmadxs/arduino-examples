#include <Arduino.h> 


#define ROVER_TYPE_2WD					        "2WD"

#define ROVER_BODY_MOVE_TYPE_LEFT		    "LEFT"
#define ROVER_BODY_MOVE_TYPE_RIGHT		  "RIGHT"
#define ROVER_BODY_MOVE_TYPE_FORWARD	  "FORWARD"
#define ROVER_BODY_MOVE_TYPE_BACK		    "BACK"

#define ROVER_SERIAL_CMD_GET_IP         6

class RoverLink {
  public:

        //Constructor de la clase
    RoverLink();
 
    //Funcion que obtiene API Doc
    String getIndex();
  
  private:
};
