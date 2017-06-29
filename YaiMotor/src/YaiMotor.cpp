#include <Arduino.h>
//#include "RoverLink.h"
#include "YaiCommons.h"
//#include "ObstacleLink.h"
#include <string.h>
//#include <Thread.h>
//#include <ThreadController.h>
#include <Wire.h>
#include "YaiCommunicator.h"

//RoverLink roverLn;

//ObstacleLink obstacleLn;
YaiCommunicator yaiCommunicator;
//String answerI2C = "RDY";

YaiUtil yaiUtil;

//int TIME_INTERVAL_SERVO = 15;
//Thread threadObstacleRun;
//ThreadController threadController;

//void callbackObstacleRead(){
//	obstacleLn.callbackObstacleRead();
//}


YaiCommand executeCommand(YaiCommand yaiCommand){
	YaiCommand yaiResponse;
	YaiCommand yaiResponseSvc;
	//yaiResponse.type = String(YAI_COMMAND_TYPE_RESULT);
	//yaiResponse.p1 = String(STATUS_NOK);
	//yaiResponse.p2 = String(YAI_COMMAND_TYPE_NONE);
	//yaiResponse.p3 = String(YAI_COMMAND_TYPE_NONE);
	//yaiResponse.p4 = String(YAI_COMMAND_TYPE_NONE);
	yaiResponse.type = "RESULT";
	yaiResponse.p1 = "NOK";
	yaiResponse.p2 = "NONE";
	yaiResponse.p3 = "NONE";
	yaiResponse.p4 = "NONE";
	//String content = "Command not found";
	//String resultStr = "NOK";
	//String responseSvc;
	String commandRoot = yaiCommand.command;
	Serial.print("commandRoot::");
	Serial.println(commandRoot);
	Serial.print("p1::");
	Serial.println(yaiCommand.p1);
	//String jsonResult = "{\""+String(YAI_COMMAND_TYPE_RESULT)+"\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
	boolean respCommand = false;
	int rovStopCmd = 100002;
	if (commandRoot == String(ROVER_STOP)){
		Serial.println(ROVER_STOP);
		yaiResponse.p1 ="OK";
		//resultStr = "OK";
		respCommand = true;
	    //roverLn.motorStop(yaiCommand.p1.toInt());
	    //content = "{\"TIME:\":" + yaiCommand.p2 + ", \"ROVER\":\"STOP\"}";
	}
	if (commandRoot == String(LASER_ACTION)){
		yaiResponse.p1 = String(STATUS_OK);
		//resultStr = "OK";
		respCommand = true;
	    //content = "{\"LASER_STATUS\": "+yaiCommand.p1+", \"TIME\": " + yaiCommand.p2 + "}";
	    boolean activar = false;
	    if(yaiCommand.p1 == "true"){
	    	activar = true;
	    }
	    yaiResponse.p2 = yaiCommand.p1;
	    //roverLn.laser(activar);
	}
	if(commandRoot == String(ROVER_MOVE_MANUAL_BODY)){
		Serial.println("ROVER_MOVE_MANUAL_BODY");
		yaiResponse.p1 = String(STATUS_OK);
		//resultStr = "OK";
		respCommand = true;
		//yaiResponseSvc = roverLn.motorMove(yaiCommand.p1, yaiCommand.p4);
		yaiResponse.p2 = yaiResponseSvc.p2;
	    //content = "{\"TIME:\":" + yaiCommand.p2 + ", \"ROVER\":\""+responseSvc+"\"}";
	}
	if (commandRoot == String(OBSTACLE_READER)){
		yaiResponse.p1 = "OK";
		//resultStr = "OK";
		respCommand = true;
		//yaiResponseSvc = obstacleLn.distancia(yaiCommand.p1.toInt(), yaiCommand.p2.toInt());
		//yaiResponse.p2 = yaiResponseSvc.p2;
		yaiResponse.p2 = "0.0";
	    //content = "{\"OBSTACLE_SENSOR\":"+responseSvc+"}";
	}

	String msgResp = yaiResponse.type + "," + yaiResponse.p1 + "," + yaiResponse.p2 + "," +
				yaiResponse.p3 + "," + yaiResponse.p4;
	Serial.println("----------");
	Serial.print(yaiResponse.type);
	Serial.print(" p1 : ");
	Serial.print(yaiResponse.p1);
	Serial.print(" p2 : ");
	Serial.print(yaiResponse.p2);
	Serial.print(" p3 : ");
	Serial.print(yaiResponse.p3);
	Serial.print(" p4 : ");
	Serial.println(yaiResponse.p4);
	Serial.println("------------");
	Serial.println(msgResp);
	Serial.println("------------**");
	yaiResponse.message = msgResp;
	//	jsonResult = "{\""+String(YAI_COMMAND_TYPE_RESULT)+"\"";
	//	Serial.print(jsonResult);
	//	jsonResult += ":\""+resultStr+"\", \"CONTENT\":";
	//    Serial.print(":\""+resultStr+"\", \"CONTENT\":");
	//    jsonResult += content + "}";
	//   Serial.println(content + "}");


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

String bufferCmd = "";
boolean receiveFull = false;
String commandI2C = "";
String answerOk = "OK";
boolean receive = false;
String respToMaster;

void receiveEvent(int countToRead) {

	YaiBufferCommand requestFromMaster = yaiCommunicator.receiveI2CFromMaster();
	answerOk = "PART"+String(requestFromMaster.part)+"/"+String(requestFromMaster.total)+",OK";
	respToMaster = answerOk;
	if(requestFromMaster.status == String(STATUS_OK)){
		commandI2C = requestFromMaster.content;
		receiveFull = true;
	}
	receive = true;
	/*
	YaiCommand yaiResCmdI2C;
	YaiCommand yaiCommandI2C;
	YaiBufferCommand requestFromMaster = yaiCommunicator.receiveI2CFromMaster();
	String answerOk = "PART"+String(requestFromMaster.part)+"/"+String(requestFromMaster.total)+",OK";
	Serial.println(answerOk);
	bufferCmd = bufferCmd + requestFromMaster.partContent;
	if(requestFromMaster.status == String(STATUS_OK)){
		Serial.print("FULL::");
		Serial.println(bufferCmd);		
	//	receive = true;
	//	commandI2C = requestFromMaster.content;
	//	yaiCommandI2C.message = requestFromMaster.content;
	//	yaiResCmdI2C = executeCommand(yaiCommandI2C);
	//	answerI2C = "XDDD";
		bufferCmd = "";
	}
	*/
}

void requestEvent() {	
	yaiCommunicator.sendI2CToMaster(answerOk);	
	//Serial.println("<< " + answer);
}

void setup() {	
	Serial.begin(9600);
	Serial.println("***********************");
	Serial.println("Yai motor inicializado");
	Serial.println("***********************");
	Serial.println("Serial port ready");
	//threadObstacleRun.onRun(callbackObstacleRead);
	//threadObstacleRun.setInterval(TIME_INTERVAL_SERVO);
	//threadController.add(&threadObstacleRun);
	Serial.println("Thread Obstacle inicializado");
	Wire.begin(I2C_CLIENT_YAI_MOTOR);
	Wire.onRequest(requestEvent);
	Wire.onReceive(receiveEvent);
	Serial.println("I2C ready! " + String(MAX_I2C_COMAND) + " Bytes");
}

void loop() {
 //threadController.run();
	if(receive){
		Serial.print(" >> ");
		Serial.println(answerOk);
		receive = false;
	}
	if(receiveFull){
		YaiCommand yaiCommandI2C;
		YaiCommand yaiResCmdI2C;

		Serial.print(" Full >> ");
		Serial.println(commandI2C);
		yaiCommandI2C.message = commandI2C;
		yaiUtil.string2YaiCommand(yaiCommandI2C);

		if(yaiCommandI2C.execute){
			yaiResCmdI2C = executeCommand(yaiCommandI2C);
			answerOk = yaiResCmdI2C.message;
		}

		receiveFull = false;
	}

	//serialController();
}
