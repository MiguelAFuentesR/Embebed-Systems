                 
#include <TFT_ILI9163C.h>                
#include <Adafruit_GFX.h>
#include <SPI.h>
#define CS=15 DC=12 SCLK=14 SDA=13 


#define WHITE       0xFFFF
   #define BLACK       0x0000
   #define BLUE        0x001F
   #define RED         0xF800
   #define GREEN       0x07E0
   #define CYAN        0x07FF
   #define MAGENTA     0xF81F
   #define YELLOW      0xFFE0
   #define GREY        0x2108 
   #define SCALE0      0xC655                                                  // accent color for unused scale segments                                   
   #define SCALE1      0x5DEE                                                  // accent color for unused scale segments
   #define TEXT_COLOR  0xFFFF                                                  // is currently white 

void setup() {
  TFT_ILI9163C tft=TFT_ILI9163C();
  // put your setup code here, to run once:
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(WHITE); 
  tft.setCursor(0,0); 
}


void loop() {
  tft.print("Hola Mundo"); 
}
