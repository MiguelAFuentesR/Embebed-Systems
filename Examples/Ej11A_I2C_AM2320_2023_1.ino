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

void setup() {
  Serial.begin(115200);
  tft.begin(); //Inicializar la LCD
  am2320.begin();
  tft.fillRect(18,50,90,20,RED);
  tft.fillRect(28,80,70,20,ORANGE);
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
    tft.setCursor(28,55);
    tft.print("Temp: ");
    tft.print(t,1);
    tft.print((char)0xF7); //Visualiza el simbolo de grados °
    tft.print('C');
    tft.setTextColor(WHITE,ORANGE);
    tft.setCursor(33,85);
    tft.print("Hum: ");
    tft.print(h,1);
    tft.print('%');
  }
  delay(1000);
}
