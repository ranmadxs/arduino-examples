/*******************************************************
 This Library for LGDP4535 240x320 TFT controller driver
 Rewrote from adafruit TFT library
 For original code / licensing please refer to
 https://github.com/adafruit/TFTLCD-Library
*******************************************************/
#include <avr/pgmspace.h>

#include "pins_arduino.h"
#include "wiring_private.h"
#include "LGDP4535.h"

// Use the include which corresponde to your arduino
//#include "mega_24_shield.h"
#include "uno_24_shield.h"

#define TFTWIDTH   240
#define TFTHEIGHT  320

// Constructor for breakout board (configurable LCD control lines).
// Can still use this w/shield, but parameters are ignored.
LGDP4535::LGDP4535() :  Adafruit_GFX(TFTWIDTH, TFTHEIGHT) {

	// Convert pin numbers to registers and bitmasks
	_reset     = LCD_RESET;
 
    csPort     = portOutputRegister(digitalPinToPort(LCD_CS));
    cdPort     = portOutputRegister(digitalPinToPort(LCD_CD));
    wrPort     = portOutputRegister(digitalPinToPort(LCD_WR));
    rdPort     = portOutputRegister(digitalPinToPort(LCD_RD));

	csPinSet   = digitalPinToBitMask(LCD_CS);
	cdPinSet   = digitalPinToBitMask(LCD_CD);
	wrPinSet   = digitalPinToBitMask(LCD_WR);
	rdPinSet   = digitalPinToBitMask(LCD_RD);
	csPinUnset = ~csPinSet;
	cdPinUnset = ~cdPinSet;
	wrPinUnset = ~wrPinSet;
	rdPinUnset = ~rdPinSet;

	*csPort   |=  csPinSet; // Set all control bits to HIGH (idle)
	*cdPort   |=  cdPinSet; // Signals are ACTIVE LOW
	*wrPort   |=  wrPinSet;
	*rdPort   |=  rdPinSet;
 
	pinMode(LCD_CS, OUTPUT);    // Enable outputs
	pinMode(LCD_CD, OUTPUT);
	pinMode(LCD_WR, OUTPUT);
	pinMode(LCD_RD, OUTPUT);
//  if (reset) {
    digitalWrite(LCD_RESET, HIGH);
    pinMode(LCD_RESET, OUTPUT);
 // }
	init();
}

void LGDP4535::init(void) {
  
	setWriteDir(); // Set up LCD data port(s) for WRITE operations
	rotation  = 0; 
	cursor_y  = cursor_x = 0;
	textsize  = 1;
	textcolor = 0xFFFF;
	_width    = TFTWIDTH;
	_height   = TFTHEIGHT;
}

// // Initialization command table for LCD controller
#define TFTLCD_DELAY 0xFF

static const uint16_t LGPD4535_regValues[] PROGMEM = {
  
      0x15, 0x0030,     // Set the internal vcore voltage                                               
	  0x9A, 0x0010,     // Start internal OSC 
      0x11, 0x0020,        // set SS and SM bit 
      0x10, 0x3428,        // set 1 line inversion 
      0x12, 0x0002,        // set GRAM write direction and BGR=1  
      0x13, 0x1038,        // Resize register 
      TFTLCD_DELAY, 40, 
      0x12, 0x0012,        // set the back porch and front porch 
      TFTLCD_DELAY, 40, 
      0x10, 0x3420,        // set non-display area refresh cycle ISC[3:0] 
      0x13, 0x3045,        // FMARK function 
      TFTLCD_DELAY, 70, 
      0x30, 0x0000,      // RGB interface setting 
      0x31, 0x0402,        // Frame marker Position 
      0x32, 0x0307,      // RGB interface polarity 
      0x33, 0x0304,      // SAP, BT[3:0], AP, DSTB, SLP, STB 
      0x34, 0x0004,      // DC1[2:0], DC0[2:0], VC[2:0] 
      0x35, 0x0401,      // VREG1OUT voltage 
      0x36, 0x0707,      // VDV[4:0] for VCOM amplitude 
      0x37, 0x0305,      // SAP, BT[3:0], AP, DSTB, SLP, STB 
      0x38, 0x0610,      // DC1[2:0], DC0[2:0], VC[2:0] 
      0x39, 0x0610,      // VREG1OUT voltage 
      0x01, 0x0100,      // VDV[4:0] for VCOM amplitude 
      0x02, 0x0300,      // VCM[4:0] for VCOMH 
      0x03, 0x1030,      // GRAM horizontal Address 
      0x08, 0x0808,      // GRAM Vertical Address 
      0x0A, 0x0008,      
      0x60, 0x2700,        // Gate Scan Line 
      0x61, 0x0001,        // NDL,VLE, REV 
      0x90, 0x013E,
      0x92, 0x0100,
      0x93, 0x0100,
      0xA0, 0x3000,
      0xA3, 0x0010,
      0x07, 0x0001,
      0x07, 0x0021,
      0x07, 0x0023,
      0x07, 0x0033,
      0x07, 0x0133,
};

void LGDP4535::begin(uint16_t id) {
	uint8_t i = 0;
    uint16_t a, d;
	reset();
    CS_ACTIVE;
    while(i < sizeof(LGPD4535_regValues) / sizeof(uint16_t)) {
		a = pgm_read_word(&LGPD4535_regValues[i++]);
		d = pgm_read_word(&LGPD4535_regValues[i++]);
		if (a == TFTLCD_DELAY) delay(d);
		else writeRegister16(a, d);
    }
    setRotation(rotation);
    setAddrWindow(0, 0, TFTWIDTH-1, TFTHEIGHT-1);
}

void LGDP4535::reset(void) {
  
	CS_IDLE;
//	CD_DATA;
	WR_IDLE;
	RD_IDLE;

	if (_reset) {
		digitalWrite(_reset, LOW);
		delay(2);
		digitalWrite(_reset, HIGH);
	}

	// Data transfer sync
	CS_ACTIVE;
	CD_COMMAND;
	write8(0x00);
	for (uint8_t i=0; i<3; i++) WR_STROBE; // Three extra 0x00s
	CS_IDLE;
}

void LGDP4535::setAddrWindow(int x1, int y1, int x2, int y2) {

	CS_ACTIVE;
	
	int x, y, t;
	switch(rotation) {
		default:
			x  = x1;
			y  = y1;
			break;
		case 1:
			t  = y1;
			y1 = x1;
			x1 = TFTWIDTH  - 1 - y2;
			y2 = x2;
			x2 = TFTWIDTH  - 1 - t;
			x  = x2;
			y  = y1;
			break;
		case 2:
			t  = x1;
			x1 = TFTWIDTH  - 1 - x2;
			x2 = TFTWIDTH  - 1 - t;
			t  = y1;
			y1 = TFTHEIGHT - 1 - y2;
			y2 = TFTHEIGHT - 1 - t;
			x  = x2;
			y  = y2;
			break;
		case 3:
			t  = x1;
			x1 = y1;
			y1 = TFTHEIGHT - 1 - x2;
			x2 = y2;
			y2 = TFTHEIGHT - 1 - t;
			x  = x1;
			y  = y2;
			break;
	}
	
	writeRegister16(0x0050, x1); // Set address window
	writeRegister16(0x0051, x2);
	writeRegister16(0x0052, y1);
	writeRegister16(0x0053, y2);
	writeRegister16(0x0020, x ); // Set address counter to top left
	writeRegister16(0x0021, y );

	CS_IDLE;
}

void LGDP4535::setLR(void) {
  CS_ACTIVE;
  CS_IDLE;
}

void LGDP4535::flood(uint16_t color, uint32_t len) {
	uint16_t blocks;
	uint8_t i, hi = color >> 8, lo = color;

	CS_ACTIVE;
	CD_COMMAND;
	
	write8(0x00); // High byte of GRAM register...
	write8(0x22); // Write data to GRAM

	// Write first pixel normally, decrement counter by 1
	CD_DATA;
	write8(hi);
	write8(lo);
	len--;
	
	blocks = (uint16_t)(len / 64); // 64 pixels/block
	if (hi == lo) {
		// High and low bytes are identical.  Leave prior data
		// on the port(s) and just toggle the write strobe.
		while(blocks--) {
			i = 16; // 64 pixels/block / 4 pixels/pass
			do {
				WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // 2 bytes/pixel
				WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // x 4 pixels
			} while(--i);
		}
		// Fill any remaining pixels (1 to 64)
		for (i = (uint8_t)len & 63; i--; ) {
		  WR_STROBE;
		  WR_STROBE;
		}
	} else {
		while(blocks--) {
			i = 16; // 64 pixels/block / 4 pixels/pass
			do {
				write8(hi); write8(lo); write8(hi); write8(lo);
				write8(hi); write8(lo); write8(hi); write8(lo);
			} while(--i);
		}
		for (i = (uint8_t)len & 63; i--; ) {
			write8(hi);
			write8(lo);
		}
	}
	
	CS_IDLE;
}

void LGDP4535::drawFastHLine(int16_t x, int16_t y, int16_t length, uint16_t color) {
  
	int16_t x2;

	// Initial off-screen clipping
	if ((length <= 0) || (y < 0) || (y >= _height) || (x >= _width) || ((x2 = (x + length - 1)) < 0)) return;

	if (x < 0) {        // Clip left
		length += x;
		x       = 0;
	}

	if (x2 >= _width) { // Clip right
		x2      = _width - 1;
		length  = x2 - x + 1;
	}

	setAddrWindow(x, y, x2, y);
	flood(color, length);
	setAddrWindow(0, 0, _width - 1, _height - 1);
}

void LGDP4535::drawFastVLine(int16_t x, int16_t y, int16_t length, uint16_t color) {
	int16_t y2;

	// Initial off-screen clipping
	if ((length <= 0 ) || (x < 0 ) || (x >= _width) || (y >= _height) || ((y2 = (y+length-1)) < 0)) return;
	
	if (y < 0) {         // Clip top
		length += y;
		y       = 0;
	}
	
	if (y2 >= _height) { // Clip bottom
		y2      = _height - 1;
		length  = y2 - y + 1;
	}

	setAddrWindow(x, y, x, y2);
	flood(color, length);
	setAddrWindow(0, 0, _width - 1, _height - 1);
}

void LGDP4535::fillRect(int16_t x1, int16_t y1, int16_t w, int16_t h, uint16_t fillcolor) {
	
	int16_t  x2, y2;

	// Initial off-screen clipping
	if ( (w <= 0) || (h <= 0) || (x1 >= _width) || (y1 >= _height) || ((x2 = x1+w-1) < 0) || ((y2 = y1+h-1) < 0 )) return;
	
	if (x1 < 0) { // Clip left
		w += x1;
		x1 = 0;
	}
	
	if (y1 < 0) { // Clip top
		h += y1;
		y1 = 0;
	}
	
	if (x2 >= _width) { // Clip right
		x2 = _width - 1;
		w  = x2 - x1 + 1;
	}
	
	if (y2 >= _height) { // Clip bottom
		y2 = _height - 1;
		h  = y2 - y1 + 1;
	}

	setAddrWindow(x1, y1, x2, y2);
	flood(fillcolor, (uint32_t)w * (uint32_t)h);
	setAddrWindow(0, 0, _width - 1, _height - 1);
}

void LGDP4535::fillScreen(uint16_t color) {

    uint16_t x, y;
    switch(rotation) {
		default: x = 0            ; y = 0            ; break;
		case 1 : x = TFTWIDTH  - 1; y = 0            ; break;
		case 2 : x = TFTWIDTH  - 1; y = TFTHEIGHT - 1; break;
		case 3 : x = 0            ; y = TFTHEIGHT - 1; break;
    }

    CS_ACTIVE;
    
	writeRegister16(0x0020, x);
    writeRegister16(0x0021, y);
	flood(color, (long)TFTWIDTH * (long)TFTHEIGHT);
}

void LGDP4535::drawPixel(int16_t x, int16_t y, uint16_t color) {

	// Clip
	if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return;

	CS_ACTIVE;

	int16_t t;
	switch(rotation) {
		case 1:
			t = x;
			x = TFTWIDTH  - 1 - y;
			y = t;
			break;
		case 2:
			x = TFTWIDTH  - 1 - x;
			y = TFTHEIGHT - 1 - y;
			break;
		case 3:
			t = x;
			x = y;
			y = TFTHEIGHT - 1 - t;
			break;
	}
	
	writeRegister16(0x0020, x);
	writeRegister16(0x0021, y);
	writeRegister16(0x0022, color );

	CS_IDLE;
}

// Issues 'raw' an array of 16-bit color values to the LCD; used
// externally by BMP examples.  Assumes that setWindowAddr() has
// previously been set to define the bounds.  Max 255 pixels at
// a time (BMP examples read in small chunks due to limited RAM).
void LGDP4535::pushColors(uint16_t *data, uint8_t len, boolean first) {

	uint16_t color;
	uint8_t  hi, lo;
	
	CS_ACTIVE;
	
	if (first == true) { // Issue GRAM write command only on first call
		CD_COMMAND;
		write8(0x00);
		write8(0x22);
	}
	
	CD_DATA;
	
	while(len--) {
		color = *data++;
		hi    = color >> 8; // Don't simplify or merge these
		lo    = color;      // lines, there's macro shenanigans
		write8(hi);         // going on.
		write8(lo);
	}
	
	CS_IDLE;
}

void LGDP4535::setRotation(uint8_t x) {

	// Call parent rotation func first -- sets up rotation flags, etc.
	Adafruit_GFX::setRotation(x);
	// Then perform hardware-specific rotation operations...

	CS_ACTIVE;
	
	//   uint16_t t;
	//   switch(rotation) {
	//    default: t = 0x1030; break;
	//    case 1 : t = 0x1028; break;
	//    case 2 : t = 0x1000; break;
	//    case 3 : t = 0x1018; break;
	//   }
	//   writeRegister16(0x0003, t ); // MADCTL
	//    For 932X, init default full-screen address window:
	//   setAddrWindow(0, 0, _width - 1, _height - 1); // CS_IDLE happens here
}

#ifdef read8isFunctionalized
  #define read8(x) x=read8fn()
#endif

// Because this function is used infrequently, it configures the ports for
// the read operation, reads the data, then restores the ports to the write
// configuration.  Write operations happen a LOT, so it's advantageous to
// leave the ports in that state as a default.
uint16_t LGDP4535::readPixel(int16_t x, int16_t y) {

	if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return 0;

	CS_ACTIVE;

	uint8_t hi, lo;
	int16_t t;
	
	switch(rotation) {
		case 1:
			t = x;
			x = TFTWIDTH  - 1 - y;
			y = t;
			break;
		case 2:
			x = TFTWIDTH  - 1 - x;
			y = TFTHEIGHT - 1 - y;
			break;
		case 3:
			t = x;
			x = y;
			y = TFTHEIGHT - 1 - t;
			break;
	}
	
	writeRegister16(0x0020, x);
	writeRegister16(0x0021, y);
	
	// Inexplicable thing: sometimes pixel read has high/low bytes
	// reversed.  A second read fixes this.  Unsure of reason.  Have
	// tried adjusting timing in read8() etc. to no avail.
	
	for (uint8_t pass=0; pass<2; pass++) {
		CD_COMMAND; write8(0x00); write8(0x22); // Read data from GRAM
		CD_DATA;
		setReadDir();  // Set up LCD data port(s) for READ operations
		read8(hi);     // First 2 bytes back are a dummy read
		read8(hi);
		read8(hi);     // Bytes 3, 4 are actual pixel value
		read8(lo);
		setWriteDir(); // Restore LCD data port(s) to WRITE configuration
	}

	CS_IDLE;

	return ((uint16_t)hi << 8) | lo;
}

// Ditto with the read/write port directions, as above.
uint16_t LGDP4535::readID(void) {

	uint8_t hi, lo;

	CS_ACTIVE;
	CD_COMMAND;
	
	write8(0x00);
	WR_STROBE;     // Repeat prior byte (0x00)
	setReadDir();  // Set up LCD data port(s) for READ operations
	CD_DATA;
	read8(hi);
	read8(lo);
	setWriteDir();  // Restore LCD data port(s) to WRITE configuration
	
	CS_IDLE;

	return (hi << 8) | lo;
}

// Pass 8-bit (each) R,G,B, get back 16-bit packed color
uint16_t LGDP4535::color565(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void LGDP4535::writeA16B3(uint16_t address, uint8_t ub, uint8_t mb, uint8_t lb){
	uint8_t hi , lo;
	
	CS_ACTIVE;
	
	hi = (address) >> 8; lo = (address);
	CD_COMMAND;
	write8(hi);
	write8(lo);
	
	CD_DATA;
	
	write8(ub);
	write8(ub);
	write8(mb);
	write8(mb);
	write8(lb);
	write8(lb);
}

void LGDP4535::drawLine3Byte(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t r, uint8_t g, uint8_t b) {
 
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) ystep = 1;
	else ystep = -1;

	for (; x0<=x1; x0++) {
		if (steep) drawPixel3(y0, x0, r, g, b);
		else drawPixel3(x0, y0, r, g, b);
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void LGDP4535::drawPixel3(int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b) {

	if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return;

	CS_ACTIVE;
 
    int16_t t;
    switch(rotation) {
		case 1:
			t = x;
			x = TFTWIDTH  - 1 - y;
			y = t;
			break;
		case 2:
			x = TFTWIDTH  - 1 - x;
			y = TFTHEIGHT - 1 - y;
			break;
		case 3:
			t = x;
			x = y;
			y = TFTHEIGHT - 1 - t;
			break;
    }
	
    writeRegister16(0x0020, x);
    writeRegister16(0x0021, y);
    writeA16B3(0x0022, r , g, b);
	
	CS_IDLE;
}


// For I/O macros that were left undefined, declare function
// versions that reference the inline macros just once:

#ifndef write8
void LGDP4535::write8(uint8_t value) {
	write8inline(value);
}
#endif

#ifdef read8isFunctionalized
uint8_t LGDP4535::read8fn(void) {
	uint8_t result;
	read8inline(result);
	return result;
}
#endif

#ifndef setWriteDir
void LGDP4535::setWriteDir(void) {
	setWriteDirInline();
}
#endif

#ifndef setReadDir
void LGDP4535::setReadDir(void) {
	setReadDirInline();
}
#endif

#ifndef writeRegister8
void LGDP4535::writeRegister8(uint8_t a, uint8_t d) {
	writeRegister8inline(a, d);
}
#endif

#ifndef writeRegister16
void LGDP4535::writeRegister16(uint16_t a, uint16_t d) {
	writeRegister16inline(a, d);
}
#endif

#ifndef writeRegisterPair
void LGDP4535::writeRegisterPair(uint8_t aH, uint8_t aL, uint16_t d) {
	writeRegisterPairInline(aH, aL, d);
}
#endif

