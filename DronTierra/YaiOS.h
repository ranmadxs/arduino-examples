#include <Arduino.h>

class YaiOS {
  public:
	YaiOS();
	//Funcion que obtiene el html home (index)
	String getIndex();
  //Funcion que obtiene html API Doc
  String getAPI();
  //Obtiene HTML del Joistick del rover
  String getRoverJoystick();
  private:
};
