/*
kayemk
*/
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 13);

//                        D0, D1,CS, DC, RST
//U8GLIB_PCD8544 u8g (10, 9, 12, 11, 13);
//U8GLIB_SSD1306_128X64 u8g(10, 7, 9);

short ballSX           = 3;
short ballSY           = 2;

const byte width           = 127;
const byte height          = 63;

const byte ballPadding     = 1;
const byte ballSize        = 2;

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void u8g_line(uint8_t a) {
  u8g.drawLine( 1, 60, 128, 60);
}

void u8g_r_frame(uint8_t a) {
  u8g.drawRFrame(5, 10,40,30, a+1);
}

uint8_t draw_hpX = 100;

uint8_t draw_state = 0;
uint8_t p1X = 10;
uint8_t p1Y = 29;
uint8_t p2X = 120;
uint8_t p2Y = 29;
uint8_t ballX = 63;
uint8_t ballY = 31;
uint8_t padH = 15;
uint8_t p1_padY = 15;
uint8_t p2_padY = 15;
uint8_t p1_padX = 5;
uint8_t p2_padX = 5;

void reset()
{
  // Reset the game to the initial state;
  ballX = 63;
  ballY = 31;
  p1Y = 28;
  p2Y = 28;
  ballSX = 3;
  ballSY = 2;
  
  draw();
  
  delay(2000);
}

void checkCollision() {
    if(ballSX > 0) {
      // check collision for bottom
      if (ballY + ballSize + ballPadding >= height)  {
        
        ballY = height - ballSize - ballPadding;
        ballSX *= -1;
      }
      }else{
    
        // check collision for top
        if (ballY <= 0) {
          ballY = 0;
          ballSX *= -1;
        }
      }
      // check collision for left paddle
      if(ballX <= p1X + ballSY && (ballY - ballSize >= p1Y && ballY <= p1Y + p1_padY))
    {
      ballSY *= -1;
      ballX = p1X+2;
    }
      // check for left end
      if(ballX <= 1) {
        ballX = 0;
        u8g.drawStr( 2, 0, "Player 2 won!");
        reset();
      }
  // -----
    if(ballSY > 0) {
   
      // check collision for right paddle
      if(ballX + ballSize + ballPadding >= p2X && (ballY <= p2Y + p2_padY && ballY >= p2Y)) {
        ballX = p2X-3;
        ballSY *= -1;
      }
      // check for right end
      if (ballX + ballSize + ballPadding >= width) {
        ballX = width - ballSize - ballPadding; 
        u8g.drawStr( 2, 0, "Player 1 won!");   
        reset();
      }
      
    }else{
    /*
    */
  }
}

void draw(void) {
  u8g_prepare();
  u8g.drawDisc(ballX, ballY, 3);
  u8g.drawBox(p1X,p1Y,p1_padX,p1_padY);
  u8g.drawBox(p2X,p2Y,p2_padX,p2_padY);
 // P1
 if (digitalRead(2) == HIGH) {
  u8g.drawBox(p1X,p1Y, p1_padX, p1_padY);
  }else{
    if(p1Y <= 0) {
    u8g.drawBox(p1X,0, p1_padX, p1_padY);
    }else{
    u8g.drawBox(p1X,p1Y--, p1_padX, p1_padY);
    }   
  }
  
  if (digitalRead(3) == HIGH) {
  u8g.drawBox(p1X,p1Y, p1_padX, p1_padY);
  }else{
    if(p1Y >= 52) {
    u8g.drawBox(p1X,p1Y, p1_padX, p1_padY);
    }else{
    u8g.drawBox(p1X,p1Y++, p1_padX, p1_padY);
    }
  }
  // P2
   if (digitalRead(4) == HIGH) {
  u8g.drawBox(p2X,p2Y, p2_padX, p2_padY);
  }else{
    if(p2Y <= 0) {
    u8g.drawBox(p2X,0, p2_padX, p2_padY);
    }else{
    u8g.drawBox(p2X,p2Y--, p2_padX, p2_padY);
    }   
  }
  
  if (digitalRead(5) == HIGH) {
  u8g.drawBox(p2X,p2Y, p2_padX, p2_padY);
  }else{
    if(p2Y >= 52) {
    u8g.drawBox(p2X,52, p2_padX, p2_padY);
    }else{
    u8g.drawBox(p2X,p2Y++, p2_padX, p2_padY);
    }
  }
}

void update()
{
  ballY += ballSX;
  ballX += ballSY;
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
  update();
  checkCollision();
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


