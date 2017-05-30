#include <Arduino.h>
#include "RoverLink.h"
#include "YaiCommons.h"
#include "ObstacleLink.h"
#include <string.h>

RoverLink roverLn;
ObstacleLink obstacleLn;

YaiUtil yaiUtil;

String executeCommand(YaiCommand yaiCommand){
	String content = "Command not found";
	String resultStr = "NOK";
	String responseSvc;
	String commandRoot = yaiCommand.command;
	String jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
	boolean respCommand = false;
	if (commandRoot == String(ROVER_STOP)){
		resultStr = "OK";
		respCommand = true;
		int tiempoStop = yaiCommand.p2.toInt();
		delay(tiempoStop);
	    roverLn.motorStop(yaiCommand.p1.toInt());
	    content = "{\"TIME:\":" + yaiCommand.p2 + ", \"ROVER\":\"STOP\"}";
	}
	if (commandRoot == String(LASER_ACTION)){
		resultStr = "OK";
		respCommand = true;
	    int tiempoStop = yaiCommand.p2.toInt();
	    content = "{\"LASER_STATUS\": "+yaiCommand.p1+", \"TIME\": " + yaiCommand.p2 + "}";
	    delay(tiempoStop);
	    boolean activar = false;
	    if(yaiCommand.p1 == "true"){
	    	activar = true;
	    }
	    roverLn.laser(activar);
	}
	if(commandRoot == String(ROVER_MOVE_MANUAL_BODY)){
		resultStr = "OK";
		respCommand = true;
	    int tiempoStop = yaiCommand.p2.toInt();
	    delay(tiempoStop);
	    responseSvc = roverLn.motorMove(yaiCommand.p1, yaiCommand.p4);
	    content = "{\"TIME:\":" + yaiCommand.p2 + ", \"ROVER\":\""+responseSvc+"\"}";
	}
	if (commandRoot == String(OBSTACLE_READER)){
		resultStr = "OK";
		respCommand = true;
	    responseSvc = obstacleLn.distancia(yaiCommand.p1.toInt(), yaiCommand.p2.toInt());
	    content = "{\"OBSTACLE_SENSOR\":"+responseSvc+"}";
	}
	if(respCommand){
		jsonResult = "{\"RESULT\"";
		Serial.print(jsonResult);
		jsonResult += ":\""+resultStr+"\", \"CONTENT\":";
	    Serial.print(":\""+resultStr+"\", \"CONTENT\":");
	    jsonResult += content + "}";
	    Serial.println(content + "}");
	}
	return jsonResult;
}

void serialController(){
	YaiCommand yaiCommand;
	yaiCommand = yaiUtil.commandSerialFilter();
	//TODO: no propaga asi que solo ejecuta los CMD
	if(yaiCommand.execute){
		executeCommand(yaiCommand);
	}
}

void setup() {
	Serial.begin(9600);
	Serial.println("Yai motor inicializado");
	Serial.println("Serial port ready");
}

void loop() {
 serialController();
 delay(50);
}

