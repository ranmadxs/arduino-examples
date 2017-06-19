/***********************************************************
Example 3: 4x4 keypad, write results on serial monitor
File version: 1.1
Update: fix for using CeezTouchScreen lib
Description: Open serial monitor to see result or incoming
             debug information
************************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <LGDP4535.h> // Hardware-specific library
#include <zTouchScreen.h>

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// If using the shield, all control and data lines are fixed
LGDP4535 tft;

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

// You need to calibrate to fit your LCD
#define TS_MINX 895
#define TS_MINY 941
#define TS_MAXX 180
#define TS_MAXY 180


// un-comment this line to enable debug information in serial port
//#define DEBUG

#define PENRADIUS 3
#define MINPRESSURE 10
#define MAXPRESSURE 1000
// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int matriz[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};


void setup(void) {
  
  // initiate these variable for calculation correct point 
  /*
    )ts.min_x = TS_MINX;
    ts.min_y = TS_MINY;
    ts.max_x = TS_MAXX;
    ts.max_y = TS_MAXY;
    ts.width = 240;
    ts.height = 320;
    ts.orientation = 2; // rotate 180 degree
   */
  ts.InitVariable(2, 240, 320, TS_MINX, TS_MAXX, TS_MINY, TS_MAXY);
  
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

  tft.reset();

  uint16_t identifier = tft.readID();
  Serial.print(F("LCD driver chip: "));
  Serial.println(identifier, HEX);
  if (identifier == 0x4535) 
    Serial.println(F("Using the library LGDP4535.\n\nPress the keypad to display number:"));
  else Serial.println(F("This is not the driver chip LGDP4535.\nForce using library LGDP4535..."));
  Serial.println();
  tft.begin();
  DibuRects(WHITE);
  DibuNums(RED);  
}

void loop(void) {
  // Recently Point was renamed TSPoint in the TouchScreen library
  // If you are using an older version of the library, use the
  // commented definition instead.
  // Point p = ts.getPoint();
  int x,y;
  static int anterior=0, actual;
  static unsigned long int tanterior=0, tactual=0;
  TSPoint p = ts.getPoint();
    // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
  #ifdef DEBUG  
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);
  #endif      

  x=(4*p.x)/tft.width();
  y=(4*p.y)/tft.height();
  
  #ifdef DEBUG
    Serial.print("("); Serial.print(p.x);
    Serial.print(", "); Serial.print(p.y);
    Serial.println(")");
    Serial.println(x);
    Serial.println(y);
  #endif

      actual=matriz[y][x];
      tactual=millis();
    if (tactual-tanterior>1000)
    {
      tanterior=tactual;
      anterior=0;
    }
    if (actual!=anterior )
    {
      Serial.println(actual);
      anterior=actual;
      #ifdef DEBUG  
      tft.fillCircle(p.x, p.y, PENRADIUS, BLUE);
      #endif
    }
  }
}
unsigned long DibuRects(uint16_t color) {

  int ancho,  alto, i, j;

  tft.fillScreen(BLACK);
  ancho= tft.width()/4;
  alto= tft.height()/4;

  for(i=0; i<4; i++)
    for(j=0; j<4; j++) {
    
    tft.drawRect(i*ancho, j*alto, ancho, alto, color);
  }


}

unsigned long DibuNums(uint16_t color)
{
  int ancho,  alto, i, j;
  ancho= tft.width()/4;
  alto= tft.height()/4;
  #if defined __AVR_ATmega2560__
  tft.setRotation(4);
  #endif
  for(i=0; i<4; i++)
    for(j=0; j<4; j++) {
      if((i+j*4+1)<=9)tft.setCursor(i*ancho+ancho/3, j*alto+alto/3);
      else tft.setCursor(i*ancho+ancho/10, j*alto+alto/3);
      tft.setTextColor(color);
      tft.setTextSize(4);
      tft.println(matriz[j][i]);
  }

}