#include <Arduino.h>
#include "YRCommand.h"
#include "YRCommons.h"
#include "YRUtil.h"
#include "YRServoSvc.h"

YRServoSvc yrServoSvc;
YRUtil yaiUtil;
int arrayServoId[] = { 9 };

String executeCommand(String masterCommand) {
	String responseExe = String(YAI_COMMAND_TYPE_RESULT);
	String resultStr = String(STATUS_NOK);
	String content = String(YAI_COMMAND_TYPE_NONE);
	String rootCmd[9];
	yaiUtil.getElementRoot(masterCommand, rootCmd);
	String commandRoot = rootCmd[1];
	String actionRoot = rootCmd[2];
	Serial.println("commandRoot=" + commandRoot);
	Serial.println("actionRoot=" + actionRoot);
	String tipoServo = rootCmd[3];
	if (commandRoot == YR_TYPE_SERVO) {
		if (actionRoot == yrServoSvc.SERVO_ACTION_ANGLE) {
			resultStr = String(STATUS_OK);
			int angulo = rootCmd[5].toInt();
			String idServo = rootCmd[4];
			if (idServo == yrServoSvc.SERVO_ACTION_ALL) {
				content = yrServoSvc.SERVO_ACTION_ALL +","+ String(angulo);
				for (int i = 0; i < (sizeof(arrayServoId)/sizeof(int)); i++) {
					yrServoSvc.setAngle(tipoServo, arrayServoId[i], angulo);
				}
			} else {
				content = idServo + "," + yrServoSvc.setAngle(tipoServo, idServo.toInt(),
						angulo);
			}
		}
	}
	responseExe = responseExe + "," + resultStr + "," + content;
	return responseExe;
}

void serialController() {
	YRCommand yrCommand;
	yrCommand = yaiUtil.commandSerialFilter();
	if (yrCommand.execute) {
		String respSerialCmd = executeCommand(yrCommand.message);
		if (yrCommand.print) {
			Serial.println(">> [SERIAL] " + yrCommand.message);
			Serial.println("<< [SERIAL] " + respSerialCmd);
		}
	}
}

void setup() {
	Serial.begin(9600);
	Serial.println("***************************");
	Serial.println("Yai Finger V0.0.1-SNAPSHOT");
	yrServoSvc.init(arrayServoId);
	Serial.println("***************************");
}

void loop() {
	serialController();
}
