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
  
  /*
  int sensorVal = digitalRead(2);
   switch (sensorVal == HIGH) {
    case 1:
      u8g.drawStr( 2, 10, "Left!");
      break;
    case 2:
      u8g.drawStr( 3, 10, "Up!");
      break;
    case 3:
      u8g.drawStr( 4, 10, "Down!");
      break;
    case 4:
      u8g.drawStr( 5, 10, "Right!");
      break;
  }
  */
  /*
  if (sensorVal == HIGH) {
    u8g.drawStr( 2, 3, 4, 5, 10, "Laber");
  } else {
    u8g.drawStr( 2, 10, "Laber net!");
  }
  */
 
  
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
