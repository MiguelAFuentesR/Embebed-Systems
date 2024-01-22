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

#define LED 2 //Define GPIO2

volatile uint8_t bandera; //Indica el ingreso a la rutina de int. del Timer
volatile uint16_t tiempo; //Contador de tiempo (número de interrupciones generadas por el Timer)

hw_timer_t *timer=NULL; //Se crea el objeto "timer"

void IRAM_ATTR Int_Timer(){
  digitalWrite(LED,!digitalRead(LED));
  tiempo++;
  bandera=1;
}

void setup() {
  Serial.begin(115200);
  tft.begin(); //Inicializar la LCD
  tft.setTextColor(ORANGE);
  tft.setTextSize(2);
  tft.setCursor(20,30);
  tft.print("Tiempo");
  tft.setTextColor(GREEN,BLACK);
  tft.setTextSize(3);
  pinMode(LED,OUTPUT);
  timer=timerBegin(0,80,true); //Configurar Timer 0 con preesc. x80 (1MHz) y conteo ascendente
  timerAlarmWrite(timer,1000000,true); //Timer 0 conf. a 1s (1000000us) y con autorecarga
  timerAttachInterrupt(timer,Int_Timer,true); //Hab. int. del Timer 0
  timerAlarmEnable(timer); //Habilitar el Timer 0
  bandera=0;
  tiempo=0;  
}

void loop() {
  if(bandera!=0){ //Verificar si se ingresó a la rutina de int. del Timer 0
    bandera=0;
    Serial.print("Tiempo: ");
    Serial.print(tiempo);
    Serial.println('s');
    tft.setCursor(20,60);
    tft.print(tiempo);
    tft.print('s');
  }
}
