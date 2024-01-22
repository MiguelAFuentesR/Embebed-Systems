#include <WiFi.h>
#include "ThingSpeak.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"

//Credenciales de la red WiFi a conectarse:
const char* ssid="POCO X3 GT";
const char* password="15jcamargo";

unsigned long Channel_ID=1517016; //Número del canal en ThingSpeak
const char* WriteAPIKey="7DROFJB9GY6PJH7B"; //Api Key de escritura del canal en ThingSpeak

#define LED 2 //Define GPIO2

const uint16_t ledRefresh=1;
const uint16_t dataRefresh=20; //Intervalo de refresco de los datos (en segundos)

uint16_t contadorSegundos;

WiFiClient client;
Adafruit_AM2320 am2320=Adafruit_AM2320();

void setup() {
  Serial.begin(115200);
  
  Serial.println("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid,password); //Conectarse a la red WiFi con ssid y contraseña indicada
  while(WiFi.status()!=WL_CONNECTED){ //Esperar hasta que se realice la conexión con el router
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");

  ThingSpeak.begin(client); //Iniciar cliente en ThingSpeak
  am2320.begin();

  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);  
  contadorSegundos=0;
}

void loop() {
  if(WiFi.status()==WL_CONNECTED&&contadorSegundos<=0){ //Si está conectado...
    contadorSegundos=dataRefresh;
    float t=am2320.readTemperature();
    float h=am2320.readHumidity();
    if(isnan(t)||isnan(h)){
      Serial.println("Error de comunicación con el sensor AM2320");
    }else{
      Serial.print("Temperatura: "); Serial.println(t,1);
      Serial.print("Humedad: "); Serial.println(h,1);
      ThingSpeak.setField(1,t);  //Establecer el campo 1 en Canal de ThingSpeak con valor de temperatura
      ThingSpeak.setField(2,h);  //Establecer el campo 2 en Canal de ThingSpeak con valor de humedad
      int httpCode=ThingSpeak.writeFields(Channel_ID,WriteAPIKey); //Enviar los datos al servidor de ThingSpeak
      if(httpCode==200){
        Serial.println("Canal actualizado!!");
      }else{
        Serial.println("Problema al actualizar el canal. Codigo de error HTTP: "+String(httpCode));
      }
    }
  }
  delay(ledRefresh*1000);
  digitalWrite(LED,!digitalRead(LED));
  contadorSegundos-=ledRefresh;
}
