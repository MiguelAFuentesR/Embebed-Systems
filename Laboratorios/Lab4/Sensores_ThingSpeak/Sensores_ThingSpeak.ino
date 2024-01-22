/////////////////////////////////////////////
//          Aplicacion ThingSpeak          //
/////////////////////////////////////////////

#include <WiFi.h>
#include "ThingSpeak.h"

//Credenciales de la red WiFi a conectarse:
const char* ssid = "UDNet_Academia";
const char* password = "6Lj3P_UD_$";


//const char* ssid = "ADM_UDistrital";
//const char* password = "PKFJuurjf986_$";

//const char* ssid = "Invitados_UDistrital";
//const char* password = "1nv1tad0s"
/*
  const char* ssid="Familia Ramirez";
  const char* password="FamiliaRamirezFuentes2020";
*/
unsigned long Channel_ID = 2128507; //Número del canal en ThingSpeak
const char* WriteAPIKey = "1B9QMCDN2HQUEUMX"; //Api Key de escritura del canal en ThingSpeak
WiFiClient client;

// Definicion de Sensores
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
#define LED 2 //Define GPIO2

const uint16_t ledRefresh = 1;
const uint16_t dataRefresh = 20; //Intervalo de refresco de los datos (en segundos)

uint16_t contadorSegundos;

float Sensor_Temperatura = 22.58;
float Sensor_Viento = 20.3;
float Sensor_Presion = 30.65;
float Sensor_Humedad = 40.2;
float Sensor_Lluvia  = 50.1;

void setup() {
  Serial.begin(115200);

  Serial.println("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //Conectarse a la red WiFi con ssid y contraseña indicada
  while (WiFi.status() != WL_CONNECTED) { //Esperar hasta que se realice la conexión con el router
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");

  ThingSpeak.begin(client); //Iniciar cliente en ThingSpeak


  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  contadorSegundos = 0;

  Iniciar_Sensores();
}

void loop() {


  //--------------- Lectura de Valores Sensores -------------------


  Sensor_Temperatura = bme.readTemperature();
  // El sensor mide en Pascales por tanto =  1 pascal = 0.01 mbar
  Sensor_Presion = bme.readPressure()*0.01;
  Sensor_Humedad = bme.readHumidity();
  
  Datos_ThingSpeak();

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

void Datos_ThingSpeak() {
  if (WiFi.status() == WL_CONNECTED && contadorSegundos <= 0) { //Si está conectado...
    contadorSegundos = dataRefresh;
    ThingSpeak.setField(1, Sensor_Humedad); //Establecer el campo 1 en Canal de ThingSpeak -- > Humedad Relativa
    ThingSpeak.setField(2, Sensor_Presion); //Establecer el campo 2 en Canal de ThingSpeak -- > Presión Atmosférica
    ThingSpeak.setField(3, Sensor_Temperatura); //Establecer el campo 3 en Canal de ThingSpeak -- > Temperatura
    ThingSpeak.setField(4, Sensor_Viento); //Establecer el campo 4 en Canal de ThingSpeak -- > Velocidad del viento
    ThingSpeak.setField(5, Sensor_Viento); //Establecer el campo 5 en Canal de ThingSpeak -- > Cantidad de lluvia

    int httpCode = ThingSpeak.writeFields(Channel_ID, WriteAPIKey); //Enviar los datos al servidor de ThingSpeak
    if (httpCode == 200) {
      Serial.println("Canal actualizado!!");
    } else {
      Serial.println("Problema al actualizar el canal. Codigo de error HTTP: " + String(httpCode));
    }
  }
  delay(ledRefresh * 1000);
  digitalWrite(LED, !digitalRead(LED));
  contadorSegundos -= ledRefresh;
}
