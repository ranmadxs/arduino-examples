#ifndef YaiOS_h
#define YaiOS_h
#include <Wire.h>
#include <Arduino.h>
#include "ServoLink.h"
#include "YaiCommons.h"
#include <SD.h>
//#include "YaiCommunicator.h"

static int PinSDCard = 15;
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
			totalLines = 0;
		};
		String fileName;
		boolean fileExist;
		String content;
		String contentType;
		int codeStatus;
		int totalLines;
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
   		serverIP = "0.0.0.0";
   	};

   	int countFilesInDirectory(File dir);

   	YaiParseFile baseSDTemplate(String fileName);

   	boolean existsFile(String fileName);

   	String executeCommand(String pipelineCommand[], int totalCmds);

    void initSD(){
      String logFolder = String(YAI_LOG_FOLDER);
      if (!SD.begin(PinSDCard)) {
        logEnabled = false;
        Serial.println("Error iniciando SD Card");
      }else{
        Serial.println("SD Card connected !!!!");
        File folderRootLogs = SD.open(logFolder);
        if(folderRootLogs){
        	logEnabled = true;
			int totalFiles = countFilesInDirectory(folderRootLogs);
			totalFiles++;
			logFileName = logFolder+"/"+getNewLogFileName(totalFiles, 8)+".LOG";
			while(existsFile(logFileName)){
				totalFiles++;
				logFileName = logFolder+"/"+getNewLogFileName(totalFiles, 8)+".LOG";
				Serial.println("[WARN] Archivo de log existe se incrementa : " + logFileName);
			}
			Serial.println("Log file " + logFileName);
		}else{
			logEnabled = false;
			Serial.println("[ERROR] Folder "+logFolder+" do not exist");
		}
      }

    };

    YaiParseFile parseSDFile(String fileName, YaiParam params[], int totalParams);

    YaiParseFile getFileLogLines(int lineInit, int lineEnd, boolean printSerial);

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
    YaiCommand executeCommand(YaiCommand command);

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
    
    void setServerIP(String _ip){
    	serverIP = _ip;
    }

    String getServerIP(){
    	return serverIP;
    }

    void setServerSsid(String _ssid){
    	serverSsid = _ssid;
    }

    String getServerSsid(){
    	return serverSsid;
    }

  private:    
    String logFileName;
    ServoLink servoLn;
    String clientIP;
    String serverIP;
    String serverSsid;
    String macStr;
    boolean logEnabled;    
	YaiUtil yaiUtil;
	int paramsYai;
  
	String getNewLogFileName(int index, int ceros);
  
    void logBase(String tipo, String msgLog){
       if(logEnabled){
        File logFile = SD.open(logFileName, FILE_WRITE);
        if (logFile) {
          logFile.print("["+tipo+"]  (");
          logFile.print(String(millis()));
          logFile.print(") ");
          logFile.println(msgLog);
          logFile.close();
        }
      }      
    }
};

#endif
