#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED)||!defined(CONFIG_BLUEDROID_ENABLED) //Verificar Bluetooth habilitado
#error Bluetooth deshabilitado!!
#endif

BluetoothSerial SerialBT; //Crear objeto "SerialBT"

#define LED_B 2 //Define GPIO2
#define LED 33 //Define GPIO33

uint32_t t_actual;
char dataIn;
String Mensaje="";

void setup() {
  Serial.begin(115200);
  pinMode(LED_B,OUTPUT);
  pinMode(LED,OUTPUT);
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
  if(Serial.available()){
    SerialBT.write(Serial.read());
  }

  if(SerialBT.available()){ //Verificar disponibilidad de dato en el Bluetooth
    dataIn=SerialBT.read(); //Leer dato recibido
    if(dataIn!='\n'){ //Si dato recibido es diferente al código final del Enter lo almacena
      Mensaje+=String(dataIn); //Se va generando el string con los datos recibidos
    }else{
      Mensaje="";
    }
    Serial.write(dataIn);
  }
  if(Mensaje=="LED_On"){
    digitalWrite(LED,HIGH);
  }
  if(Mensaje=="LED_Off"){
    digitalWrite(LED,LOW);
  }

  if(millis()-t_actual>=2000){ //Cada 2s envia al BL y al monitor serie el valor del ADC
    t_actual=millis();  
    uint16_t volt=analogRead(34);
    SerialBT.print(volt*3.3/4095.0);
    SerialBT.println('v');  
    Serial.print(volt*3.3/4095.0);
    Serial.println('v');
    digitalWrite(LED,!digitalRead(LED_B));
  }
}
