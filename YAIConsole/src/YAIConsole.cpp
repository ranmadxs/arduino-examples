#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <LGDP4535.h>
#include <zTouchScreen.h>

// Change these to to fit your touchscreen
#define YP 15   // -> A1
#define XM 16   // -> A2
#define YM 7
#define XP 6

#define MINPRESSURE 10
#define MAXPRESSURE 1000

int TS_MINX = 0;
int TS_MINY = 0;
int TS_MAXX = 1023;
int TS_MAXY = 1023;

typedef struct {
  int x;
  int y;
} XY;

TouchScreen ts(XP, YP, XM, YM, 300);

#define		BLACK   	0x0000
#define		BLUE    	0x001F
#define		RED     	0xF800
#define		GREEN   	0x07E0
#define		CYAN    	0x07FF
#define		MAGENTA 	0xF81F
#define		YELLOW  	0xFFE0
#define		WHITE   	0xFFFF

LGDP4535 tft;



void setup() {
  Serial.begin(9600);
  tft.reset();
  tft.begin();
  
  ts.InitVariable(0, 240, 320, TS_MINX, TS_MAXX, TS_MINY, TS_MAXY, MINPRESSURE, MAXPRESSURE);
  //ts.SetPressure(0,1000);
  int w = tft.width();
  int h = tft.height();
  
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(0,h/2-30);
  tft.println("YaiConsole Ready ...");
}

void loop() {
	serialController();
}