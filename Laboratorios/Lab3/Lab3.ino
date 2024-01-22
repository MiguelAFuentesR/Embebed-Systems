#include <ESP32Servo.h>
#include "RTClib.h"

#include <SPI.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h>



#define SERVO_PIN 26  // ESP32 pin GIOP26 connected to servo motor
#define LED 2
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


uint16_t umbralSensorT9 = 0;
uint16_t umbralSensorT5 = 0;
uint16_t umbralSensorT6 = 0;
uint16_t umbralSensorT7 = 0;
uint8_t SensorT9, SensorT5, SensorT6, SensorT7;
int segundo, minuto, hora, dia, mes, anio;
int velocidad;
int velAct;
uint8_t pos = 80;
char date[10] = "06:00:10";
DateTime now;

RTC_DS1307 rtc;
Servo servoMotor;
hw_timer_t *My_timer = NULL;

void IRAM_ATTR onTimer() {
  // digitalWrite(LED, !digitalRead(LED));
  
//  if(digitalRead(LED)==HIGH){
//    if(pos>18){
//      if(pos<=21){
//        pos = 18;
//      }else{
//        pos=pos-3;
//      }
//    }else{
//      if(pos>=15){
//        pos = 18;
//      }else{
//      pos = pos+3;
//      }
//    }
//  }else{
//    if (pos < 180) {
//      pos++;
//    }
//  }
  if(digitalRead(LED)==HIGH){
    if (pos > 18) {
       pos-=3;
    }else{
      pos = 18;
      servoMotor.write(pos);
    }
  }else{
    if (pos < 180) {
       pos++;
    }
  }
  servoMotor.write(pos);
}

void setUmbral() {
  for (uint8_t i = 0; i < 200; i++) {
    umbralSensorT9 += touchRead(T9);
    umbralSensorT5 += touchRead(T5);
    umbralSensorT6 += touchRead(T6);
    umbralSensorT7 += touchRead(T7);
    delay(1);
  }
  umbralSensorT9 /= 200;
  umbralSensorT5 /= 200;
  umbralSensorT6 /= 200;
  umbralSensorT7 /= 200;

  umbralSensorT9 *= 0.5;
  umbralSensorT5 *= 0.5;
  umbralSensorT6 *= 0.5;
  umbralSensorT7 *= 0.5;
}

void updateTime(uint32_t seg) {
  timerAlarmWrite(My_timer, seg * 10000, true);
  // print in display
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  tft.begin(); //Inicializar la LCD
  tft.setTextColor(BLACK,CYAN);
  tft.fillScreen(CYAN);

  if (!rtc.begin()) {
   // Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  DateTime now = rtc.now();
  if (!rtc.isrunning()) {
    //Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  } else {
         
    rtc.adjust(DateTime(now.year(), now.month(), now.day(), 5, 59, 0));
  }
  tft.setCursor(10,10);
  tft.print(now.year());
  


  My_timer = timerBegin(0, 8000, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  updateTime(5);
  timerAlarmEnable(My_timer);  //Just Enable
  velocidad=12;

  setUmbral();
  tft.setCursor(15,40);
  tft.print("velocidad: "); 
  tft.setCursor(10,50);
  tft.print("Posicion");
  Serial.println("Umbrales");
  Serial.println(umbralSensorT9);
  Serial.println(umbralSensorT5);
  Serial.println(umbralSensorT6);
  Serial.println(umbralSensorT7);

  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
  servoMotor.write(pos);
}

void loop() {
  DateTime time = rtc.now();
  tft.setCursor(10,20);
  tft.print(time.timestamp(DateTime::TIMESTAMP_TIME));
  tft.setCursor(10,30);
  tft.print(time.timestamp(DateTime::TIMESTAMP_DATE));

  tft.setCursor(70,50);
  if (pos<10){
    tft.print("  ");
    tft.print(pos);
  }else if(pos<100){
    tft.print(" ");
    tft.print(pos);    
  }else{
    tft.print(pos);   
  }
  if (velocidad!=velAct){
    tft.setCursor(75,40);
    if((velocidad/10)>=1){
      tft.print(velocidad); 
    }else{
      tft.print(" ");
      tft.print(velocidad); 
    } 
    tft.print((char)248);
    tft.print("/h");   
     velAct=velocidad;
  }
    if(time.timestamp(DateTime::TIMESTAMP_TIME)<date){
      digitalWrite(LED, LOW);
      SensorT9 = touchRead(T9);
      SensorT5 = touchRead(T5);
      SensorT6 = touchRead(T6);
      SensorT7 = touchRead(T7);
      Serial.print("SensorT9 ");
      Serial.println(SensorT9);
    
    if (SensorT9 < umbralSensorT9 && SensorT9 > 5) {
      SensorT9 = touchRead(T9);
      if (SensorT9 < umbralSensorT9 && SensorT9 > 5){
        updateTime(4);
        //pos = 0;
        //servoMotor.write(pos);
        velocidad=15;
      }
      while (SensorT9 < umbralSensorT9) { SensorT9 = touchRead(T9); }
      delay(200);
    }
    if (SensorT5 < umbralSensorT5 && SensorT5 > 5 ) {
      updateTime(5);
      //pos = 18;
      //servoMotor.write(pos);
      while (SensorT5 < umbralSensorT5) { SensorT5 = touchRead(T5); }
      velocidad=12;
      delay(200);
    }
    if (SensorT6 < umbralSensorT6 && SensorT6 > 5) {
      updateTime(6);
      //pos = 30;
      //servoMotor.write(pos);
      while (SensorT6 < umbralSensorT6) { SensorT6 = touchRead(T6); }
      velocidad=10;
      delay(200);
    }
    if (SensorT7 < umbralSensorT7 && SensorT7 > 5) {
      updateTime(10);
      //pos = 54;
      //servoMotor.write(pos);
      while (SensorT7 < umbralSensorT7) { SensorT7 = touchRead(T7); }
      velocidad=6;
      delay(200);
    }
  }else{
    updateTime(1);
    velocidad = 3;
    digitalWrite(LED,HIGH);
  }

}
