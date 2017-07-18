#ifndef YaiLCD_h
#define YaiLCD_h

#include <Adafruit_GFX.h>
#include <LGDP4535.h>
//#include <zTouchScreen.h>

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

#define		BLACK   	0x0000
#define		BLUE    	0x001F
#define		RED     	0xF800
#define		GREEN   	0x07E0
#define		CYAN    	0x07FF
#define		MAGENTA 	0xF81F
#define		YELLOW  	0xFFE0
#define		WHITE   	0xFFFF

#include "YaiCommons.h"

//TouchScreen ts(XP, YP, XM, YM, 300);

class YaiLCD {
public:
	YaiLCD() {
		width = 0;
		height = 0;
		dy = 10;
		lastLines = 0;
	}

	void printCmd(YaiCommand yaiCommand) {
		int y0 = getCursorY(lastLines);
		lastLines = getMsgLines(yaiCommand.message);
		tft.setTextSize(1);
		tft.setCursor(0, y0);
		tft.println(yaiCommand.message);
	}

	int getMsgLines(String msg) {
		int lins = 1 + msg.length() / 41;
		//Serial.println(String(msg.length()) + "   ----   " + String(lins));
		return lins;
	}

	int getCursorY(int lines) {
		posY = posY + lines * dy;
		if (posY >= height) {
			init();
		}
		return posY;
	}

	int width;
	int height;

	void init() {
		tft.reset();
		tft.begin();
		lastLines = 0;
		//ts.InitVariable(0, 240, 320, TS_MINX, TS_MAXX, TS_MINY, TS_MAXY, MINPRESSURE, MAXPRESSURE);
		//ts.SetPressure(0,1000);
		width = tft.width();
		height = tft.height();
		//calibrate:
		tft.fillScreen(BLACK);
		tft.setTextColor(WHITE);
		tft.setTextSize(1);
		tft.setCursor(0, 0);

		tft.println("YaiConsole Ready ...");

		posY = height / 2 - 80;
		tft.drawLine(TS_MINX, posY - 1 , TS_MAXX, posY - 1, BLUE);
	}

private:
	int dy;
	int posY;
	int lastLines;
	LGDP4535 tft;

};

#endif
