#include <WiFi.h>
#include <HTTPClient.h>

//Credenciales de la red WiFi a conectarse:
const char* ssid="POCO X3 GT";
const char* password="15jcamargo";

#define LED 2 //Define GPIO2

const char* host="api.thingspeak.com"; //Dirección del servidor de ThingSpeak
const int httpPortRead=80; 
const char* url1="/apps/thinghttp/send_request?api_key=LCY7AAOML067VXUO";
const char* url2="/apps/thinghttp/send_request?api_key=OKYBIVAI659YD0BX";
const char* url3="/apps/thinghttp/send_request?api_key=R6VIUC72TGGY77A7";

const uint16_t ledRefresh=1;
const uint16_t dataRefresh=20; //Intervalo de refresco de los datos (en segundos)

String casosTotales,muertes,recuperados,casosActivos,casosCerrados,dataRaw;
uint16_t contadorSegundos,remover;

WiFiClient client; //Crear cliente WiFi
HTTPClient http; //Crear cliente http

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
  Serial.print("Dirección IP asignada: ");
  Serial.println(WiFi.localIP()); //Dirección IP asignada al ESP32 por el router

  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);  
  contadorSegundos=0;
}

void loop() {
  if(WiFi.status()==WL_CONNECTED&&contadorSegundos<=0){ //Si está conectado...
    contadorSegundos=dataRefresh;

    if(http.begin(host,httpPortRead,url1)){ //Se conecta y verifica conexión al host (url1)
      int httpCode=http.GET();
      if(httpCode>0){
        if(httpCode==HTTP_CODE_OK||httpCode==HTTP_CODE_MOVED_PERMANENTLY){ //Si código de respuesta es 200 o 301...
          dataRaw=http.getString();

          Serial.print("Datos recibidos de la URL 1: ");
          Serial.println(dataRaw);
        }else{
          Serial.printf("Error en solicitud HTTP con URL 1: %s\n",http.errorToString(httpCode).c_str());
        }
      }else{
        Serial.println("No hubo conexión HTTP con la URL 1");
      }
    }
    http.end();

    if(http.begin(host,httpPortRead,url2)){ //Se conecta y verifica conexión al host (url2)
      int httpCode=http.GET();
      if(httpCode>0){
        if(httpCode==HTTP_CODE_OK||httpCode==HTTP_CODE_MOVED_PERMANENTLY){ //Si código de respuesta es 200 o 301...
          dataRaw=http.getString();

          Serial.print("Datos recibidos de la URL 2: ");
          Serial.println(dataRaw);
        }else{
          Serial.printf("Error en solicitud HTTP con URL 2: %s\n",http.errorToString(httpCode).c_str());
        }
      }else{
        Serial.println("No hubo conexión HTTP con la URL 2");
      }
    }
    http.end();

    if(http.begin(host,httpPortRead,url3)){ //Se conecta y verifica conexión al host (url3)
      int httpCode=http.GET();
      if(httpCode>0){
        if(httpCode==HTTP_CODE_OK||httpCode==HTTP_CODE_MOVED_PERMANENTLY){ //Si código de respuesta es 200 o 301...
          dataRaw=http.getString();

          Serial.print("Datos recibidos de la URL 3: ");
          Serial.println(dataRaw);
        }else{
          Serial.printf("Error en solicitud HTTP con URL 3: %s\n",http.errorToString(httpCode).c_str());
        }
      }else{
        Serial.println("No hubo conexión HTTP con la URL 3");
      }
    }
    http.end();
    
  }
  delay(ledRefresh*1000);
  digitalWrite(LED,!digitalRead(LED));
  contadorSegundos-=ledRefresh;
}
