/*********************************************************************
*
* LCD_ID_Reader
*
* This sketch is meant only to attempt to read the driver ID code
* from inexpensive touchscreen LCDs found on eBay without needing to
* load any additional libraries.  The hope is to identify the most 
* common varieties and choose the best library for the screen you have.
*
* This has been successfully tested so far on 992X and 778X variety
* screens.
*
* Usage: 
*
* Compile the sketch and run it on your board with the screen
* attached.  In the serial monitor, you should see a message containing
* the driver code.  The tricky thing is that if it does not work, the
* results may be undetermined.  However, if we can compile a list,
* the difference between working and not may become more evident.
*
* Please visit http://misc.ws/lcd_information for more information.
*
* Version 1.2 - January 29th, 2015
* 
*********************************************************************/

#include <Arduino.h>

/*********************************************************************
*
* PIN ASSIGNMENTS
*
* You can alter the pin assignments to reflect any configuration you
* wish.  I've provided the default shield configuration, which works
* on both the Arduino UNO and Mega 2560.
* 
*********************************************************************/
//-- Arduino UNO or Mega 2560 Plugged as shield
#define LCD_RST A4
#define LCD_CS A3
#define LCD_RS A2
#define LCD_WR A1
#define LCD_RD A0

#define LCD_D0 8
#define LCD_D1 9
#define LCD_D2 2
#define LCD_D3 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7



/*********************************************************************
*
* Attempt to initialize and reset LCD, then read its Driver Code
* at register index 0.
* 
*********************************************************************/

void lcdWrite8(uint16_t data) {
  digitalWrite(LCD_D0, data & 1);
  digitalWrite(LCD_D1, (data & 2) >> 1);
  digitalWrite(LCD_D2, (data & 4) >> 2);
  digitalWrite(LCD_D3, (data & 8) >> 3);
  digitalWrite(LCD_D4, (data & 16) >> 4); 
  digitalWrite(LCD_D5, (data & 32) >> 5);
  digitalWrite(LCD_D6, (data & 64) >> 6);
  digitalWrite(LCD_D7, (data & 128) >> 7);  
}

uint16_t lcdRead8() {
  uint16_t result = digitalRead(LCD_D7);
  result <<= 1;
  result |= digitalRead(LCD_D6);
  result <<= 1;
  result |= digitalRead(LCD_D5);
  result <<= 1; 
  result |= digitalRead(LCD_D4); 
  result <<= 1;
  result |= digitalRead(LCD_D3);
  result <<= 1;
  result |= digitalRead(LCD_D2); 
  result <<= 1;
  result |= digitalRead(LCD_D1);
  result <<= 1;
  result |= digitalRead(LCD_D0); 
  
  return result;
}

void lcdSetWriteDir() {
  pinMode(LCD_D0, OUTPUT);
  pinMode(LCD_D1, OUTPUT);
  pinMode(LCD_D2, OUTPUT);
  pinMode(LCD_D3, OUTPUT);  
  pinMode(LCD_D4, OUTPUT);  
  pinMode(LCD_D5, OUTPUT);
  pinMode(LCD_D6, OUTPUT);
  pinMode(LCD_D7, OUTPUT);  
}


void lcdSetReadDir() {
  pinMode(LCD_D0, INPUT);
  pinMode(LCD_D1, INPUT);
  pinMode(LCD_D2, INPUT);
  pinMode(LCD_D3, INPUT);  
  pinMode(LCD_D4, INPUT);  
  pinMode(LCD_D5, INPUT);
  pinMode(LCD_D6, INPUT);
  pinMode(LCD_D7, INPUT);    
}

void lcdWriteData(uint16_t data) {
  
  lcdSetWriteDir();
  digitalWrite(LCD_CS, LOW);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_WR, HIGH);
  
  lcdWrite8(data >> 8);
  
  digitalWrite(LCD_WR, LOW);
  delayMicroseconds(10);
  digitalWrite(LCD_WR, HIGH);
  
  lcdWrite8(data);
  
  digitalWrite(LCD_WR, LOW);
  delayMicroseconds(10);
  digitalWrite(LCD_WR, HIGH);
  
  digitalWrite(LCD_CS, HIGH);  
}


void lcdWriteCommand(uint16_t command) {
  lcdSetWriteDir(); 
  digitalWrite(LCD_CS, LOW);
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_WR, HIGH);  
  lcdWrite8(command >> 8);
  digitalWrite(LCD_WR, LOW);
  delayMicroseconds(10);
  digitalWrite(LCD_WR, HIGH);
  lcdWrite8(command);
  digitalWrite(LCD_WR, LOW);
  delayMicroseconds(10);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_CS, HIGH);    
}

void lcdWriteRegister(uint16_t addr, uint16_t data) {
  lcdWriteCommand(addr);
  lcdWriteData(data);
}

int lcdReadData() {
  uint16_t result;
  lcdSetReadDir();
  digitalWrite(LCD_CS, LOW);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_WR, HIGH);
  
  digitalWrite(LCD_RD, LOW);  
  delayMicroseconds(10);
  result = lcdRead8() << 8;
  digitalWrite(LCD_RD, HIGH);
  
  delayMicroseconds(10);
  
  digitalWrite(LCD_RD, LOW);
  delayMicroseconds(10);
  result |= lcdRead8();
  
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_CS, HIGH);
  
  return result;
}

uint16_t lcdReadRegister(uint16_t reg) {
  lcdWriteCommand(reg);
  return lcdReadData();
}

void print_all_regs() {
  char str[60];
  uint16_t i, val;

  for(i=0; i < 256; i++ )
  {
    delay(40);
    val = lcdReadRegister(i);
    sprintf(str, "Register 0x%0.2X : 0x%0.4X", i, val);
    Serial.println( str );
  }  
}

/*********************************************************************
*
*   LCD Functions - Inefficient but should be good enough 
*                   to read the ID.
*
*********************************************************************/
void lcdRegister0154() {
  lcdWriteRegister(0x000C, 0x130); 
  lcdWriteRegister(0x0080, 0x8d);
  lcdWriteRegister(0x0092, 0x10);
  lcdWriteRegister(0x0011, 0x1b);
  lcdWriteRegister(0x0012, 0x3101);
  lcdWriteRegister(0x0013, 0x105f);
  lcdWriteRegister(0x0014, 0x667f);
  lcdWriteRegister(0x0010, 0x800);
  delay(20); 
  lcdWriteRegister(0x0011, 0x11b);
  delay(20); 
  lcdWriteRegister(0x0011, 0x31b);
  delay(20); 
  lcdWriteRegister(0x0011, 0x71b);
  delay(20); 
  lcdWriteRegister(0x0011, 0xf1b);
  delay(20); 
  lcdWriteRegister(0x0011, 0xf3b);
  delay(30); 
  lcdWriteRegister(0x0001, 0x2128);
  lcdWriteRegister(0x0002, 0x100);
  lcdWriteRegister(0x0003, 0x1030);
  lcdWriteRegister(0x0007, 0); 
  lcdWriteRegister(0x0008, 0x808);
  lcdWriteRegister(0x000B, 0x1100);
  lcdWriteRegister(0x000F, 0xf01);
  lcdWriteRegister(0x0015, 0);
  lcdWriteRegister(0x0030, 0);
  lcdWriteRegister(0x0034, 319); 
  lcdWriteRegister(0x0035, 0); 
  lcdWriteRegister(0x0036, 239); 
  lcdWriteRegister(0x0037, 0); 
  lcdWriteRegister(0x0038, 319); 
  lcdWriteRegister(0x0039, 0); 
  lcdWriteRegister(0x0050, 0);
  lcdWriteRegister(0x0051, 0xf00);
  lcdWriteRegister(0x0052, 0xa03);
  lcdWriteRegister(0x0053, 0x300);
  lcdWriteRegister(0x0054, 0xc05);
  lcdWriteRegister(0x0055, 0xf00);
  lcdWriteRegister(0x0056, 0xf00);
  lcdWriteRegister(0x0057, 3);
  lcdWriteRegister(0x0058, 0x1f07);
  lcdWriteRegister(0x0059, 0x71f);
  delay(20);
  lcdWriteRegister(0x0007, 0x12);
  delay(20);
  lcdWriteRegister(0x0007, 0x13);
}

void lcdRegisterOther() {
  Serial.println("Loading LCD registers...");
  lcdWriteRegister(0x00e5,0x8000);
  lcdWriteRegister(0x0000,0x0001);
  lcdWriteRegister(0x0001,0x0100);
  lcdWriteRegister(0x0002,0x0700);
  lcdWriteRegister(0x0003,0x1030);
  lcdWriteRegister(0x0004,0x0000);
  lcdWriteRegister(0x0008,0x0202);
  lcdWriteRegister(0x0009,0x0000);
  lcdWriteRegister(0x000a,0x0000);
  lcdWriteRegister(0x000c,0x0000);
  lcdWriteRegister(0x000d,0x0000);
  lcdWriteRegister(0x000f,0x0000);
  lcdWriteRegister(0x0010,0x0000);
  lcdWriteRegister(0x0011,0x0000);
  lcdWriteRegister(0x0012,0x0000);
  lcdWriteRegister(0x0013,0x0000);
  lcdWriteRegister(0x0010,0x17b0);
  lcdWriteRegister(0x0011,0x0037);
  lcdWriteRegister(0x0012,0x0138);
  lcdWriteRegister(0x0013,0x1700);
  lcdWriteRegister(0x0029,0x000d);
  lcdWriteRegister(0x0020,0x0000);
  lcdWriteRegister(0x0021,0x0000);
  lcdWriteRegister(0x0030,0x0001);
  lcdWriteRegister(0x0031,0x0606);
  lcdWriteRegister(0x0032,0x0304);
  lcdWriteRegister(0x0033,0x0202);
  lcdWriteRegister(0x0034,0x0202);
  lcdWriteRegister(0x0035,0x0103);
  lcdWriteRegister(0x0036,0x011d);
  lcdWriteRegister(0x0037,0x0404);
  lcdWriteRegister(0x0038,0x0404);
  lcdWriteRegister(0x0039,0x0404);
  lcdWriteRegister(0x003c,0x0700);
  lcdWriteRegister(0x003d,0x0a1f);
  lcdWriteRegister(0x0050,0x0000);
  lcdWriteRegister(0x0051,0x00ef);
  lcdWriteRegister(0x0052,0x0000);
  lcdWriteRegister(0x0053,0x013f);
  lcdWriteRegister(0x0060,0x2700);
  lcdWriteRegister(0x0061,0x0001);
  lcdWriteRegister(0x006a,0x0000);
  lcdWriteRegister(0x0090,0x0010);
  lcdWriteRegister(0x0092,0x0000);
  lcdWriteRegister(0x0093,0x0003);
  lcdWriteRegister(0x0095,0x0101);
  lcdWriteRegister(0x0097,0x0000);
  lcdWriteRegister(0x0098,0x0000);
  lcdWriteRegister(0x0007,0x0021);
  lcdWriteRegister(0x0007,0x0031);
  lcdWriteRegister(0x0007,0x0173);
}

void lcdRegister7783() {
    
  lcdWriteRegister(0x0001,0x0100);    
  lcdWriteRegister(0x0002,0x0700);    
  lcdWriteRegister(0x0003,0x1030);    
  lcdWriteRegister(0x0008,0x0302);    
  lcdWriteRegister(0x0009,0x0000);   
  lcdWriteRegister(0x000A,0x0008);    
  lcdWriteRegister(0x0010,0x0790);    
  lcdWriteRegister(0x0011,0x0005);    
  lcdWriteRegister(0x0012,0x0000);   
  lcdWriteRegister(0x0013,0x0000); 
  lcdWriteRegister(0x0010,0x12B0);    
  lcdWriteRegister(0x0011,0x0007);  
  lcdWriteRegister(0x0012,0x008C);   
  lcdWriteRegister(0x0013,0x1700);    
  lcdWriteRegister(0x0029,0x0022);    
  lcdWriteRegister(0x0030,0x0000);    
  lcdWriteRegister(0x0031,0x0505);    
  lcdWriteRegister(0x0032,0x0205);    
  lcdWriteRegister(0x0035,0x0206);    
  lcdWriteRegister(0x0036,0x0408);    
  lcdWriteRegister(0x0037,0x0000);   
  lcdWriteRegister(0x0038,0x0504);
  lcdWriteRegister(0x0039,0x0206);    
  lcdWriteRegister(0x003C,0x0206);   
  lcdWriteRegister(0x003D,0x0408);    
  lcdWriteRegister(0x0050,0x0000);
  lcdWriteRegister(0x0051,0x00EF);   
  lcdWriteRegister(0x0052,0x0000);   
  lcdWriteRegister(0x0053,0x013F);   
  lcdWriteRegister(0x0060,0xA700);   
  lcdWriteRegister(0x0061,0x0001);   
  lcdWriteRegister(0x0090,0x0033); 
  lcdWriteRegister(0x0007,0x0133);
  lcdWriteRegister(0x0001,0x0100);
  lcdWriteRegister(0x0002,0x0700);    
  lcdWriteRegister(0x0003,0x1030);    
  lcdWriteRegister(0x0008,0x0302);    
  lcdWriteRegister(0x0009,0x0000);   
  lcdWriteRegister(0x000A,0x0008);    
  lcdWriteRegister(0x0010,0x0790);    
  lcdWriteRegister(0x0011,0x0005);    
  lcdWriteRegister(0x0012,0x0000);  
  lcdWriteRegister(0x0013,0x0000);    
  lcdWriteRegister(0x0010,0x12B0);    
  lcdWriteRegister(0x0011,0x0007);    
  lcdWriteRegister(0x0012,0x008C);    
  lcdWriteRegister(0x0013,0x1700);    
  lcdWriteRegister(0x0029,0x0022);    
  lcdWriteRegister(0x0030,0x0000);    
  lcdWriteRegister(0x0031,0x0505);    
  lcdWriteRegister(0x0032,0x0205);    
  lcdWriteRegister(0x0035,0x0206);    
  lcdWriteRegister(0x0036,0x0408);   
  lcdWriteRegister(0x0037,0x0000);    
  lcdWriteRegister(0x0038,0x0504);
  lcdWriteRegister(0x0039,0x0206);    
  lcdWriteRegister(0x003C,0x0206);    
  lcdWriteRegister(0x003D,0x0408);   
  lcdWriteRegister(0x0050,0x0000);
  lcdWriteRegister(0x0051,0x00EF);   
  lcdWriteRegister(0x0052,0x0000);   
  lcdWriteRegister(0x0053,0x013F);   
  lcdWriteRegister(0x0060,0xA700);   
  lcdWriteRegister(0x0061,0x0001);   
  lcdWriteRegister(0x0090,0x0033);
  lcdWriteRegister(0x0007,0x0133);
}

void lcdInit() {
  pinMode(LCD_CS, OUTPUT);
  digitalWrite(LCD_CS, HIGH);
  pinMode(LCD_RS, OUTPUT);
  digitalWrite(LCD_RS, HIGH);
  pinMode(LCD_WR, OUTPUT);
  digitalWrite(LCD_WR, HIGH);
  pinMode(LCD_RD, OUTPUT);
  digitalWrite(LCD_RD, HIGH);
  pinMode(LCD_RST, OUTPUT);
  digitalWrite(LCD_RST, HIGH);  
}

void lcdReset() {
  digitalWrite(LCD_RST, LOW);
  delay(2); 
  digitalWrite(LCD_RST, HIGH);
  lcdWriteData(0);
  lcdWriteData(0);
  lcdWriteData(0);
  lcdWriteData(0);
}


uint16_t lcdReadID() {
  return lcdReadRegister(0x00);
}


void lcdFillScreen(uint16_t color) {
  
  Serial.println("Filling the screen...");
  
  /*lcdWriteRegister(0x0050, 0);
  lcdWriteRegister(0x0051, 219);  
  lcdWriteRegister(0x0052, 0);
  lcdWriteRegister(0x0053, 319);  
  */
  lcdWriteRegister(0x0020, 0);
  lcdWriteRegister(0x0021, 0);
  lcdWriteCommand(0x0022);
  
  digitalWrite(LCD_CS, LOW);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_WR, HIGH);
 
  lcdSetWriteDir();
  
  uint32_t i = 320;
  i *=240;

  while( i-- ) {
    lcdWrite8(color >> 8);
    digitalWrite(LCD_WR, LOW);
    delayMicroseconds(10);
    digitalWrite(LCD_WR, HIGH); 
    lcdWrite8(color);
    digitalWrite(LCD_WR, LOW);
    delayMicroseconds(10);
    digitalWrite(LCD_WR, HIGH); 
  }
  
  digitalWrite(LCD_CS, HIGH); 
  Serial.println("Done filling...");
  
}

void setup() {
  
  char hexString[7];
  uint16_t id;
  
  Serial.begin(9600);
  Serial.println("Initializing LCD...");
  lcdInit();
  lcdReset();
  
  delay(500);
  
  Serial.print("Reading ID...");
  id = lcdReadID();
  sprintf(hexString, "0x%0.4X", id); 
  Serial.println( hexString );
  
  if( id == 0x7783 ) {
    lcdRegister7783();
    lcdFillScreen(0xF800);
    Serial.println("If your screen filled red, then you may be able to use the library at https://github.com/Smoke-And-Wires/TFT-Shield-Example-Code");
  } else if( id == 0x0154 ) {
    lcdRegister0154();
    lcdFillScreen(0xF800);
    Serial.println("If your screen filled red, please report it at http://misc.ws/lcd_information");
    Serial.println("There is currently no known working library.");
  } else {
    lcdRegisterOther();
    lcdFillScreen(0xF800);
    Serial.println("If your screen filled red, you may be able to use the library at http://misc.ws");
  } 
  
  //print_all_regs();
}

void loop() {
  
}