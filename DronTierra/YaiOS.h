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

class YaiParseFile{
	public:
		YaiParseFile(){
			fileExist = false;
			contentType = "text/plain";
			codeStatus = 404;
		};
		String fileName;
		boolean fileExist;
		String content;
		String contentType;
		int codeStatus;
};

class YaiCmd{
  public:
    YaiCmd(){};

    String command;
    String p1;
    String p2;
    String p3;
    String p4;
    String p5;
    String p6;
    String p7;
};
class YaiOS {
  public:
   	YaiOS(){
   		logEnabled = false;
   	};

   	YaiParseFile baseSDTemplate(String fileName);

   	String executeCommand(String pipelineCommand[], int totalCmds);

    void initSD(){
      if (!SD.begin(PinSDCard)) {
        logEnabled = false;
        Serial.println("No se pudo inicializar SD Card");
      }else{
        logEnabled = true;
        Serial.println("SD Card Inicializado!!!");     
        File folderRootLogs = SD.open("/logs");
        int totalFiles = countFilesInDirectory(folderRootLogs);
        totalFiles++;
        logFileName = "/logs/"+getNewLogFileName(totalFiles, 8)+".LOG";
        Serial.println("Log file " + logFileName);   
      }

    };

    YaiParseFile parseSDFile(String fileName, YaiParam params[], int totalParams){
    	YaiParseFile yaiFile;
    	String strReturn = "File not found in SD ("+ fileName + ")";
    	yaiFile.fileName = fileName;
    	yaiFile.codeStatus = 404;
    	yaiFile.fileExist = false;
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
				yaiFile.fileExist = true;
				yaiFile.codeStatus = 200;
				yaiFile.contentType = "text/html";
				if(fileName.indexOf(".css") > 0){
					yaiFile.contentType = "text/css";
				}
				if(fileName.indexOf(".js") > 0){
					yaiFile.contentType = "application/javascript";
				}
			}else {
				logError("Error al abrir el archivo handleRoot");
			}
			myFile.close();
    	}
    	yaiFile.content = strReturn;
    	return yaiFile;
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

    String getYoistickJS();

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
    String logFileName;
    ServoLink servoLn;
    String clientIP;
    String macStr;
    boolean logEnabled;    

	int paramsYai;

  int countFilesInDirectory(File dir) {
    int count = 0;
    while (true) {

      File entry =  dir.openNextFile();
      if (! entry) {
        // no more files
        break;
      }
      if (!entry.isDirectory()) {
        count++;
      }
      entry.close();
    }
    return count;
  }
  
  String getNewLogFileName(int index, int ceros){
    String res = String(index);
    String strIndex = String (index);

    int totalCeros = ceros - strIndex.length();
    for (int j = 0; j < totalCeros; j++){
      res =  "0" + res;
    }
    return res;
  }
  
    void logBase(String tipo, String msgLog){
       if(logEnabled){
        File logFile = SD.open(logFileName, FILE_WRITE);
        if (logFile) {
          logFile.print("["+tipo+"] (");
          logFile.print(String(millis()));
          logFile.print(") ");
          logFile.println(msgLog);
          logFile.close();
        }
      }      
    }
};
