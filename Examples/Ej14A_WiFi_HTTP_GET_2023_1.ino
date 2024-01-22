#include <WiFi.h>
#include <HTTPClient.h>

//Credenciales de la red WiFi a conectarse:
const char* ssid="POCO X3 GT"; //"Invitados_UDistrital";
const char* password="15jcamargo"; //"1nv1tad0s";

#define LED_B 2 //GPIO2

const char* url="https://www.worldometers.info/coronavirus/";
const uint16_t ledRefresh=1;
const uint16_t dataRefresh=10; //Intervalo de refresco de los datos (en segundos);

String casosTotales,muertes,recuperados,casosActivos,casosCerrados;
uint16_t contadorSegundos;

void setup() {
  Serial.begin(115200);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_B,HIGH);

  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid,password); //Conectarse a la red WiFi con ssid y la contraseña indicadas
  while(WiFi.status()!=WL_CONNECTED){ //Esperar hasta que se realice la conexión con el router
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("Dirección IP asignada: ");
  Serial.println(WiFi.localIP()); //Dirección IP asignada por el router
  digitalWrite(LED_B,LOW);
  contadorSegundos=0;
}

void loop() {
  if(WiFi.status()==WL_CONNECTED&&contadorSegundos<=0){
    contadorSegundos=dataRefresh;
    HTTPClient http; //Se crea un objeto asociado a un cliente HTTP llamado "http"
    http.begin(url); //Inicia el cliente HTTP con la url a accesar
    int httpCodigoRespuesta=http.GET(); //Lee código de respuesta generado por la url
    if(httpCodigoRespuesta>0){ //Verifica si hay un código de respuesta válido
      WiFiClient * stream=http.getStreamPtr();
      Serial.print("Código de respuesta HTTP: ");
      Serial.println(httpCodigoRespuesta);
      if(stream->find("maincounter-number")){
        stream->find("span");
        stream->find(">");
        casosTotales=stream->readStringUntil('<');
        Serial.print("Casos totales: ");
        Serial.println(casosTotales);

        stream->find("maincounter-number");
        stream->find("span");
        stream->find(">");
        muertes=stream->readStringUntil('<');
        Serial.print("Muertes: ");
        Serial.println(muertes);

        stream->find("maincounter-number");
        stream->find("span");
        stream->find(">");
        recuperados=stream->readStringUntil('<');
        Serial.print("Recuperados: ");
        Serial.println(recuperados);

        stream->find("number-table-main");
        stream->find(">");
        casosActivos=stream->readStringUntil('<');
        Serial.print("Casos activos: ");
        Serial.println(casosActivos);

        stream->find("number-table-main");
        stream->find(">");
        casosCerrados=stream->readStringUntil('<');
        Serial.print("Casos cerrados: ");
        Serial.println(casosCerrados);  
      }
    }else{
      Serial.println("Error en solicitud HTTP");
      Serial.print("Código de error");
      Serial.println(httpCodigoRespuesta);
    }
    http.end();
    Serial.println("");
  }
  delay(ledRefresh*1000);
  digitalWrite(LED_B,!digitalRead(LED_B));
  contadorSegundos=-ledRefresh;
}
