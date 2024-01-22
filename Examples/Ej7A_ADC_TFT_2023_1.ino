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
  Serial.begin(115200);
  tft.begin(); //Inicializar la LCD
  tft.fillScreen(RED);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.setCursor(20,30);
  tft.print("Voltaje:");
  tft.setTextColor(GREEN,RED);
  tft.setTextSize(3);
}

void loop() {
  uint16_t volt=analogRead(34); //Lee el valor del CH6 del ADC1 (GPIO34)
  Serial.print("Voltaje: ");
  Serial.print(volt*(3.3/4095.0));
  Serial.println('v');
  tft.setCursor(20,60);
  tft.print(volt*(3.3/4095.0));
  tft.println('v');
  delay(1000);
}
