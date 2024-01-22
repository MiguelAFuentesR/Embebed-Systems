/*
  Sensores :
  1. humedad relativa (valor en %)
  2. presión atmosférica (valor en mbar)

  3. temperatura (valor en °C)
  4. Velocidad_Actualizacion del viento (valor en m/s)
  5. cantidad de lluvia (valor en mm/h)
*/


//////////////////////////////////////////////
//        App Bluetooth usando RemoteXY     //
//////////////////////////////////////////////


// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLUETOOTH
#include <BluetoothSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "Lab4 Sistemas Embebidos"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 672 bytes
  { 255,1,0,57,2,153,2,16,30,4,131,5,89,46,21,6,1,12,88,83,
  101,110,115,111,114,32,52,0,131,4,89,19,21,6,2,12,8,83,101,110,
  115,111,114,32,49,0,129,0,8,0,52,4,0,1,69,115,116,97,99,105,
  195,179,110,32,77,101,116,101,111,114,111,108,195,179,103,105,99,97,32,85,
  68,0,66,0,38,9,9,21,4,2,26,129,0,4,13,19,5,2,146,82,
  101,108,97,116,105,118,97,0,129,0,71,17,4,5,2,24,37,0,67,1,
  49,15,20,5,4,24,26,101,129,0,249,8,22,5,2,146,72,117,109,101,
  100,97,100,0,129,0,253,8,19,5,4,64,80,114,101,115,105,195,179,110,
  32,0,71,56,29,8,25,25,3,0,73,95,135,0,0,0,0,0,0,200,
  66,0,0,160,65,0,0,32,65,0,0,0,64,39,0,129,0,246,7,29,
  5,5,106,84,101,109,112,101,114,97,116,117,114,97,0,66,131,22,14,36,
  13,5,2,24,129,0,74,15,6,5,5,8,194,176,32,67,0,129,0,249,
  7,23,5,3,238,86,101,108,111,99,105,100,97,100,0,129,0,3,12,23,
  5,3,238,100,101,108,32,118,105,101,110,116,111,0,72,4,30,9,20,20,
  2,95,26,189,39,0,0,0,0,0,0,200,66,0,0,0,0,67,1,57,
  16,13,6,2,24,26,101,131,4,89,54,21,6,3,12,88,83,101,110,115,
  111,114,32,53,0,129,0,70,15,12,5,4,24,109,98,97,114,0,67,1,
  60,14,13,6,5,24,26,101,67,1,58,14,13,6,3,24,26,101,67,1,
  52,16,13,6,1,24,26,101,129,0,73,14,6,5,3,8,109,47,115,0,
  129,0,254,7,23,5,1,6,67,97,110,116,105,100,97,100,32,100,101,0,
  129,0,10,11,14,5,1,6,76,108,117,118,105,97,0,66,1,29,12,21,
  16,1,193,26,129,0,72,17,8,5,1,8,109,109,47,104,0,131,4,89,
  28,21,6,4,12,8,83,101,110,115,111,114,32,50,0,131,4,89,37,21,
  6,5,12,8,83,101,110,115,111,114,32,51,0,129,0,1,13,28,5,4,
  64,65,116,109,111,115,102,195,169,114,105,99,97,0,68,17,237,33,100,28,
  2,8,36,129,0,247,27,22,5,0,255,72,105,115,116,111,114,105,99,111,
  58,0,68,17,244,33,93,28,4,8,36,68,17,238,33,98,28,5,8,36,
  68,17,238,33,98,28,1,8,36,68,17,237,33,99,28,3,8,36,4,128,
  71,3,30,5,0,164,26,129,0,73,9,3,2,0,24,83,101,103,0,129,
  0,71,0,14,3,0,240,84,97,115,97,32,65,99,116,32,58,32,0,129,
  0,96,9,3,2,0,24,83,101,103,0,67,1,87,255,8,4,0,24,26,
  11,129,0,96,0,6,3,0,24,32,83,101,103,0,67,1,67,8,5,3,
  0,24,26,11,67,1,90,8,5,3,0,24,26,11,129,0,37,6,10,2,
  4,24,49,48,48,48,32,109,98,97,114,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t Tasa_Actualizacion; // =0..100 slider position 

    // output variables
  int8_t Barra_Presion; // =0..100 level position 
  char Valor_Presion[101];  // string UTF8 end zero 
  float Barra_VelocidadViento;  // from 0 to 100 
  int8_t Barra_Temperatura; // =0..100 level position 
  float Barra_Humedad;  // from 0 to 100 
  char Valor_Humedad[101];  // string UTF8 end zero 
  char Valor_Temperatura[101];  // string UTF8 end zero 
  char Valor_Viento[101];  // string UTF8 end zero 
  char Valor_Lluvia[101];  // string UTF8 end zero 
  int8_t Barra_Lluvia; // =0..100 level position 
  float Graf_Humedad;
  float Graf_Atmosfera;
  float Graf_Temperatura;
  float Graf_LLuvia;
  float Graf_Viento;
  char Valor_Tiempo[11];  // string UTF8 end zero 
  char Valor_Tiempo_Minimo[11];  // string UTF8 end zero 
  char Valor_Tiempo_Maximo[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//          Aplicacion ThingSpeak          //
/////////////////////////////////////////////


// Definicion de Sensores
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

#define LED_B 2 //Define GPIO2
#define SW 14//Define GPIO14

// Definicion de Variables

double Sensor_Temperatura = 22.58;
double Sensor_Viento = 20.3;
double Sensor_Presion = 30.65;
double Sensor_Humedad = 40.2;
double Sensor_Lluvia  = 50.1;

//Variables Auxiliares
uint32_t t_actual;
bool Inicio_Bluetooth = true;
int test = 50;
int Tiempo = 5; //Tiempo de actualizacion en Segundos
int Tiempo_Min = 5; //5 Seg minimos
int Valor_Max_Tiempo = 60; // 60 Seg

//******************* TIMMER *******************************
//Variables Timmer
int Velocidad_Actualizacion ;
hw_timer_t *timer1 = NULL;

void IRAM_ATTR Int_Timer1() {
  if (test < 100) {
    Sensor_Viento++;
    Sensor_Lluvia++;
    test++;
  } else {
    Sensor_Viento = 0;
    Sensor_Lluvia = 0;
    test = 50;
  }
  Actualizar_Datos(); //Actualiza los Datos de la App Bluetooth
}

void setup()
{
  timer1 = timerBegin(1, 80, true); //Configura Timer 1 con preesc.x80 (=1MHz) y cambio por flanco de bajada
  Velocidad_Actualizacion = 5000000; // Actualizacion de datos cada 5 Segundos
  Activar_Timer();

  RemoteXY_Init ();
  Serial.begin(115200);

  //Inicializacion de Pines Sensores
  pinMode(LED_B, OUTPUT);
  Iniciar_Sensores();


  //Conexion  Wifi


  //Conexion Bluetooth
  Serial.print("Emparejando");
  digitalWrite(LED_B, HIGH);
  t_actual = millis();

}

void loop()
{

  //--------------- Inicializacion WiFi       -------------------



  //--------------- Inicializacion Bluetooth  -------------------

  RemoteXY_Handler ();
  if (!RemoteXY.connect_flag) {
    Serial.print('.');
    delay(1000);
  }
  if (RemoteXY.connect_flag && Inicio_Bluetooth) {
    Serial.println(' ');
    Serial.println("Bluetooth Conectado");
    digitalWrite(LED_B, LOW);
    Inicio_Bluetooth = false;
  }

  //--------------- Lectura de Valores Sensores -------------------


  Sensor_Temperatura = bme.readTemperature();
  // El sensor mide en Pascales por tanto =  1 pascal = 0.01 mbar
  Sensor_Presion = bme.readPressure()*0.01;
  Sensor_Humedad = bme.readHumidity();


  //------------ Actualizacion de Datos Bluetooth ------------------

  Tasa_Actualizacion();
  Activar_Timer();
  //Actualizar_Datos(); //Actualiza los Datos de la App Bluetooth
}

void Iniciar_Sensores() {
  Serial.println(F("BME280 test"));
  bool status;
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}
void Tasa_Actualizacion() {
  if (RemoteXY.Tasa_Actualizacion == 0) {
    Velocidad_Actualizacion = Tiempo_Min * 1000000;
    Tiempo = 5;
  } else {
    Velocidad_Actualizacion = (RemoteXY.Tasa_Actualizacion * Valor_Max_Tiempo * 10000); // Para ajustar el Timmer
    Tiempo = (int)(RemoteXY.Tasa_Actualizacion * 3 / 5);
  }
  itoa (Tiempo, RemoteXY.Valor_Tiempo, 10);
  itoa (Tiempo_Min, RemoteXY.Valor_Tiempo_Minimo, 10);
  itoa (Valor_Max_Tiempo, RemoteXY.Valor_Tiempo_Maximo, 10);
}
void Activar_Timer() {
  timerAttachInterrupt(timer1, Int_Timer1, true); //Hab. int del Timer 1
  timerAlarmWrite(timer1, Velocidad_Actualizacion, true);
  timerAlarmEnable(timer1); //Habilitar el Timer 1
}
void Desactivar_Timer() {
  timerRestart(timer1);
  timerAlarmDisable(timer1); //Habilitar el Timer 1
}
void Actualizar_Datos() {

  //Actualizacion de los Strings
  dtostrf(Sensor_Humedad, 0, 2, RemoteXY.Valor_Humedad);
  dtostrf(Sensor_Temperatura, 0, 2, RemoteXY.Valor_Temperatura);
  dtostrf(Sensor_Viento, 0, 2, RemoteXY.Valor_Viento);
  dtostrf(Sensor_Lluvia, 0, 2, RemoteXY.Valor_Lluvia);
  dtostrf(Sensor_Presion, 0, 2, RemoteXY.Valor_Presion);

  //Actualizacion de la Barra de Humedad Relativa %
  RemoteXY.Barra_Humedad =   Sensor_Humedad;
  //Actualizacion de la Barra de Temperatura  Grados Celcius
  RemoteXY.Barra_Temperatura  =  Sensor_Temperatura;
  //Actualizacion de la Barra de Viento
  RemoteXY.Barra_VelocidadViento  =  Sensor_Viento;
  //Actualizacion de la Barra de Lluvia
  RemoteXY.Barra_Lluvia = (int)(Sensor_Lluvia) ;
  //Actualizacion de la Barra de Presion
  RemoteXY.Barra_Presion = (int)(Sensor_Presion/10) ; //Escalarlo para mostrarlo de una escala de 0 - 100 

  // Actualizar las Graficas
  Actualizar_Graficas();
}
void Actualizar_Graficas() {

  //Añadir Valores al Historico
  RemoteXY.Graf_Humedad = Sensor_Humedad;
  RemoteXY.Graf_Atmosfera = Sensor_Presion;
  RemoteXY.Graf_Temperatura = Sensor_Temperatura;
  RemoteXY.Graf_LLuvia = Sensor_Lluvia;
  RemoteXY.Graf_Viento = Sensor_Viento;

}
