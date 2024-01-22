#include <WiFi.h>

//Credenciales de la red WiFi a conectar:
const char* ssid="Invitados_UDistrital";
const char* password="1nv1tad0s";

WiFiServer server(80); //Establecer nímero del puerto del servidor Web asignado al objeto "server"

String header; //Almacena solicitud HTTP

String Estado_LED_B="Off"; //Almacena el estado actual del LED_B
String Estado_LED_R="Off"; //Almacena el estado actual del LED_R

#define LED_B 2 //Define GPIO2
#define LED_R 25 //Define GPIO25

uint32_t currentTime,previousTime;
const long timeoutTime=2000;

void setup() {
  Serial.begin(115200);
  pinMode(LED_B,OUTPUT);
  pinMode(LED_R,OUTPUT);
  digitalWrite(LED_B,LOW);
  digitalWrite(LED_R,LOW);

  currentTime=millis();
  previousTime=0;

  Serial.println("Conectando a "+String(ssid));
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){ //Esperar hasta que se realice la conexión a la red WiFi
    delay(500);
    Serial.print('.');  
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("Dirección IP asignada: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client=server.available(); //Escuchar a los clientes entrantes
  if(client){
    currentTime=millis();
    previousTime=currentTime;
    Serial.println("Nuevo cliente");
    String dataIn=""; //Utilizada para almacenar los datos entrantes del cliente
    while(client.connected()&&currentTime-previousTime<=timeoutTime){ //Mientras el cliente esté conectado...
      currentTime=millis();
      if(client.available()){
        char c=client.read(); //Leer byte entrante
        Serial.write(c);
        header+=c;
        if(c=='\n'){ //Si dato es final de Enter, implica final de la petición HTTP del cliente y se debe enviar respuesta
          if(dataIn.length()==0){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if(header.indexOf("GET /Azul/on")>=0){
              Serial.println("Estado Actual LED Azul: On");
              Estado_LED_B="On";
              digitalWrite(LED_B,HIGH);
            }else if (header.indexOf("GET /Azul/off")>=0){
              Serial.println("Estado Actual LED Azul: Off");
              Estado_LED_B="Off";
              digitalWrite(LED_B,LOW);
            }else if(header.indexOf("GET /Rojo/on")>=0){
              Serial.println("Estado Actual LED Rojo: On");
              Estado_LED_R="On";
              digitalWrite(LED_R,HIGH);
            }else if (header.indexOf("GET /Rojo/off")>=0){
              Serial.println("Estado Actual LED Rojo: Off");
              Estado_LED_R="Off";
              digitalWrite(LED_R,LOW);
            }

            //Mostrar la página Web HTML embebida en el ESP32
            //La página Web se envía al cliente utilizando la función client.println()
            //Se debe introducir como argumento lo que se quiera enviar a cliente

            client.println("<!DOCTYPE html><html>"); //Indica al cliente que se está enviando HTML
            client.println("<head<meta name=\"viewport\" content=\"device-width,initial-scale=1\">"); //Hacer que la página Web responda a cualquier navegador Web
            client.println("<link rel=\"icon\" href=\"data:,\">"); //Enviar peticiones en el favicon

            //Texto CSS para darle apariencia a los botones utilizados en la página Web
            //Se elige fuente Helvetica, el contenido se muestra como un bloque y alineado al centro
            client.println("<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            //Se asigna color Azul (#3B83BD) al primer botón, sin borde, texto en color blanco y tamaño 16px 40px
            client.println(".button {background-color: #3B83BD; border: none; color: white; padding: 16px 40px;");
            //Se establece el text-decoration a none, tamaño de fuente 30px, margen 2px y cursor a un puntero
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button1 {background-color: #AF4C50;}"); //Asigna color rojo al segundo boton
            client.println(".button2 {background-color: #555555;}</style></head>"); //Asigna color gris al botón de apagado
            
            client.println("<body><h1><font color=#FF00FF>ESP32 STA Web Server</font></h1>"); //Titulo de la página Web
            client.println("<p>Estado Actual LED Azul: "+ Estado_LED_B + "</p>"); //Muestra el estado actual del boton Azul
            if(Estado_LED_B=="Off"){
              client.println("<p><a href=\"/Azul/on\"><button class=\"button\">ON</button></a></p>");
            }else{
              client.println("<p><a href=\"/Azul/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p><br/></p>"); //Enviar un Enter
            client.println("<p>Estado Actual LED Rojo: "+ Estado_LED_R + "</p>"); //Muestra el estado actual del boton Rojo
            if(Estado_LED_R=="Off"){
              client.println("<p><a href=\"/Rojo/on\"><button class=\"button button1\">ON</button></a></p>");
            }else{
              client.println("<p><a href=\"/Rojo/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p><br/></p>"); //Enviar un Enter
            client.println("</body></html>");
            
            client.println("<p><br/></p>");
            break; //Salir del bucle while
          }else{ //Si se tiene una nueva linea, se borra dataIn
            dataIn="";
          }  
        }else if(c!='\r'){
          dataIn+=c;
        }
      }
    }
    header="";
    client.stop();
    Serial.println("Cliente desconectado");
    Serial.println("");
  }
}
