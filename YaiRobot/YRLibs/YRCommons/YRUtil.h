#ifndef YRUtil_h
#define YRUtil_h

#include <Arduino.h>
#include "YRCommand.h"
#include "YRCommons.h"

class YRUtil {
public:
	YRUtil() {
	}

	YRCommand commandSerialFilter() {
		String serialIn;
		YRCommand yaiCommand;
		yaiCommand.type = String(YAI_COMMAND_TYPE_NONE);
		yaiCommand.message = "";
		yaiCommand.execute = false;
		yaiCommand.print = false;
		if (Serial.available() > 0) {
			serialIn = Serial.readStringUntil('\n');
			if (serialIn.length() > 0) {
				yaiCommand.message = serialIn;
				yaiCommand.type = String(YAI_COMMAND_TYPE_SERIAL);
				string2YaiCommand(yaiCommand);
			}
		}
		return yaiCommand;
	}

	void string2YaiCommand(YRCommand &yaiCommand) {
		yaiCommand.command = "";
		yaiCommand.execute = false;
		yaiCommand.type = String(YAI_COMMAND_TYPE_NONE);
		if (yaiCommand.message != "") {
			yaiCommand.print = true;
			String root[9];
			if (yaiCommand.message.indexOf(String(YAI_COMMAND_TYPE_RESULT))
					> 0) {
				yaiCommand.type = String(YAI_COMMAND_TYPE_RESULT);
			} else {
				getElementRoot(yaiCommand.message, root);
				yaiCommand.type = root[0];
				if (yaiCommand.type == String(YAI_COMMAND_TYPE_SERIAL)
						|| yaiCommand.type == String(YAI_COMMAND_TYPE_SPI)
						|| yaiCommand.type == String(YAI_COMMAND_TYPE_WIFI)
						|| yaiCommand.type == String(YAI_COMMAND_TYPE_I2C))
					yaiCommand.execute = true;
				yaiCommand.command = root[1];
				yaiCommand.p1 = root[2];
				yaiCommand.p2 = root[3];
				yaiCommand.p3 = root[4];
				yaiCommand.p4 = root[5];
				yaiCommand.p5 = root[6];
				yaiCommand.p6 = root[7];
				yaiCommand.p7 = root[8];
			}
		}
	}

	void string2YaiRespCommand(YRCommand &yaiCommand) {
		yaiCommand.execute = false;
		yaiCommand.type = String(YAI_COMMAND_TYPE_NONE);
		if (yaiCommand.message.indexOf(String(YAI_COMMAND_TYPE_RESULT)) > 0) {

			String root[9];
			getElementRoot(yaiCommand.message, root);
			yaiCommand.type = root[0];
			yaiCommand.p1 = root[1];
			yaiCommand.p2 = root[2];
			yaiCommand.p3 = root[3];
			yaiCommand.p4 = root[4];
		}

	}

	char *strSplit(char *str, const char *delim, char **save) {
		char *res, *last;

		if (!save)
			return strtok(str, delim);
		if (!str && !(str = *save))
			return NULL;
		last = str + strlen(str);
		if ((*save = res = strtok(str, delim))) {
			*save += strlen(res);
			if (*save < last)
				(*save)++;
			else
				*save = NULL;
		}
		return res;
	}

	void getElementRoot(String myString, String rootElement[]) {
		char copy[64];
		myString.toCharArray(copy, 64);
		char *p = copy;
		char *str;

		int i = 0;

		while ((str = strSplit(p, ",", &p)) != NULL) {
			rootElement[i] = str;
			i++;
		}
	}

};

#endif
