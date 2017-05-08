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

class YaiParam{
	public:
		YaiParam(){};

		String nombre;
		String valor;
};


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

    String parseSDFile(String fileName, YaiParam params[], int totalParams){
    	String strReturn = "No content SD "+ fileName;
    	String varName;
    	char ltr;
    	if (logEnabled){
			String SD_Read = "";
			File myFile;
			logDebug("Abriendo archivo :: " + fileName);
			myFile = SD.open(fileName);
			if (myFile) {
				while (myFile.available()) {
					ltr = myFile.read();
			    	SD_Read += ltr;
				}
				if (totalParams > 0){
					for (int i = 0; i < totalParams; i++) {
						varName = "${" +params[i].nombre+ "}";
						SD_Read.replace(varName, params[i].valor);
					}
				}
				strReturn = SD_Read;
			}else {
				logError("Error al abrir el archivo handleRoot");
			}
			myFile.close();
    	}

    	return strReturn;
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

	int paramsYai;

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
