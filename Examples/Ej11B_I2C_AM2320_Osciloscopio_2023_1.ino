#include <SPI.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"

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

Adafruit_AM2320 am2320=Adafruit_AM2320(); //Se crea objeto "am2320"

uint8_t xiPos,yiPos,xPos,yPos,maxim;
uint16_t muestreo;

void screenPlantilla(){
  tft.fillScreen(BLUE);
  for(uint8_t i=10;i<=maxim;i+=10){
    tft.drawFastVLine(xPos+i,yPos,maxim,0x633F);
  }
  for(uint8_t i=10;i<=maxim;i+=10){
    tft.drawFastHLine(xPos,yPos+i,maxim,0x633F);
  }
  tft.drawRect(xPos,yPos,maxim+1,(maxim/2)+1,WHITE);
  tft.drawRect(xPos,yPos+maxim/2,maxim+1,(maxim/2)+1,WHITE);
}


void setup() {
  Serial.begin(115200);
  am2320.begin();
  tft.begin();
  tft.fillScreen(BLUE);
  xiPos=5;
  yiPos=7;
  xPos=xiPos;
  yPos=yiPos;
  muestreo=500;
  maxim=120;
  screenPlantilla();
}

void loop() {
  float t=am2320.readTemperature(); //Leer el valor de la temperatura actual
  float h=am2320.readHumidity(); //Leer el valor de la humedad relativa actual
  if(isnan(h)||isnan(t)){
    Serial.println("Error de comunicación con el sensor AM2320!!!");
  }else{
    Serial.print("Temp: ");
    Serial.println(t,1);
    Serial.print("Hum: ");
    Serial.println(h,1);
    tft.setTextColor(WHITE,RED);
    
    tft.setTextColor(WHITE,RED);
    tft.setCursor (3,1),
    tft.print("Temp:");
    tft.print(t,1);
    tft.print((char)0xF7); //Visualiza el simbolo de grados °
    tft.print("C");
    tft.setTextColor(WHITE,ORANGE);
    tft.setCursor (74,1),
    tft.print("Hum:");
    tft.print(h,1);
    tft.print("%");

    uint16_t tEsc=t*(maxim/2)/80; //Escaliza valor leido de la temperatura para graficar
    tft.drawPixel(xPos+1,yPos+(maxim/2)-tEsc,RED); //Dibujar el punto asociado al valor leido de la temperatura
    uint16_t hEsc=h*(maxim/2)/100; //Escaliza valor leido de la humedad para graficar
    tft.drawPixel(xPos+1,yPos+maxim-hEsc,ORANGE); //Dibujar el punto asociado al valor leido de la humedad
    if(xPos>maxim){
    xPos=xiPos;
    screenPlantilla();
    }else{
      xPos++;
    }
  }
  delay(muestreo);
}
