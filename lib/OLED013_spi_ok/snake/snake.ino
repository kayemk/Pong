/*

  GraphicsTest.pde
  
  >>> Before compiling: Please remove comment from the constructor of the 
  >>> connected graphics display (see below).
  
  Universal 8bit Graphics Library, http://code.google.com/p/u8glib/
  
  Copyright (c) 2012, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  


*/


#include "U8glib.h"
U8GLIB_SSD1306_132X64 u8g(10, 9, 12, 11, 13);
//                        D0, D1,CS, DC, RST

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

int hp_amount = 3;

void draw(void) {
  u8g_prepare();
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


