#include <SPI.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h>
#include "Imagenes.h"

//Pin RESET conectado a VCC (+3.3v)
//Pin LED conectado a VCC (+3.3v)
#define CS 5 //pin CS0
#define DC 3 //pin A0
#define MOSI 23 //pin SDA (predefinido en la libreria SPI)
#define SCK 18 //pin CLK (predefinido en la libreria SPI)

TFT_ILI9163C tft=TFT_ILI9163C(CS,DC); //Se crea el objeto de nombre "tft" 

//Definición de colores en formato RGB565
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800 //0b1111100000000000
#define GREEN   0x07E0 //0b0000011111100000
#define BLUE    0x001F //0b0000000000011111
#define YELLOW  0xFFE0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define ORANGE  0xFD20

uint16_t dato;

void setup() {
  tft.begin(); //Inicializar la LCD
  dato=0;
}

void loop() {
  for(uint8_t y=0;y<128;y++){
    for(uint8_t x=0;x<128;x++){
      tft.drawPixel(x,y,Atardecer[dato]);
      dato++;
    }
  }
  delay(5000);
  dato=0;
  for(uint8_t y=0;y<128;y++){
    for(uint8_t x=0;x<128;x++){
      tft.drawPixel(x,y,tft.Color24To565(Batman[dato]));
      dato++;
    }
  }
  delay(5000);
  dato=0;
  for(uint8_t y=0;y<128;y++){
    for(uint8_t x=0;x<128;x++){
      tft.drawPixel(x,y,Bronco[dato]);
      dato++;
    }
  }
  delay(5000);
  dato=0;
  for(uint8_t y=0;y<128;y++){
    for(uint8_t x=0;x<128;x++){
      tft.drawPixel(x,y,Chrome[dato]);
      dato++;
    }
  }
  delay(5000);
  dato=0;
  for(uint8_t y=0;y<128;y++){
    for(uint8_t x=0;x<128;x++){
      tft.drawPixel(x,y,Muralla[dato]);
      dato++;
    }
  }
  delay(5000);
  dato=0;
}
