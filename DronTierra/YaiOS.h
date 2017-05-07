#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "ServoLink.h"
#include "YaiConstants.h"
#include <SD.h>

static int PinSDCard = 4;

class YaiOS {
  public:
   	YaiOS(){
      
   		logEnabled = false;
   	};

    void init(){
      if (!SD.begin(PinSDCard)) {
        logEnabled = false;
        Serial.println("No se pudo inicializar SD Card");
      }else{
        logEnabled = true;
        Serial.println("SD Card Inicializado!!!");        
      }

    };

   	void logInfo(String msgLog){
      logBase("INFO", msgLog);
   	};

     void logDebug(String msgLog){
      logBase("DEBUG", msgLog);
    };

     void logError(String msgLog){
      logBase("ERROR", msgLog);
    };

     void logWarn(String msgLog){
      logBase("WARN", msgLog);
    };
    
  	//Funcion que obtiene el html home (index)
  	String getIndex();
    //Funcion que obtiene html API Doc
    String getAPI();
    String getAPIServo();
    //Obtiene HTML del Joistick del rover
    String getRoverJoystick();

    String getJS();

    void callBackServoMovement(){
      servoLn.callBackMovement();
    };

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
    ServoLink servoLn;
    String clientIP;
    String macStr;
    File logFile;
    boolean logEnabled;    

    void logBase(String tipo, String msgLog){
       if(logEnabled){
        logFile = SD.open("LOGS/logYAI.log", FILE_WRITE);
        logFile.print("["+tipo+"] (");
        logFile.print(String(millis()));
        logFile.print(") ");
        logFile.println(msgLog);
        logFile.close();
      }      
    }
};
