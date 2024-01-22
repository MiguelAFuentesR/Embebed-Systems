#include <SPI.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h>
#include "Imagenes_LED.h"

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

#define LED 2 //Define GPIO2

volatile uint8_t cont1,cont2,cont3,LED1,LED2,LED3;

hw_timer_t *timer0=NULL;
hw_timer_t *timer1=NULL;
hw_timer_t *timer2=NULL;
hw_timer_t *timer3=NULL;

void IRAM_ATTR Int_Timer0(){
  digitalWrite(LED,!digitalRead(LED));
}

void IRAM_ATTR Int_Timer1(){
  cont1=1;
  LED1=!LED1;
}

void IRAM_ATTR Int_Timer2(){
  cont2=1;
  LED2=!LED2;
}

void IRAM_ATTR Int_Timer3(){
  cont3=1;
  LED3=!LED3;
}

void dibujarImagen(uint8_t xi,uint8_t yi,uint8_t size_x,uint8_t size_y,const uint16_t *bitmap){
uint16_t dato=0;
  for(uint8_t y=yi;y<yi+size_y;y++){
    for(uint8_t x=xi;x<xi+size_x;x++){
      tft.drawPixel(x,y,bitmap[dato]);
      dato++;
    }
  }
}


void setup() {
  tft.begin();
  tft.fillScreen(WHITE);
  pinMode(LED,OUTPUT);

  timer0=timerBegin(0,80,true); //Configura Timer 0 con preesc.x80 (=1MHz) y cambio por flanco de bajada
  timerAlarmWrite(timer0,1000000,true); //Timer 0 genera 1.000.000 de conteos (=1s) con autorecarga
  timerAttachInterrupt(timer0,Int_Timer0,true); //Hab. int del Timer 0
  timerAlarmEnable(timer0); //Habilitar el Timer 0

  timer1=timerBegin(1,80,true); //Configura Timer 1 con preesc.x80 (=1MHz) y cambio por flanco de bajada
  timerAlarmWrite(timer1,2000000,true); //Timer 1 genera 2.000.000 de conteos (=2s) con autorecarga
  timerAttachInterrupt(timer1,Int_Timer1,true); //Hab. int del Timer 1
  timerAlarmEnable(timer1); //Habilitar el Timer 1

  timer2=timerBegin(2,80,true); //Configura Timer 2 con preesc.x80 (=1MHz) y cambio por flanco de bajada
  timerAlarmWrite(timer2,5000000,true); //Timer 2 genera 5.000.000 de conteos (=5s) con autorecarga
  timerAttachInterrupt(timer2,Int_Timer2,true); //Hab. int del Timer 2
  timerAlarmEnable(timer2); //Habilitar el Timer 2

  timer3=timerBegin(3,80,true); //Configura Timer 3 con preesc.x80 (=1MHz) y cambio por flanco de bajada
  timerAlarmWrite(timer3,500000,true); //Timer 3 genera 500.000 de conteos (=0.5s) con autorecarga
  timerAttachInterrupt(timer3,Int_Timer3,true); //Hab. int del Timer 3
  timerAlarmEnable(timer3); //Habilitar el Timer 3

  cont1=0,cont2=0,cont3=0;
  LED1=0,LED2=0,LED3=0;

  dibujarImagen(48,10,30,30,LEDVerdeOff);
  dibujarImagen(48,50,30,30,LEDNaranjaOff);
  dibujarImagen(48,90,30,30,LEDRojoOff);
}

void loop() {
  if(cont1!=0){
    if(LED1==0){
      dibujarImagen(48,10,30,30,LEDVerdeOff);
    }else{
      dibujarImagen(48,10,30,30,LEDVerdeOn);
    }
    cont1=0;
  }

  if(cont2!=0){
    if(LED2==0){
      dibujarImagen(48,50,30,30,LEDNaranjaOff);
    }else{
      dibujarImagen(48,50,30,30,LEDNaranjaOn);
    }
    cont2=0;
  }

  if(cont3!=0){
    if(LED3==0){
      dibujarImagen(48,90,30,30,LEDRojoOff);
    }else{
      dibujarImagen(48,90,30,30,LEDRojoOn);
    }
    cont3=0;
  }
}
