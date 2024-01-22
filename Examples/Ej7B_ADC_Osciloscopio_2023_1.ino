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

#define ADC1_CH6 34 //Canal 6 del ADC1 del ESP32 en GPIO34

uint8_t xiPos=2,yiPos=2,xPos,yPos,muestreo,maxim;

void screenPlantilla(){
  tft.fillScreen(BLUE);
  for(uint8_t i=10;i<=maxim;i+=10){
    tft.drawFastVLine(xPos+i,yPos,maxim,0x633F);
  }
  for(uint8_t i=10;i<=maxim;i+=10){
    tft.drawFastHLine(xPos,yPos+i,maxim,0x633F);
  }
  tft.drawFastVLine(xPos,yPos,maxim,WHITE);
  tft.drawFastHLine(xPos,yPos+(maxim/2)-1,maxim-1,WHITE);
  tft.setCursor(85,4);
  tft.print("V=");
}

void setup() {
  tft.begin(); //Inicializar la LCD
  tft.setTextColor(WHITE,BLUE);
  xPos=xiPos;
  yPos=yiPos;
  muestreo=100;
  maxim=120;
  screenPlantilla();
}

void loop() {
  uint16_t volt=analogRead(ADC1_CH6); //Lee valor del ADC
  uint16_t voltEsc=map(volt,0,4095,0,maxim); //Escaliza valor leido del ADC para graficar
  tft.setCursor(97,4);
  tft.print(volt*(3.3/4095.0)); //Escalizada medición del ADC en milivoltios
  tft.drawPixel(xPos+1,yPos+maxim-voltEsc,BLACK); //Dibujar el punto asociado al valor leido del ADC
  if(xPos>maxim){
    xPos=xiPos;
    screenPlantilla();
  }else{
    xPos++;
  }
  delay(muestreo);
}
