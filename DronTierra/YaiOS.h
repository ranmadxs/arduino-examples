#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "RoverLink.h"
#include "YaiConstants.h"


class YaiOS {
  public:
   	YaiOS(){};
  	//Funcion que obtiene el html home (index)
  	String getIndex();
    //Funcion que obtiene html API Doc
    String getAPI();
    //Obtiene HTML del Joistick del rover
    String getRoverJoystick();

    String getJS();
   
    //Execute jsonCommand
    String executeCommand(String command);

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
