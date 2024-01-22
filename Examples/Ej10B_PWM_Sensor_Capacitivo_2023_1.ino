#include <SPI.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h>

//Pin RESET conectado a Vcc (+3.3v)
//Pin LED conectado a +3.3v
#define CS 5 //CS0
#define DC 3 //A0
#define MOSI 23 //SDA
#define SCK 18 //CLK

TFT_ILI9163C tft=TFT_ILI9163C(CS,DC); //Se crea objeto de nombre tft

//Definición de colores en formato RGB565
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define YELLOW  0xFFE0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define ORANGE  0xFD80

#define LED 2 //Define GPIO2
#define PWMChannel 0 //Canal PWM utilizado (valor entre 0 y 15)
#define PWMResolution 12 //Resolución de 12 bits (valor entre 1 y 16)
#define PWMFreq 5000 //Frecuencia del PWM a 5KHz

uint8_t SensorT4,SensorT5;
uint16_t ciclo,ciclo_ant;

void setup() {
  Serial.begin(115200);
  tft.begin();
  ledcSetup(PWMChannel,PWMFreq,PWMResolution);
  ledcAttachPin(LED,PWMChannel);
  ciclo=2048;
  ciclo_ant=ciclo;
  ledcWrite(PWMChannel,ciclo);
  Serial.print((ciclo*100/4095.0),1); //Escaliza ciclo util entre 0% y 100%
  Serial.println("%");
  tft.fillScreen(map(ciclo,0,4095,0,31));
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(25,10);
  tft.print("Azul al");
  tft.setCursor(35,40);
  tft.print((ciclo*100/4095.0),1);
  tft.print("%");
}

void loop() {
  SensorT4=touchRead(T4);
  SensorT5=touchRead(T5);

  if(SensorT4<30&&SensorT4>5){
    ciclo+=128;
    if(ciclo>4095){ciclo=4095;}
    while(SensorT4<30){SensorT4=touchRead(T4);}
  }
  if(SensorT5<30&&SensorT5>5){
    if(ciclo==4095){
      ciclo=3968;
    }else{
      if(ciclo!=0){ciclo-=128;}
    }
    while(SensorT5<30){SensorT5=touchRead(T5);}
  }
  if(ciclo!=ciclo_ant){
    ledcWrite(PWMChannel,ciclo); //Actualiza el valor del ciclo util en el PWM
    Serial.print((ciclo*100/4095.0),1);
    Serial.println("%");
    tft.fillScreen(map(ciclo,0,4095,0,31));
    tft.setCursor(25,10);
    tft.print("Azul al");
    tft.setCursor(35,40);
    tft.print((ciclo*100/4095.0),1);
    tft.print("%");
    ciclo_ant=ciclo;
  }
  delay(500);
}
