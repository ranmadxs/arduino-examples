#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "RoverLink.h"

#define ROVER_TYPE_2WD                  1001

#define ROVER_BODY_MOVE_TYPE_LEFT       2001
#define ROVER_BODY_MOVE_TYPE_RIGHT      2002
#define ROVER_BODY_MOVE_TYPE_FORWARD    2003
#define ROVER_BODY_MOVE_TYPE_BACK       2004

#define ROVER_MOVE_MANUAL_BODY          100001
#define ROVER_STOP                      100002
#define YAI_SERIAL_CMD_GET_IP           100003

class YaiOS {
  public:

   	YaiOS();
  	//Funcion que obtiene el html home (index)
  	String getIndex();
    //Funcion que obtiene html API Doc
    String getAPI();
    //Obtiene HTML del Joistick del rover
    String getRoverJoystick();

    String getJS();
  
    //Execute jsonCommand
    void executeCommand(String command);

    String getClientIP(){
      return clientIP;
    }

    void setClientIP(String clientIPIN){
      clientIP = clientIPIN;
    }

    String getMac(){
      return macStr ;
    }

    void setMac(byte ar[]){
      for (byte i = 0; i < 6; ++i){
        char buf[3];
        sprintf(buf, "%2X", ar[i]);
        macStr += buf;
        if (i < 5) macStr += ':';
      }
    }

    void setMac(String macIN){
    	macStr = macIN;
    }
    
  private:
    RoverLink roverLn;
    String clientIP;
    String macStr;
    
};
