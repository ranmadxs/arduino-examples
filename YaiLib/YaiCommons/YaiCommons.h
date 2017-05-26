#ifndef YaiCommons_h
#define YaiCommons_h

#include <Arduino.h>

//Enum Type
#define ROVER_TYPE_2WD                    		1001
#define SERVO_TYPE_SG90               	  		2001
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
#define SERVO_ACTION_CONTINUOUS	          		200001
#define SERVO_ACTION_ANGLE	        	  		200002
#define SERVO_STOP	  			      	  		200003
#define OBSTACLE_READER                    		300001

#define YAI_LOG_FOLDER							"/logs"

class YaiUtil{
	public:
		YaiUtil(){}

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


