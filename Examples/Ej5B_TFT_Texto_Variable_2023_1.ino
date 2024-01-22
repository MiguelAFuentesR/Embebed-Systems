#include <SPI.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h>

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

void setup() {
  tft.begin(); //Inicializar la LCD
  tft.fillScreen(BLUE);
  tft.setTextColor(WHITE,BLUE);
  tft.setTextSize(1);
  tft.setCursor(20,30);
  tft.print("Tiempo");
  tft.setCursor(20,40);
  tft.print("desde reset:");
}

void loop() {
  tft.setCursor(20,50);
  tft.print(millis()/1000);
  tft.print('s');
}
