// UTFT_Demo_800x480 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of how to use most of the functions
// of the library with a supported display modules.
//
// This demo was made for modules with a screen resolution 
// of 800x480 pixels.
//
// This program requires the UTFT library.
//

#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
UTFTGLUE myGLCD(0x9163,A2,A1,A3,A4,A0);    //arguments are ignored

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t LargeFont[];


// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Arduino Uno / 2009:
// -------------------
// Standard Arduino Uno/2009 shield            : <display model>,A5,A4,A3,A2
// DisplayModule Arduino Uno TFT shield        : <display model>,A5,A4,A3,A2
//
// Arduino Mega:
// -------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Mega      : <display model>,38,39,40,41
//
// Remember to change the model parameter to suit your display module!
//UTFT myGLCD(ITDB50,38,39,40,41);
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0 
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF
#define TEST            0x1BF5
#define JJCOLOR         0x1CB6
#define JJORNG          0xFD03
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
MCUFRIEND_kbv tft; 

uint8_t YP = A1;  // must be an analog pin, use "An" notation!
uint8_t XM = A2;  // must be an analog pin, use "An" notation!
uint8_t YM = 7;   // can be a digital pin
uint8_t XP = 6;   // can be a digital pin

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 0.005
#define MAXPRESSURE 10000

void setup()
{
  randomSeed(analogRead(0));

  Serial.begin(230400);
  
// Setup the LCD
  myGLCD.InitLCD(PORTRAIT);      //800x480 is already wider than tall.
  myGLCD.setFont(SmallFont);
  
  drawMenue();

  
}


void drawMenue()
{
   /* These two lines are for drawing background in black*/
   myGLCD.setColor(0,0,0);
   //myGLCD.drawRoundRect(x,y,x2,y2); // for open rectangles
   myGLCD.fillRoundRect(0,0,500,500);
   
   myGLCD.setColor(17,150,200);
   myGLCD.fillRoundRect(55,140,165,200);
   myGLCD.setTextSize(2);
   myGLCD.setTextColor(WHITE);
   myGLCD.print("Menu",87,160);
   myGLCD.print("Heart rate",110,240);

   while (1){
    
       tp = ts.getPoint();
       pinMode(XM, OUTPUT);
       pinMode(YP, OUTPUT);
       pinMode(XP, OUTPUT);
       pinMode(YM, OUTPUT);
       if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
       
       myGLCD.setCursor(0,(tft.height()*3)/4);
       //myGLCD.print("Menuhex",17,50);
       //myGLCD.print("tp.x="+String(tp.x)+" tp.y="+String(tp.y),17,50);
       
      // Serial.println("tp.x=" + String(tp.x)  + " tp.y=" + String(tp.y));
       
       if(tp.x>380 && tp.x<780 && tp.y>400 && tp.y<615){

           myGLCD.setColor(random(255), random(255), random(255));
           myGLCD.print("Menuhex",17,50);

           drawButtons();
        
       }
     
        
   }

   

/* 
   myGLCD.setColor(17, 150, 120);
  //myGLCD.drawRoundRect(x,y,x2,y2); // for open rectangles
  myGLCD.fillRoundRect(110,20,200,60);

myGLCD.setColor(17, 150, 120);
//myGLCD.drawRoundRect(x,y,x2,y2); // for open rectangles
myGLCD.fillRoundRect(10,70,100,110);

 
 
myGLCD.setColor(17, 150, 120);
//myGLCD.drawRoundRect(x,y,x2,y2); // for open rectangles
myGLCD.fillRoundRect(110,70,200,110);


myGLCD.setColor(17, 150, 120);
//myGLCD.drawRoundRect(x,y,x2,y2); // for open rectangles
myGLCD.fillRoundRect(10,120,100,160);

myGLCD.setColor(17, 150, 120);
//myGLCD.drawRoundRect(x,y,x2,y2); // for open rectangles
myGLCD.fillRoundRect(110,120,200,160);

myGLCD.setColor(17, 150, 120);
//myGLCD.drawRoundRect(x,y,x2,y2); // for open rectangles
myGLCD.fillRoundRect(10,170,100,210);

myGLCD.setColor(17, 150, 120);
myGLCD.print("That's it!", 12, 173);
//myGLCD.drawRoundRect(x,y,x2,y2); //for open rectangles
myGLCD.fillRoundRect(110,170,200,210);

myGLCD.setColor(17, 150, 220);
//myGLCD.drawRoundRect(x,y,x2,y2); //for open rectangles
myGLCD.fillRoundRect(10,220,100,260);
   
myGLCD.setColor(210, 150, 120);
//myGLCD.drawRoundRect(x,y,x2,y2); //for open rectangles
myGLCD.fillRoundRect(110,220,200,260);

myGLCD.setColor(17, 150, 120);
//myGLCD.drawRoundRect(x,y,x2,y2); //for open rectangles
myGLCD.fillRoundRect(10,270,200,310);
*/
 /* while (1) {
        tp = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        pinMode(XP, OUTPUT);
        pinMode(YM, OUTPUT);
        if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
      //  if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) break;
        myGLCD.setCursor(0, (tft.height() * 3) / 4);
        myGLCD.print("tp.x=" + String(tp.x) + " tp.y=" + String(tp.y) + "   ",17,110);
        Serial.println("tp.x=" + String(tp.x)  + " tp.y=" + String(tp.y));
   }
   */
    
}

void drawButtons(){

    myGLCD.clrScr(); // First clear existing menu wali screen
    // Now make background for new frame 
    myGLCD.setColor(0,0,0);  
    myGLCD.fillRoundRect(0,0,500,500);

    // Now I will make buttons

    myGLCD.setColor(17,150,200);
    myGLCD.fillRoundRect(55,40,165,80);

    myGLCD.setTextSize(2);
    myGLCD.setTextColor(WHITE);
    myGLCD.print("Back",87,54);

    // Bulb1
    myGLCD.setColor(17,150,200);
    myGLCD.fillRoundRect(55,90,165,130);
    myGLCD.setTextSize(2);
    myGLCD.setTextColor(WHITE);
    myGLCD.print("Bulb1",87,104);
    
    // Bulb2
    myGLCD.setColor(17,150,200);
    myGLCD.fillRoundRect(55,140,165,180);
    myGLCD.setTextSize(2);
    myGLCD.setTextColor(WHITE);
    myGLCD.print("Bulb2",87,154);

    //Bulb3
    myGLCD.setColor(17,150,200);
    myGLCD.fillRoundRect(55,190,165,230);
    myGLCD.setTextSize(2);
    myGLCD.setTextColor(WHITE);
    myGLCD.print("Bulb3",87,204);

    // Bulb4
    myGLCD.setColor(17,150,200);
    myGLCD.fillRoundRect(55,240,165,280);
    myGLCD.setTextSize(2);
    myGLCD.setTextColor(WHITE);
    myGLCD.print("Bulb4",87,254);

    while (1){
    
       tp = ts.getPoint();
       pinMode(XM, OUTPUT);
       pinMode(YP, OUTPUT);
       pinMode(XP, OUTPUT);
       pinMode(YM, OUTPUT);
       if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
       
       myGLCD.setCursor(0,(tft.height()*3)/4);
          //myGLCD.print("Menuhex",17,50);
          //myGLCD.print("tp.x="+String(tp.x)+" tp.y="+String(tp.y),17,50);
       
       Serial.println("tp.x=" + String(tp.x)  + " tp.y=" + String(tp.y));

       if(tp.x>310 && tp.x<730 && tp.y>750 && tp.y<850){

           //myGLCD.setColor(random(255), random(255), random(255));
           //myGLCD.print("Menuhex",17,50);
           drawMenue();
        
       }

       else if(tp.x>310 && tp.x<730 && tp.y>620 && tp.y<720){

          // Bulb 1 pressed
          Serial.println("Bulb 1 pressed");
          
        
       }
       else if(tp.x>310 && tp.x<730 && tp.y>490 && tp.y<590){

           //Bulb 2 pressed
           Serial.println("Bulb 2 pressed");
        
       }

       else if(tp.x>310 && tp.x<730 && tp.y>360 && tp.y<460){

           // Bulb 3 pressed
           Serial.println("Bulb 3 pressed");
       
       }

       else if(tp.x>310 && tp.x<730 && tp.y>230 && tp.y<330){

           // Bulb 4 pressed
           Serial.println("Bulb 4 pressed");
           
        
       }

       
        
    }

 
    
    


  
}

void loop()
{
  /*int buf[798];
  int x, x2;
  int y, y2;
  int r;

   */
  
 /* myGLCD.setColor(0,0,0);
  //myGLCD.fillRect(1,15,798,464);
   
// Draw some random rectangles  */
  /*for (int i=0; i<250; i++)
  {
    myGLCD.setColor(random(255), random(255), random(255));
    x=2+random(796);
    y=16+random(447);
    x2=2+random(796);
    y2=16+random(447);
    myGLCD.drawRect(x, y, x2, y2);
  }

  delay(2000);
  
  */

  /*drawMenue();
   */
 
  /*delay (10000);
   */
 
}
