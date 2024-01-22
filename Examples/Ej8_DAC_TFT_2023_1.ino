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
 
#define ADC1_CH6 34
#define DAC1 25

uint8_t i;

void leerVolt(){
  uint16_t volt=analogRead(ADC1_CH6);
  tft.setTextColor(WHITE,BLACK);
  tft.setCursor(55,5);
  tft.print(volt*(3.3/4095.0));
  tft.print("v");
  tft.setCursor(50,56);
  tft.setTextColor(CYAN,BLACK);
  tft.print(i);
  tft.print("  ");
}


void setup() {
  tft.begin(); //Inicializar la LCD
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(30,5);
  tft.print("V:");
  tft.setTextColor(CYAN);
  tft.setCursor(20,40);
  tft.print("Muestra:");
}

void loop() {
  for(i=0;i<255;i++){
    dacWrite(DAC1,i);
    leerVolt();
    delay(10);
  }
  for(i=255;i>0;i--){
    dacWrite(DAC1,i);
    leerVolt();
    delay(10);
  }

}
