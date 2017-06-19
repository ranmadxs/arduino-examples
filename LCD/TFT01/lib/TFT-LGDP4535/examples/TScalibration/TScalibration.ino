////////////////////////////////////////////////////////////////////
// Touch Screen Calibration
// Version 1.0
// Original work from NICK
// For TFT shield using LGDP4535
////////////////////////////////////////////////////////////////////

#include <Adafruit_GFX.h>
#include <LGDP4535.h>
#include <zTouchScreen.h>

// Change these to to fit your touchscreen
#define YP A1
#define XM A2
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

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

LGDP4535 tft;

void setup() {
  Serial.begin(9600);
  tft.reset();
  tft.begin();
  
  ts.InitVariable(0, 240, 320, TS_MINX, TS_MAXX, TS_MINY, TS_MAXY, MINPRESSURE, MAXPRESSURE);
  //ts.SetPressure(0,1000);
  int w = tft.width();
  int h = tft.height();
  
  //calibrate:
  tft.fillScreen(BLACK);
  
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(0,h/2-30);
  tft.println("Screen Calibration\n\nTap to Continue...");
  TSPoint point;
  
  point = ts.getNextRawPoint();
  
  tft.fillScreen(BLACK);
  tft.drawCircle(w/2,-10, 40,WHITE);
  tft.drawLine(w/2,0+45, w/2, h/4+45, GREEN);
  tft.drawLine(w/2-10,h/4-20+45, w/2, h/4+45, GREEN);
  tft.drawLine(w/2+10,h/4-20+45, w/2, h/4+45, GREEN);
  tft.setCursor(w/2-30,h/2-15);
  tft.print("Slide");
  point = ts.getNextRawPoint();  // get the TOP limit
  tft.fillScreen(WHITE);
  TS_MINY = point.y;
  
  delay(100);
  tft.fillScreen(BLACK);
  tft.drawCircle(w+10,h/2, 40,WHITE);
  tft.drawLine(w-55,h/2, w/2-40,h/2, GREEN);
  tft.drawLine(w/2+20, h/2-10, w/2-40, h/2, GREEN);
  tft.drawLine(w/2+20, h/2+10, w/2-40, h/2, GREEN);
  tft.setCursor(w/2-30,h/2+30);
  tft.print("Slide");
  point = ts.getNextRawPoint();  // get the RIGHT limit
  tft.fillScreen(WHITE);
  TS_MAXX = point.x;
  
  delay(100);
  tft.fillScreen(BLACK);
  tft.drawCircle(w/2,h+10, 40,WHITE);
  tft.drawLine(w/2,h-45, w/2, h-h/4-45, GREEN);
  tft.drawLine(w/2-10,h-h/4+20-45, w/2, h-h/4-45, GREEN);
  tft.drawLine(w/2+10,h-h/4+20-45, w/2, h-h/4-45, GREEN);  
  tft.setCursor(w/2-30,h/2);
  tft.print("Slide"); 
  point = ts.getNextRawPoint();   // get the BOTTOM limit
  tft.fillScreen(WHITE);
  TS_MAXY = point.y;
  
  delay(100);
  tft.fillScreen(BLACK);
  tft.drawCircle(-10,h/2, 40,WHITE);
  tft.drawLine(45,h/2, w/2+40,h/2, GREEN);
  tft.drawLine(w/2+20, h/2-10, w/2+40, h/2, GREEN);
  tft.drawLine(w/2+20, h/2+10, w/2+40, h/2, GREEN);
  tft.setCursor(w/2-30,h/2+30);
  tft.print("Slide");
  point = ts.getNextRawPoint();   // get the LEFT limit
  tft.fillScreen(WHITE);
  TS_MINX = point.x;
  
  delay(100);
  tft.fillScreen(BLACK);
  ts.SetMinMaxXY(TS_MINX,TS_MAXX,TS_MINY,TS_MAXY);

  tft.setTextSize(1);
  tft.setCursor(0,0);
  tft.println("Your ADC calibrations values are:");
  tft.print("TS_MINX = ");
  tft.println(TS_MINX);
  tft.print("TS_MINY = ");
  tft.println(TS_MINY);
  tft.print("TS_MAXX = ");
  tft.println(TS_MAXX);
  tft.print("TS_MAXY = ");
  tft.println(TS_MAXY);
  
  tft.println();
  tft.print("The orientation of the touch screen should be zero with these values\nTouch anywhere to test the screen. The coordinates will be in the upper left corner.");
}

void loop() {

  tft.setTextSize(2);
  tft.setCursor(tft.width()/2-40,tft.height()/2-10);
  tft.setTextColor(GREEN);
  TSPoint p = ts.getNextPoint();
  tft.fillScreen(BLACK);
  tft.print('(');tft.print(p.x);tft.print(',');
  tft.print(p.y);tft.print(')');
  tft.fillCircle(p.x,p.y,5,BLUE);
  delay(100);
}
