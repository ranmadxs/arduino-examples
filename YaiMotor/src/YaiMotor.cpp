#include <Arduino.h>
#include "RoverLink.h"
#include "YaiCommons.h"
#include "ObstacleLink.h"
#include <string.h>
#include <Thread.h>
#include <ThreadController.h>

RoverLink roverLn;
ObstacleLink obstacleLn;

YaiUtil yaiUtil;

int TIME_INTERVAL_SERVO = 15;
Thread threadObstacleRun;
ThreadController threadController;

void callbackObstacleRead(){
	obstacleLn.callbackObstacleRead();
}

YaiCommand executeCommand(YaiCommand yaiCommand){
	YaiCommand yaiResponse;
	YaiCommand yaiResponseSvc;
	yaiResponse.type = String(YAI_COMMAND_TYPE_RESULT);
	yaiResponse.p1 = String(STATUS_NOK);
	//String content = "Command not found";
	//String resultStr = "NOK";
	//String responseSvc;
	String commandRoot = yaiCommand.command;
	//String jsonResult = "{\""+String(YAI_COMMAND_TYPE_RESULT)+"\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
	//boolean respCommand = false;
	if (commandRoot == String(ROVER_STOP)){
		yaiResponse.p1 = String(STATUS_OK);
		//resultStr = "OK";
		//respCommand = true;
	    roverLn.motorStop(yaiCommand.p1.toInt());
	    //content = "{\"TIME:\":" + yaiCommand.p2 + ", \"ROVER\":\"STOP\"}";
	}
	if (commandRoot == String(LASER_ACTION)){
		yaiResponse.p1 = String(STATUS_OK);
		//resultStr = "OK";
		//respCommand = true;
	    //content = "{\"LASER_STATUS\": "+yaiCommand.p1+", \"TIME\": " + yaiCommand.p2 + "}";
	    boolean activar = false;
	    if(yaiCommand.p1 == "true"){
	    	activar = true;
	    }
	    yaiResponse.p2 = yaiCommand.p1;
	    roverLn.laser(activar);
	}
	if(commandRoot == String(ROVER_MOVE_MANUAL_BODY)){
		yaiResponse.p1 = String(STATUS_OK);
		//resultStr = "OK";
		//respCommand = true;
		yaiResponseSvc = roverLn.motorMove(yaiCommand.p1, yaiCommand.p4);
		yaiResponse.p2 = yaiResponseSvc.p2;
	    //content = "{\"TIME:\":" + yaiCommand.p2 + ", \"ROVER\":\""+responseSvc+"\"}";
	}
	if (commandRoot == String(OBSTACLE_READER)){
		yaiResponse.p1 = String(STATUS_OK);
		//resultStr = "OK";
		//respCommand = true;
		yaiResponseSvc = obstacleLn.distancia(yaiCommand.p1.toInt(), yaiCommand.p2.toInt());
		yaiResponse.p2 = yaiResponseSvc.p2;
	    //content = "{\"OBSTACLE_SENSOR\":"+responseSvc+"}";
	}
	/*
	if(respCommand){
		jsonResult = "{\""+String(YAI_COMMAND_TYPE_RESULT)+"\"";
		Serial.print(jsonResult);
		jsonResult += ":\""+resultStr+"\", \"CONTENT\":";
	    Serial.print(":\""+resultStr+"\", \"CONTENT\":");
	    jsonResult += content + "}";
	    Serial.println(content + "}");
	}
	*/
	return yaiResponse;
}

void serialController(){
	YaiCommand yaiCommand;
	YaiCommand yaiResCmd;
	yaiCommand = yaiUtil.commandSerialFilter();
	//TODO: no propaga asi que solo ejecuta los CMD
	if(yaiCommand.execute){
		yaiResCmd = executeCommand(yaiCommand);
		//if(yaiResCmd.p1 == String(STATUS_OK)){
			Serial.println(yaiResCmd.type + "," + yaiResCmd.p1 + "," + yaiResCmd.p2 + "," + yaiResCmd.p3 + "," + yaiResCmd.p4);
		//}
	}
}

void setup() {
	Serial.begin(9600);
	Serial.println("Yai motor inicializado");
	Serial.println("Serial port ready");
	threadObstacleRun.onRun(callbackObstacleRead);
	threadObstacleRun.setInterval(TIME_INTERVAL_SERVO);
	threadController.add(&threadObstacleRun);
	Serial.println("Thread Obstacle inicializado");
}

void loop() {
 serialController();
 threadController.run();
}

