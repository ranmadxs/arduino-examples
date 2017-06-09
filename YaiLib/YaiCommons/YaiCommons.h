#ifndef YaiCommons_h
#define YaiCommons_h

#include <Arduino.h>

//Enum Rover Type
#define ROVER_TYPE_2WD                    		1001

//Enum Servo Type
#define SERVO_TYPE_SG90               	  		2001

//Enum Obstacle Type
#define OBSTACLE_HC_SR04                   		3001

//Rover move enum
#define ROVER_BODY_MOVE_TYPE_LEFT         		10001
#define ROVER_BODY_MOVE_TYPE_RIGHT        		10002
#define ROVER_BODY_MOVE_TYPE_FORWARD      		10003
#define ROVER_BODY_MOVE_TYPE_BACK         		10004

//Servo direction enum
#define SERVO_DIRECTION_HORIZONTAL		  		20001
#define SERVO_DIRECTION_VERTICAL		  		20002
#define SERVO_DIRECTION_ALL				  		20003

//Obstacle Direction Sensor Enum
#define OBSTACLE_SENSOR_FRONT            		30001

//Servo movement enum
#define SERVO_CLOCKWISE					  		21001   //Horario
#define SERVO_COUNTER_CLOCKWISE			  		21002   //Antihorario

//Comands
#define ROVER_MOVE_MANUAL_BODY            		100001
#define ROVER_STOP                        		100002
#define YAI_SERIAL_CMD_GET_IP             		100003
#define LASER_ACTION                      		100004
#define YAI_GET_CURRENT_LOG             		100005
#define SERVO_ACTION_CONTINUOUS	          		200001
#define SERVO_ACTION_ANGLE	        	  		200002
#define SERVO_STOP	  			      	  		200003
#define OBSTACLE_READER                    		300001

#define YAI_LOG_FOLDER							"/logs"

#define YAI_COMMAND_TYPE_SERIAL					"SERIAL"
#define YAI_COMMAND_TYPE_SPI					"SPI"
#define YAI_COMMAND_TYPE_WIFI					"WIFI"
#define YAI_COMMAND_TYPE_RESULT					"RESULT"
#define YAI_COMMAND_TYPE_NONE					"NONE"
#define YAI_COMMAND_TYPE_I2C					"I2C"

#define STATUS_OK								"OK"
#define STATUS_NOK								"NOK"

class YaiCommand{
	public:
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
		boolean execute;
};

class YaiUtil{
	public:
		YaiUtil(){}

		YaiCommand commandSerialFilter(){
			String serialIn;
			YaiCommand yaiCommand;
			yaiCommand.type = String(YAI_COMMAND_TYPE_NONE);
			yaiCommand.message = "";
			yaiCommand.execute = false;
			if (Serial.available() >0) {
				serialIn = Serial.readStringUntil('\n');
				if (serialIn.length() >0){
					yaiCommand.message = serialIn;
					yaiCommand.type=String(YAI_COMMAND_TYPE_SERIAL);
					string2Serial(yaiCommand);
				}
			}
			return yaiCommand;
		}

		void string2Serial(YaiCommand &yaiCommand){
			yaiCommand.command = "";
			yaiCommand.execute = false;
			yaiCommand.type = String(YAI_COMMAND_TYPE_NONE);
			if(yaiCommand.message != ""){
				  String root[9];
				  if(yaiCommand.message.indexOf("RESULT") > 0){
					  yaiCommand.type = String(YAI_COMMAND_TYPE_RESULT);
				  }else{
					  getElementRoot(yaiCommand.message, root);
					  yaiCommand.type = root[0];
					  if(yaiCommand.type == String(YAI_COMMAND_TYPE_SERIAL) ||
							  yaiCommand.type == String(YAI_COMMAND_TYPE_SPI) ||
							  yaiCommand.type == String(YAI_COMMAND_TYPE_WIFI) ||
							  yaiCommand.type == String(YAI_COMMAND_TYPE_I2C))
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

		char *strSplit(char *str, const char *delim, char **save){
		    char *res, *last;

		    if( !save )
		        return strtok(str, delim);
		    if( !str && !(str = *save) )
		        return NULL;
		    last = str + strlen(str);
		    if( (*save = res = strtok(str, delim)) )
		    {
		        *save += strlen(res);
		        if( *save < last )
		            (*save)++;
		        else
		            *save = NULL;
		    }
		    return res;
		};

		void getElementRoot(String myString, String rootElement[]){
		  char copy[64];
		  myString.toCharArray(copy, 64);
		  char *p = copy;
		  char *str;

		  int i = 0;

		  while ((str = strSplit(p, ",", &p)) != NULL){
		    rootElement[i] = str;
		    i++;
		  }
		};
};

#endif


