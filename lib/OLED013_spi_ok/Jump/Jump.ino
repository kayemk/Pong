#include "U8glib.h"
//U8GLIB_SSD1306_132X64 u8g(13, 11, 10, 7, 9);
//                        SCK, MOSI, CS, DC/A0, RST
//U8GLIB_SSD1306_132X64 u8g(10, 7, 9);
//                          CS, DC/A0, RST
U8GLIB_SSD1306_132X64 u8g(10, 9, 12, 11, 13);

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void u8g_line(uint8_t a) {
  u8g.drawLine(7+a, 10, 40, 55);
  u8g.drawLine(7+a*2, 10, 60, 55);
  u8g.drawLine(7+a*3, 10, 80, 55);
  u8g.drawLine(7+a*4, 10, 100, 55);
}

void u8g_disc_circle(uint8_t a) {
  u8g.drawStr( 2, 0, "drawDisc");
  u8g.drawDisc(10,18,9);
  u8g.drawDisc(24+a,16,7);
  u8g.drawStr( 2, 30, "drawCircle");
  u8g.drawCircle(10,18+30,9);
  u8g.drawCircle(24+a,16+30,7);
}

void draw(void) {
  u8g_prepare();
  
  if (digitalRead(2) == LOW) {
    u8g.drawStr( 2, 31, "Left");
  }else if(digitalRead(3) == LOW) {
    u8g.drawStr( 62, 10, "Up");
  }else if(digitalRead(4) == LOW) {
    u8g.drawStr( 62, 50, "Down");
  }else if(digitalRead(5) == LOW) {
    u8g.drawStr( 100, 31, "Right");
  }
 
}

void setup(void) {

  // flip screen, if required
  
  //u8g.setRot180();
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  
  pinMode(13, OUTPUT);           
  digitalWrite(13, HIGH);  
}

void loop(void) {
  
  // picture loop  
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
    
  // rebuild the picture after some delay
  delay(100);

}
