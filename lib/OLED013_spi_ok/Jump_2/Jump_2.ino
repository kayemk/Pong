
#include "U8glib.h"

U8GLIB_SSD1306_132X64 u8g(10, 9, 12, 11, 13);

//                        D0, D1,CS, DC, RST
//U8GLIB_PCD8544 u8g (10, 9, 12, 11, 13);
//U8GLIB_SSD1306_128X64 u8g(10, 7, 9);


void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void u8g_line(uint8_t a) {
  u8g.drawLine( 1, 60, 128, 60);
}

void u8g_disc_circle(uint8_t a) {
  u8g.drawDisc(10, 55, 5);
}

void u8g_r_frame(uint8_t a) {
  u8g.drawRFrame(5, 10,40,30, a+1);
}
void u8g_disc_circle_up(uint8_t a) {
u8g.drawDisc(10, 15, 5);
}

uint8_t draw_hpX = 100;

void status_hp (int hp_amount) {
   
}

uint8_t draw_state = 0;
uint8_t draw_discX = 10;
uint8_t draw_discY = 55;
const uint8_t p1_bmp[] = {
  0x42, 0x4d, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00,
  0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x13, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4e, 0x00,
  0x00, 0x00, 0xad, 0x1b, 0x00, 0x00, 0xad, 0x1b, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xbe, 0x80, 0x00, 0x00, 0xbe, 0xe0, 0x00, 0x00, 0xbe, 0xd6,
  0x82, 0x02, 0xbe, 0xe0, 0x00, 0x00, 0xbe, 0xe2, 0xe5, 0x02, 0xc9, 0xe0,
  0x00, 0x00, 0xf7, 0x9b, 0x26, 0x02, 0xf7, 0x80, 0x00, 0x00, 0x77, 0x00,
  0x00, 0x00, 0x77, 0x60, 0x00, 0x00, 0x77, 0x72, 0x41, 0x00, 0x77, 0x60,
  0x00, 0x00, 0x77, 0x72, 0x41, 0x00, 0x88, 0xe0, 0x00, 0x00, 0xf7, 0xf2,
  0x41, 0x00, 0xeb, 0x80, 0x00, 0x00, 0xd5, 0x80, 0x00, 0x00, 0xc1, 0x80,
  0x00, 0x00, 0xe3, 0x80, 0x00, 0x00, 0x00, 0x00
};

int hp_amount = 3;

void draw(void) {
  u8g_prepare();
//  u8g.drawBitmap(0, 0, 9, 19, p1_bmp);

 
  u8g.drawLine( 1, 60, 128, 60);
  u8g.drawBox(draw_state,45,15,15);
  /*if (digitalRead(2) == HIGH) {
  u8g.drawDisc(draw_discX, draw_discY, 5);
  }else{
  u8g.drawDisc(draw_discX, draw_discY, 5);
  }*/
 if (digitalRead(2) == HIGH) {
  u8g.drawDisc(draw_discX, draw_discY, 5);
  }else{
    draw_discY == 15;
  u8g.drawDisc(draw_discX, 15, 5);
  }
  if (draw_state == (draw_discX +5) && draw_discY == 55) {
      hp_amount = hp_amount-1;
  }
   
  if(hp_amount == 3) {
    u8g.drawDisc(draw_hpX, 5, 2); 
    u8g.drawDisc(draw_hpX + 7, 5, 2);
    u8g.drawDisc(draw_hpX + 14, 5, 2); 
  }else if(hp_amount == 2) {
    u8g.drawDisc(draw_hpX + 7, 5, 2);
    u8g.drawDisc(draw_hpX + 14, 5, 2);
  }else if(hp_amount == 1){
    u8g.drawDisc(draw_hpX + 14, 5, 2);
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
  
  // increase the state
  draw_state--;
  if ( draw_state <= -20 )
    draw_state = 135;   
  
  // rebuild the picture after some delay
  delay(10);

}


