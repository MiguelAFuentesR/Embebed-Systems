#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
#include"Imagenes_ADC_Temp.h"

//Pin RESET conectado a Vcc (+3.3v)
//Pin LED conectado a +3.3V
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


#define xiPos 20
#define yiPos 40
uint8_t xi,yi,diametro,alto,icono_act,icono_ant;
uint8_t xPos,yPos,xPosAnt,yPosAnt,paso,muestreo,x_maxim;


void screenMarco(){
  //Genera la imagen del termometro, además de la escala correspondiente
  tft.fillCircle(xi+diametro/2,yi,diametro/2,BLACK);
  tft.fillRect(xi,yi,diametro,alto,BLACK);
  tft.fillCircle(xi+diametro/2,95,20,BLACK);
  tft.fillCircle(xi+diametro/2,95,16,RED);
  tft.setTextSize(1);
  tft.setTextColor(BLACK);
  for(uint8_t i=0;i<=alto-10;i+=10 ){
      tft.drawFastHLine(xi+20,yi+i,6,BLACK);
      tft.drawFastHLine(xi+20,yi+i+5,3,BLACK);
      tft.setCursor(xi+28,yi-3+i);
      tft.print(alto-i);
      tft.drawCircle((xi+28)+13,yi-3+i,1,BLACK);
  }
  //Genera texto de la gráfica del histórico
  tft.setCursor(xPos-5,yPos-22);
  tft.print("HISTORICO");
  tft.setCursor(xPos-6,yPos-22);
  tft.print("HISTORICO");
  tft.setCursor(xPos-4,yPos-10);
  tft.print((char)0xF7);
  tft.print("C");
  tft.setCursor(xPos+x_maxim+3,yPos+alto-4);
  tft.print("m");
}

void screenPlantilla(){
  //Genera ejes y datos de la gráfica Histórico
  tft.fillRect(xPos,yPos,x_maxim+1,alto+1,WHITE);
  for(uint8_t i=paso;i<=x_maxim;i+=paso){
    tft.drawFastVLine(xPos+i,yPos+alto,4,BLACK);
    tft.setRotation(1);
    tft.setCursor(yPos+alto+6,128-(xPos+i));
    tft.print(i);
    tft.setRotation(0);
  }
  for(uint8_t i=0;i<alto;i+=paso){
    tft.drawFastHLine(xPos-4,yPos+i,4,BLACK);
    tft.setCursor(xPos-16,yPos-3+i);
    tft.print(alto-i);
  }
  tft.drawFastVLine(xPos,yPos,alto,BLACK);
  tft.drawFastHLine(xPos,yPos+alto,x_maxim+1,BLACK);
}


void dibujarImagen(uint8_t x1,uint8_t y1,uint8_t size_x, uint8_t size_y, uint8_t total_x, const uint16_t *bitmap){
//x1: coordenada en x donde se inicia a dibujar la imagen   
//y1: coordenada en y donde se inicia a dibujar la imagen  
//size_x: tamaño de la porción en x de la imagen a dibujar
//size_y: tamaño maximo de la imagen en y
//total_x: tamaño maximo de la imagen en x
  
  uint16_t dato=0;  
  for(uint8_t y=y1;y<y1+size_y;y++){
    for(uint8_t x=x1;x<x1+size_x;x++){
      tft.drawPixel(x,y,bitmap[dato]);
      dato++;
    }
    if(size_x!=total_x){
      dato=dato+(total_x-size_x);
    }
  }
}

void setup() {
  tft.begin();
  tft.fillScreen(WHITE);
  xi=85,yi=30,diametro=17,alto=50,icono_act=0,icono_ant=4;
  xPos=xiPos;yPos=yiPos;paso=10;muestreo=10;x_maxim=40;
  screenMarco();
  screenPlantilla();
}

void loop() {
  uint16_t volt=analogRead(34);
  uint16_t tm=map(volt,0,4095,0,alto); //Escalizar valor del ADC para graficar
  tft.setTextColor(BLACK,WHITE);
  tft.setCursor(xi-8,10);
  tft.print("t=");
  tft.print(volt*(alto/4095.0),1); //Escaliza valor del ADC para mostrar dato de temperatura
  tft.print((char)0xF7); //Simbolo de °
  tft.print(" ");
  tft.fillRect(xi+(diametro-10)/2,yi+(alto-tm),10,tm,RED); //Genera un rectagulo dinamico que depende de la temperatura
  tft.fillRect(xi,yi,diametro,alto-tm,BLACK);
  if(tm<=10){
    icono_act=0;
    if(icono_act!=icono_ant){
      for(uint8_t i=5;i<=20;i+=5){      
        tft.fillRect(xi-20,yi+2,20,40,WHITE);
        dibujarImagen(xi-i,yi+2,i,40,20,Media_Nieve);
        delay(100);
      }
      icono_ant=icono_act;
    }    
  }else{
    if(tm>=25){
      icono_act=1;
      if(icono_act!=icono_ant){
        for(uint8_t i=5;i<=20;i+=5){      
          tft.fillRect(xi-20,yi+2,20,40,WHITE);
          dibujarImagen(xi-i,yi+2,i,40,20,Medio_Sol);
          delay(100);
        }
        icono_ant=icono_act;
      }  
    }else{
      icono_act=2;
      if(icono_act!=icono_ant){
        if(icono_ant==0){
          for(uint8_t i=15;i>=5;i-=5){      
            tft.fillRect(xi-20,yi+2,20,40,WHITE);
            dibujarImagen(xi-i,yi+2,i,40,20,Media_Nieve);
            delay(100);
          }
        }
        if(icono_ant==1){
          for(uint8_t i=15;i>=5;i-=5){      
            tft.fillRect(xi-20,yi+2,20,40,WHITE);
            dibujarImagen(xi-i,yi+2,i,40,20,Medio_Sol);
            delay(100);
          }
        }
        tft.fillRect(xi-20,yi+2,20,40,WHITE);
        icono_ant=icono_act;
      } 
    }

    if(xPos==xiPos){ //Dibuja punto inicial de la gráfica
        tft.drawPixel(xiPos+1,yiPos+alto-tm,BLUE);
        xPosAnt=xiPos+1;
        yPosAnt=yiPos+alto-tm;
        xPos++;
    }else{
      tft.drawLine(xPosAnt,yPosAnt,xPos+1,yPos+alto-tm,BLUE);
      xPosAnt=xPos+1;
      yPosAnt=yPos+alto-tm;
      if(xPos>=(x_maxim-1)+xiPos){
        xPos=xiPos;
        screenPlantilla();
      }else{
        xPos++;
      }
    }    
  }
  
  delay(1000);
}
