#include <Arduino.h>
#include <ArduinoJson.h>
#include "RoverLink.h"
#include "RoverConstants.h"
#include "ObstacleLink.h"
#include <string.h>

DynamicJsonBuffer dynJsonBuffer;
RoverLink roverLn;
ObstacleLink obstacleLn;

void setup() {
	Serial.begin(9600);
}

void loop() {
	serialController();
 delay(50);
}

void serialController(){
  String serialIn = "";
  int command = 0;
  if (Serial.available() >0) {
    serialIn = Serial.readStringUntil('\n');
    if (serialIn.length() >0){
        String root[8];
        getElementRoot(serialIn, root);
    	String commandRoot = root[0];
    	String responseSvc = "";
    	boolean respCommand = false;
    	String p1 = root[1];
    	String p2 = root[2];
    	String p3 = root[3];
    	String p4 = root[4];
    	String p5 = root[5];
    	String p6 = root[6];
    	String p7 = root[7];
    	String content = "";
    	String resultStr = "OK";
    	if (commandRoot == ROVER_STOP){
    		respCommand = true;
    	    int tiempoStop = p2.toInt();
    	    delay(tiempoStop);
    	    roverLn.motorStop(p1.toInt());
    	    content += "{\"TIME:\":" + p2 + ", \"ROVER\":\"STOP\"}";
    	}
    	if (commandRoot == LASER_ACTION){      
    	    respCommand = true;
    	    int tiempoStop = p2.toInt();
    	    content += "{\"LASER_STATUS\": "+p1+", \"TIME\": " + p2 + "}";
    	    delay(tiempoStop);
    	    boolean activar = false;
    	    if(p1 == "true"){
    	      activar = true;
    	    }
    	    roverLn.laser(activar);
    	}
    	if(commandRoot == ROVER_MOVE_MANUAL_BODY){
          respCommand = true;
          int tiempoStop = p2.toInt();
          delay(tiempoStop);    
          responseSvc = roverLn.motorMove(p1, p4);
          content += "{\"TIME:\":" + p2 + ", \"ROVER\":\""+responseSvc+"\"}";
    	}
    	if (commandRoot == OBSTACLE_READER){
    	  respCommand = true;
    	  responseSvc = obstacleLn.distancia(p1.toInt(), p2.toInt());
    	  content += "{\"OBSTACLE_SENSOR\":"+responseSvc+"}";
    	}

      if(respCommand){
        //String jsonResult = "{\"result\":\""+resultStr+"\", \"content\":"+content+"}";
        String jsonResult = "{\"RESULT\"";
        Serial.print(jsonResult + ":\""+resultStr+"\", \"CONTENT\":");
        Serial.println(content + "}");
      }else{
        resultStr = "NOK";        
      }
    }
  }
}

void getElementRoot(String myString, String rootElement[]){
  char copy[64];
  myString.toCharArray(copy, 64);
  char *p = copy;
  char *str;  
  
  int i = 0;
  while ((str = strtok_r(p, ",", &p)) != NULL){
    rootElement[i] = str;
    i++;
  }  
}

