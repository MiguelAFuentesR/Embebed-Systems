#include "BluetoothSerial.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"

#if !defined(CONFIG_BT_ENABLED)||!defined(CONFIG_BLUEDROID_ENABLED) //Verificar Bluetooth habilitado
#error Bluetooth deshabilitado!! Por favor realice la habilitación correspondiente
#endif

BluetoothSerial SerialBT; //Crear objeto "SerialBT"
Adafruit_AM2320 am2320=Adafruit_AM2320(); //Crear el objeto "am2320" en los pines I2C_SDA=GPIO21 e I2C_SCL=GPIO22

#define LED_B 2 //Define GPIO2

uint32_t t_actual;

void setup() {
  Serial.begin(115200);
  pinMode(LED_B,OUTPUT);
  am2320.begin();
  SerialBT.begin("MyESP32"); //Inicializar y asignar nombre al Bluetooth del ESP32
  Serial.println("El Bluetooth del ESP32 inició correctamente!!");
  Serial.print("Emparejando");
  digitalWrite(LED_B,HIGH);
  while(SerialBT.read()!='*'){
    Serial.print('.');
    delay(1000);
  }
  Serial.println(' ');
  Serial.println("Conectado");
  digitalWrite(LED_B,LOW);
  t_actual=millis();
}

void loop() {
  if(millis()-t_actual>=2000){
    t_actual=millis();
    float t=am2320.readTemperature(); //Leer el valor de la temperatura actual
    float h=am2320.readHumidity(); //Leer el valor de la humedad actual
    if(isnan(t)||isnan(h)){ //Verificar si alguna de las variables tiene un valor vacio
      Serial.println("Error de comunicación con el sensor AM2320!!");
      SerialBT.println("Error de comunicación con el sensor AM2320!!"); 
    }else{
      Serial.print("Temp: ");
      Serial.print(t,1);
      Serial.println("°C");
      Serial.print("Hum: ");
      Serial.print(h,1);
      Serial.println('%');
      SerialBT.print('E');
      SerialBT.print(t);
      SerialBT.print(',');
      SerialBT.println(h);
      digitalWrite(LED_B,!digitalRead(LED_B));
    }
  }

}
