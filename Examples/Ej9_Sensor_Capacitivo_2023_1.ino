#define LED0 2
#define LED1 25
#define LED2 33
#define LED3 32

uint8_t SensorT4,SensorT5,SensorT6,SensorT7;

void setup() {
  Serial.begin(115200);
  pinMode(LED0,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
}

void loop() {
  SensorT4=touchRead(T4);
  SensorT5=touchRead(T5);
  SensorT6=touchRead(T6);
  SensorT7=touchRead(T7);
  Serial.print("Sensor T4:");
  Serial.println(SensorT4);
  Serial.print("Sensor T5:");
  Serial.println(SensorT5);
  Serial.print("Sensor T6:");
  Serial.println(SensorT6);
  Serial.print("Sensor T7:");
  Serial.println(SensorT7);
  if(SensorT4<30&&SensorT4>5){
    digitalWrite(LED0,!digitalRead(LED0));
    Serial.println("Sensor T4 oprimido");
    while(SensorT4<30&&SensorT4>5){SensorT4=touchRead(T4);}
    delay(200);
  }
  if(SensorT5<30&&SensorT5>5){
    digitalWrite(LED1,!digitalRead(LED1));
    Serial.println("Sensor T5 oprimido");
    while(SensorT5<30&&SensorT5>5){SensorT5=touchRead(T5);}
    delay(200);
  }
  if(SensorT6<30&&SensorT6>5){
    digitalWrite(LED2,!digitalRead(LED2));
    Serial.println("Sensor T6 oprimido");
    while(SensorT6<30&&SensorT6>5){SensorT6=touchRead(T6);}
    delay(200);
  }
  if(SensorT7<30&&SensorT7>5){
    digitalWrite(LED3,!digitalRead(LED3));
    Serial.println("Sensor T7 oprimido");
    while(SensorT7<30&&SensorT7>5){SensorT7=touchRead(T7);}
    delay(200);
  }
}
