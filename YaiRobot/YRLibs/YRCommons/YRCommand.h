#ifndef YaiCommons_h
#define YaiCommons_h

#include <Arduino.h>
#include "YRCommons.h"

class YRCommand {

public:
	YRCommand() {
		execute = false;
		print = false;
		propagate = false;
		message = "";
		type = String(YAI_COMMAND_TYPE_NONE);
		p1 = String(YAI_COMMAND_TYPE_NONE);
		p2 = String(YAI_COMMAND_TYPE_NONE);
		p3 = String(YAI_COMMAND_TYPE_NONE);
		p4 = String(YAI_COMMAND_TYPE_NONE);
		p5 = String(YAI_COMMAND_TYPE_NONE);
		p6 = String(YAI_COMMAND_TYPE_NONE);
		p7 = String(YAI_COMMAND_TYPE_NONE);
		address = 0;
		json = "";
	}

	String message;
	String type;
	String command;
	String p1;
	String p2;
	String p3;
	String p4;
	String p5;
	String p6;
	String p7;
	String json;
	boolean execute;
	boolean print;
	boolean propagate;
	int address;

};

#endif
