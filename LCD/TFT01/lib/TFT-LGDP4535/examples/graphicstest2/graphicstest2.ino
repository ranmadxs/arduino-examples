/******************************************************
Example 2: Draw Sine, Cosine, Tangent lines
******************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <LGDP4535.h> // Hardware-specific library

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

LGDP4535 tft;
// If using the shield, all control and data lines are fixed, and

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.print(F("LCD driver chip: "));
  Serial.println(identifier, HEX);
  if (identifier == 0x4535) 
    Serial.println(F("Using the library LGDP4535.\nRun the sample now"));
  else Serial.println(F("This is not the driver chip LGDP4535.\nForce using library LGDP4535..."));
  tft.begin();
  
  tft.setRotation(1);
  
  tft.fillScreen(BLACK);
  
  // Draw crosshairs
  //x-axis
  tft.drawLine(1,120,320,120,BLUE); 
  for (int i=10; i<320; i+=20)
    tft.drawLine(i, 115, i, 125,BLUE);

  //y-axis
  tft.drawLine(160,1,160,240,BLUE);
  for (int i=10; i<240; i+=20)
    tft.drawLine(155, i, 165, i,BLUE);
   
  tft.setTextWrap(false),
  tft.setTextSize(2);
  tft.setCursor(2,3);
  tft.setTextColor(MAGENTA);
  tft.print("LCD TEST - Sample 1");

  tft.setTextSize(1);
// Draw sin-, cos- and tan- lines  

  tft.setCursor(2,73);
  tft.setTextColor(CYAN);
  tft.print("Sine");
  double k=2.25;
  for (int i=1; i<320; i++)
  {
    tft.drawPixel(i,120+(sin(((i*k)*3.14)/180)*90),CYAN);
  }
  
  tft.setCursor(2,83);
  tft.setTextColor(RED);
  tft.print("Cosine");
  for (int i=1; i<320; i++)
  {
    tft.drawPixel(i,120+(cos(((i*k)*3.14)/180)*90),RED);
  }

  tft.setCursor(2,93);
  tft.setTextColor(YELLOW);
  tft.print("Tangent");
  for (int i=1; i<320; i++)
  {
    tft.drawPixel(i,120+(tan(((i*k)*3.14)/180)*20),YELLOW);
  }

  delay(2000);
  
}

void loop(void) {
  
}