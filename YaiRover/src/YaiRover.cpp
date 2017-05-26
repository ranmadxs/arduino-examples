#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Thread.h>
#include <ThreadController.h>
#include "YaiOS.h"

/*
 * Main.cpp
 *

 *  Created on: 23-05-2017
 *      Author: esanchez
 */

const int totalWifi = 3;
const int retryWifi = 15;

char* arrayWifi[totalWifi][2] = {
  {"VTR-YAI-5Ghz", "Pana8bc1108"},
  {"yai", "1101000000"},
  {"GalaxyJ1", "1101000000"}
};

YaiOS yaiOS;
YaiUtil yaiUtil;
//TODO: Llevarse los thread a yaoiOS
int TIME_INTERVAL_SERVO = 15;
Thread threadServoRun;
ThreadController threadController;

void serialController(){
	YaiCommand yaiCommand;
	yaiCommand = yaiUtil.commandSerialFilter();
	if(yaiCommand.execute){
		yaiOS.executeCommand(yaiCommand);
	}
}

void callBackServoThread(){
  yaiOS.callBackServoMovement();
}

ESP8266WebServer server(80);

void handleRoot() {
  String htmlSrc;
  htmlSrc = yaiOS.getIndex();
  server.send ( 200, "text/html", htmlSrc );
}

void handleAPI(){
	  String htmlSrc;
	  htmlSrc = yaiOS.getAPI();
	  server.send ( 200, "text/html", htmlSrc );
}

void handleAPIServo(){
    String htmlSrc;
    htmlSrc = yaiOS.getAPIServo();
    server.send ( 200, "text/html", htmlSrc );
}

void handleRoverJoystick(){
    String htmlSrc;
    htmlSrc = yaiOS.getRoverJoystick();
    server.send ( 200, "text/html", htmlSrc );
}

void handleNotFound(){
  String content_type = "text/plain";
  String message = "File Not Found\n\n";
  int codeStatus = 404;
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  YaiParseFile yaiFile = yaiOS.baseSDTemplate(server.uri());
  if(yaiFile.fileExist){
	  message = yaiFile.content;
	  content_type = yaiFile.contentType;
	  codeStatus = yaiFile.codeStatus;
  }
  server.send(codeStatus, content_type, message);
}

void setup(void){

	//Serial.begin(115200);
	Serial.begin(9600);
	Serial.println("");
	yaiOS.initSD();
	yaiOS.logInfo("SD card inicializada");

	threadServoRun.onRun(callBackServoThread);
	threadServoRun.setInterval(TIME_INTERVAL_SERVO);
	threadController.add(&threadServoRun);
	yaiOS.logInfo("Thread servo inicializado");

	char* ssid;
	char* password;

	for (int j = 0; j<totalWifi; j++){
		Serial.print("Conectando a " + String(arrayWifi[j][0]) + " ");
	    ssid = arrayWifi[j][0];
	    password = arrayWifi[j][1];
	    WiFi.begin(ssid, password);
	    for (int k = 0; k < retryWifi; k++){
	    	if(WiFi.status() == WL_CONNECTED){
	    		k = retryWifi;
	    		j = totalWifi;
	    		Serial.print(" Conectado!!!");
	    	}else{
	    		delay(500);
	    		Serial.print(".");
	    	}
	    }
	    Serial.println("");
	}
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to: ");
	Serial.println(ssid);
	yaiOS.logInfo("Connected to: " + String(ssid));
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	yaiOS.setClientIP(WiFi.localIP().toString());
	yaiOS.setMac(WiFi.macAddress());
	if (MDNS.begin("esp8266")) {
		Serial.println("MDNS responder started");
	}
	yaiOS.logInfo("IP: " + yaiOS.getClientIP());

	server.on("/", handleRoot);
	server.on("/api", handleAPI);
	server.on("/apiServo", handleAPIServo);
	server.on("/roverJoystick", handleRoverJoystick);
	server.on("/cmd", [](){
		String message = "";
		String jsonCommand = "";
		for (uint8_t i=0; i<server.args(); i++){
			jsonCommand += server.arg(i);
			if(i + 1 < server.args()){
				jsonCommand += ",";
			}
		}
		message += " << " + jsonCommand;
		YaiCommand yaiCommand;
		yaiCommand.type = String(YAI_COMMAND_TYPE_SERIAL);
		yaiCommand.message = jsonCommand;
		yaiUtil.string2Serial(yaiCommand);
		String responseMsg = yaiOS.executeCommand(yaiCommand);
		message += "\n \n >> " + responseMsg;
		server.send(200, "text/plain", message);
	});

	server.on("/pipelineCmd", []{
		String message = "{\"RESULT\"=\"OK\"";
	    int totalCmds = 0;
	    String responseMsg = "\"EXECUTE\":0";
	    if(server.args() > 0){
	    	String pipeline[server.args()];
	    	for (uint8_t i=0; i<server.args(); i++){
	    		pipeline[i] = server.arg(i);
	  			totalCmds++;
	  		}
	  		responseMsg = yaiOS.executeCommand(pipeline, totalCmds);
	    }
	    message += ", \"PIPELINE\":{\"TOTAL_IN\":"+String(totalCmds);
	    message += ", " + responseMsg + "}";
	    server.send(200, "text/plain", message);
	});

	server.onNotFound(handleNotFound);

	server.begin();
	Serial.println("HTTP server started");
	yaiOS.logInfo("HTTP server started");
}

void loop(void){
	server.handleClient();
	serialController();
	threadController.run();
}
