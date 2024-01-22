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
  randomSeed(0x8080);
}

void loop() {
  testFillScreen();
  delay(2000);
  testTexto();
  delay(2000);
  testRectangulos();
  delay(2000);
  testLineas();
  delay(2000);
}

void testFillScreen(){
  tft.setTextColor(WHITE,MAGENTA);
  tft.setTextSize(2); //Asigna tamaño 2 al texto (10x14 px)
  tft.fillScreen(BLACK);
  tft.setCursor(20,0);
  tft.println("Negro");
  delay(1000);
  tft.fillScreen(WHITE);
  tft.setCursor(20,0);
  tft.println("Blanco");
  delay(1000);
  tft.fillScreen(RED);
  tft.setCursor(20,0);
  tft.println("Rojo");
  delay(1000);
  tft.fillScreen(BLUE);
  tft.setCursor(20,0);
  tft.println("Azul");
  delay(1000);
  tft.fillScreen(GREEN);
  tft.setCursor(20,0);
  tft.println("Verde");
  delay(1000);
  tft.fillScreen(CYAN);
  tft.setCursor(20,0);
  tft.println("Cyan");
  delay(1000);
  tft.fillScreen(ORANGE);
  tft.setCursor(20,0);
  tft.println("Naranja");
  delay(1000);
  tft.fillScreen(YELLOW);
  tft.setCursor(20,0);
  tft.println("Amarillo");
  delay(1000);
}


void testTexto(){
  tft.fillScreen(); //Fondo color negro
  tft.setCursor(0,0);
  tft.setTextColor(WHITE,MAGENTA);
  tft.setTextSize(1); //Asigna tamaño 1 al texto (5x7 px)
  tft.println("SizeFont #1");
  tft.setTextColor(YELLOW);
  tft.setTextSize(2); //Asigna tamaño 2 al texto (10x14 px)
  tft.println("0123456789");
  tft.setTextColor(RED);
  tft.setTextSize(3); //Asigna tamaño 3 al texto (15x21 px)
  tft.println(0xDEAD,HEX);
  tft.setTextColor(GREEN,ORANGE);
  tft.setTextSize(4); //Asigna tamaño 4 al texto (20x28 px)
  tft.println("Hello");
  tft.setTextColor(BLUE);
  tft.setTextSize(5); //Asigna tamaño 5 al texto (25x35 px)
  tft.println("AbCd");
}

void testRectangulos(){
  tft.fillScreen();
  tft.fillRect(20,5,5,20,BLUE);
  tft.drawRect(40,50,40,20,RED);
  delay(2000);
  for(uint8_t y=0;y<128;y+=32){
    for(uint8_t x=0;x<128;x+=32){
      tft.fillRect(x,y,32,32,random(0xFFFF));
      tft.drawRect(x,y,32,32,random(0xFFFF));
      delay(200);
    }
  }
}

void testLineas(){
  tft.fillScreen();
  for(uint8_t i=0;i<10;i++){
    tft.drawLine(random(2,120),random(2,120),100,100,random(0xFFFF));
  }
}
