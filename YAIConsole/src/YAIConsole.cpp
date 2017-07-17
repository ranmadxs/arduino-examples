#include <Arduino.h>
#include "YaiCommons.h"
#include "YaiLCD.h"

/*
typedef struct {
  int x;
  int y;
} XY;
*/

YaiUtil yaiUtil;
YaiLCD yaiLCD;

void printCommand(YaiCommand yaiCommand){
	yaiLCD.printCmd(yaiCommand);
	Serial.println(yaiCommand.message);

}

void serialController(){
	YaiCommand yaiCommand;
	yaiCommand = yaiUtil.commandSerialFilter();
	//TODO: no propaga asi que solo ejecuta los CMD
	if(yaiCommand.print){
		printCommand(yaiCommand);
	}
}

void setup() {
  Serial.begin(9600);
  yaiLCD.init();
  Serial.println("YaiConsole V0.0.1-SNAPSHOT");

}

void loop() {
	serialController();
}
