#include <Arduino.h>
#include "RoverLink.h"
#include "YaiCommons.h"
#include "ObstacleLink.h"
#include <string.h>

RoverLink roverLn;
ObstacleLink obstacleLn;

YaiUtil yaiUtil;

void serialController(){
  String serialIn = "";  
  if (Serial.available() >0) {
    serialIn = Serial.readStringUntil('\n');
    if (serialIn.length() >0){
        String root[8];
        yaiUtil.getElementRoot(serialIn, root);
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

    	int command = commandRoot.toInt();

    	if (commandRoot == String(ROVER_STOP)){
    		respCommand = true;
    	    int tiempoStop = p2.toInt();
    	    delay(tiempoStop);
    	    roverLn.motorStop(p1.toInt());
    	    content += "{\"TIME:\":" + p2 + ", \"ROVER\":\"STOP\"}";
    	}
    	if (commandRoot == String(LASER_ACTION)){
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
    	if(commandRoot == String(ROVER_MOVE_MANUAL_BODY)){
          respCommand = true;
          int tiempoStop = p2.toInt();
          delay(tiempoStop);    
          responseSvc = roverLn.motorMove(p1, p4);
          content += "{\"TIME:\":" + p2 + ", \"ROVER\":\""+responseSvc+"\"}";
    	}
    	if (commandRoot == String(OBSTACLE_READER)){
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

void setup() {
	Serial.begin(9600);
}

void loop() {
 serialController();
 delay(50);
}

