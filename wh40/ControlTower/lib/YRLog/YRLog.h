#ifndef YRLog_h
#define YRLog_h

#include <Arduino.h>
#include <Time.h>

//platformio lib search Time
//platformio lib install 44

class YRLog {
public:

	void init(String yr_name){
		yrname = yr_name;
	}

	void info(String str){
		Serial.println(yrname + " [INFO] " +str);
	}
	void error(String str){
		Serial.println(yrname + " [ERROR] " +str);
	}
	void debug(String str){
		Serial.println(yrname + " [DEBUG] " +str);
	}
	void warn(String str){
		Serial.println(yrname + " [WARN] " +str);
	}

protected:
	String yrname;

};

#endif
