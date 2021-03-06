#include "YaiOS.h"

int YaiOS::countFilesInDirectory(File dir) {
	int count = 0;
	while (true) {

		File entry = dir.openNextFile();
		if (!entry) {
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

String YaiOS::getNewLogFileName(int index, int ceros){
  String res = String(index);
  String strIndex = String (index);

  int totalCeros = ceros - strIndex.length();
  for (int j = 0; j < totalCeros; j++){
    res =  "0" + res;
  }
  return res;
}

YaiParseFile YaiOS::getFileLogLines(int lineInit, int lineEnd,
		boolean printSerial) {
	YaiParseFile yaiFile;
	String contentLogFile = "";
	int countLine = 0;
	yaiFile.fileName = logFileName;
	yaiFile.codeStatus = 404;
	yaiFile.fileExist = false;
	char ltr;
	String lineStr = "";
	//Serial.println("lineInit:" + String(lineInit)+ "  lineEnd:" + lineEnd);
	if (logEnabled) {
		File logFile = SD.open(logFileName);
		if (logFile) {
			yaiFile.fileExist = true;
			yaiFile.codeStatus = 200;
			yaiFile.contentType = "text/plain";
			while (logFile.available()) {
				countLine++;
				lineStr = logFile.readStringUntil('\n');
				if (countLine >= lineInit && countLine <= lineEnd) {
					//ltr = logFile.read();
					contentLogFile = contentLogFile + lineStr;
					if (printSerial) {
						Serial.println(lineStr);
					}
					//contentLogFile = contentLogFile.concat('\n');
				}
				if (countLine > lineEnd) {
					break;
				}
			}
		}
		logFile.close();
	}
	yaiFile.totalLines = countLine;
	yaiFile.content = contentLogFile;
	return yaiFile;
}

boolean YaiOS::existsFile(String fileName) {
	boolean existe = false;
	File myFile = SD.open(fileName);
	if (myFile) {
		existe = true;
	}
	myFile.close();
	return existe;
}
;

YaiParseFile YaiOS::parseSDFile(String fileName, YaiParam params[],
		int totalParams) {
	YaiParseFile yaiFile;
	int countLine = 0;
	String strReturn = "File not found in SD (" + fileName + ")";
	yaiFile.fileName = fileName;
	yaiFile.codeStatus = 404;
	yaiFile.fileExist = false;
	String varName;
	char ltr;
	if (logEnabled) {
		String SD_Read = "";
		File myFile;
		logDebug("Abriendo archivo :: " + fileName);
		myFile = SD.open(fileName);
		if (myFile) {
			while (myFile.available()) {
				//ltr = myFile.read();
				SD_Read += myFile.readStringUntil('\n');
				countLine++;
			}
			if (totalParams > 0) {
				for (int i = 0; i < totalParams; i++) {
					varName = "${" + params[i].nombre + "}";
					SD_Read.replace(varName, params[i].valor);
				}
			}
			strReturn = SD_Read;
			yaiFile.fileExist = true;
			yaiFile.codeStatus = 200;
			yaiFile.contentType = "text/html";
			if (fileName.indexOf(".css") > 0) {
				yaiFile.contentType = "text/css";
			}
			if (fileName.indexOf(".js") > 0) {
				yaiFile.contentType = "application/javascript";
			}
		} else {
			logError("Error al abrir el archivo handleRoot");
		}
		myFile.close();
	}
	yaiFile.totalLines = countLine;
	yaiFile.content = strReturn;
	return yaiFile;
}
