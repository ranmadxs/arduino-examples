#include <Arduino.h> 


#define ROVER_TYPE_2WD					        1001

#define ROVER_BODY_MOVE_TYPE_LEFT		    2001
#define ROVER_BODY_MOVE_TYPE_RIGHT		  2002
#define ROVER_BODY_MOVE_TYPE_FORWARD	  2003
#define ROVER_BODY_MOVE_TYPE_BACK		    2004

#define ROVER_SERIAL_CMD_GET_IP         3001

class RoverLink {
  public:

        //Constructor de la clase
    RoverLink();
 
    //Funcion que obtiene API Doc
    String getIndex();
  
  private:
};
