#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED)||!defined(CONFIG_BLUEDROID_ENABLED) //Verificar Bluetooth habilitado
#error Bluetooth deshabilitado!! Por favor realice la habilitación correspondiente
#endif

BluetoothSerial SerialBT; //Crear objeto "SerialBT"

#define LED 2 //Define GPIO2
#define LED_R 25 //Define GPIO25
#define LED_G 33 //Define GPIO33
#define LED_B 32 //Define GPIO32

#define PWMResolution 8 //Resolución de 8 bits (valor entre 1 y 16)
#define PWMFreq 5000 //Frecuencia del PWM a 5KHz

uint32_t t_actual;
char dataIn;
String Mensaje="";

void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  SerialBT.begin("MyESP32"); //Inicializar y asignar nombre al Bluetooth del ESP32
  Serial.println("El Bluetooth del ESP32 inició correctamente!!");
  Serial.print("Emparejando");
  digitalWrite(LED,HIGH);
  while(SerialBT.read()!='*'){
    Serial.print('.');
    delay(1000);
  }
  Serial.println(' ');
  Serial.println("Conectado");
  digitalWrite(LED,LOW);
  ledcSetup(0,PWMFreq,PWMResolution); //Configurar el canal 0 del PWM
  ledcAttachPin(LED_R,0); //Asociar el pin LED_R al canal 0 del PWM
  ledcWrite(0,0xFF); //Valor inicial del ciclo útil del canal 0 del PWM
  ledcSetup(1,PWMFreq,PWMResolution); //Configurar el canal 1 del PWM
  ledcAttachPin(LED_G,1); //Asociar el pin LED_G al canal 1 del PWM
  ledcWrite(1,0xFF); //Valor inicial del ciclo útil del canal 1 del PWM
  ledcSetup(2,PWMFreq,PWMResolution); //Configurar el canal 2 del PWM
  ledcAttachPin(LED_B,2); //Asociar el pin LED_B al canal 2 del PWM
  ledcWrite(2,0xFF); //Valor inicial del ciclo útil del canal 2 del PWM
  randomSeed(255);
  t_actual=millis();
}

void loop() {
  if(SerialBT.available()){//Verificar disponibilidad del Bluetooth
    dataIn=SerialBT.read(); //Almacenar dato recibido
    if(dataIn!='\n'){ //Si dato recibido es diferente al retorno de linea (LF) lo almacena en un string
      Mensaje+=String(dataIn); //Se va generando el String con los datos recibos
    }else{
      Mensaje="";
    }
    Serial.write(dataIn);
  }
  if(Mensaje=="Rojo"){
    ledcWrite(0,0xFF); //Actualizar el ciclo util del canal 0 del PWM
    ledcWrite(1,0); //Actualizar el ciclo util del canal 1 del PWM
    ledcWrite(2,0); //Actualizar el ciclo util del canal 2 del PWM
  }
  if(Mensaje=="Azul"){
    ledcWrite(0,0); //Actualizar el ciclo util del canal 0 del PWM
    ledcWrite(1,0); //Actualizar el ciclo util del canal 1 del PWM
    ledcWrite(2,0xFF); //Actualizar el ciclo util del canal 2 del PWM
  }
  if(Mensaje=="Verde"){
    ledcWrite(0,0); //Actualizar el ciclo util del canal 0 del PWM
    ledcWrite(1,0xFF); //Actualizar el ciclo util del canal 1 del PWM
    ledcWrite(2,0); //Actualizar el ciclo util del canal 2 del PWM
  }
  if(Mensaje=="Amarillo"){
    ledcWrite(0,0xFF); //Actualizar el ciclo util del canal 0 del PWM
    ledcWrite(1,0xFF); //Actualizar el ciclo util del canal 1 del PWM
    ledcWrite(2,0); //Actualizar el ciclo util del canal 2 del PWM
  }
  if(Mensaje=="Cyan"){
    ledcWrite(0,0); //Actualizar el ciclo util del canal 0 del PWM
    ledcWrite(1,0xFF); //Actualizar el ciclo util del canal 1 del PWM
    ledcWrite(2,0xFF); //Actualizar el ciclo util del canal 2 del PWM
  }
  if(Mensaje=="Magenta"){
    ledcWrite(0,0xFF); //Actualizar el ciclo util del canal 0 del PWM
    ledcWrite(1,0); //Actualizar el ciclo util del canal 1 del PWM
    ledcWrite(2,0xFF); //Actualizar el ciclo util del canal 2 del PWM
  }
  if(Mensaje=="Aleatorio"){
    uint8_t a=random(255);
    Serial.print("\r\n"+String(a)+',');
    ledcWrite(0,a); //Actualizar el ciclo util del canal 0 del PWM
    a=random(255);
    Serial.print(String(a)+',');
    ledcWrite(1,a); //Actualizar el ciclo util del canal 1 del PWM
    a=random(255);
    Serial.print(a);
    ledcWrite(2,a); //Actualizar el ciclo util del canal 2 del PWM
  }
  if(millis()-t_actual>=1000){ //Una vez por segundo conmuta el estado del LED de la tarjeta DEVKIT-V1
    t_actual=millis();
    digitalWrite(LED,!digitalRead(LED));
  } 
}
