#include <WiFi.h>
#include <SPI.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h>

//Credenciales de la red WiFi a conectarse:
const char* ssid="Invitados_UDistrital";
const char* password="1nv1tad0s";

WiFiServer server(80); //Establecer el número del puerto del servidor Web

String header; //Variable para almacenar la solicitud HTTP

//Variables auxiliares para almacenar el estado actual de cada LED
String Estado_LED_R="up";
String Estado_LED_G="up";
String Estado_LED_B="up";

#define LED_R 25 //Define GPIO25
#define LED_G 33 //Define GPIO33
#define LED_B 32 //Define GPIO32

//Pin RESET conectado a Vcc (+3.3v)
//Pin LED conectado a +3.3v
#define CS 5 //CS0
#define DC 3 //A0
#define MOSI 23 //SDA
#define SCK 18 //CLK

TFT_ILI9163C tft=TFT_ILI9163C(CS,DC); //Se crea objeto de nombre tft

#define PWMResolution 8 //Resolución de 8 bits (valor entre 1 y 16)
#define PWMFreq 5000 //Frecuencia del PWM a 5KHz

uint32_t currentTime=millis();
uint32_t previousTime=0;
const long timeoutTime=2000;

uint8_t contR,contG,contB;


void setup() {
  Serial.begin(115200);
  
  ledcSetup(0,PWMFreq,PWMResolution); //Configurar canal 0 del PWM
  ledcAttachPin(LED_R,0); //Asociar el pin LED_R al canal 0 del PWM
  ledcSetup(1,PWMFreq,PWMResolution); //Configurar canal 1 del PWM
  ledcAttachPin(LED_G,1); //Asociar el pin LED_G al canal 1 del PWM
  ledcSetup(2,PWMFreq,PWMResolution); //Configurar canal 2 del PWM
  ledcAttachPin(LED_B,2); //Asociar el pin LED_B al canal 2 del PWM

  Serial.println("Conectando a");
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
  server.begin();

  contR=0; contG=0; contB=0;
  ledcWrite(0,contR); //Ciclo util inicial para el LED Rojo
  ledcWrite(1,contG); //Ciclo util inicial para el LED Verde
  ledcWrite(2,contB); //Ciclo util inicial para el LED Azul

  tft.begin();
  tft.fillScreen(0); //Envia a la LCD el color en formato RGB565
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

            //Controla el valor del PWM de cada uno de los LEDs
            if(header.indexOf("GET /Rojo/up")>=0){
              Serial.println("Incrementa color Rojo");
              Estado_LED_R="up";
              contR++;
              ledcWrite(0,contR);
            }else if (header.indexOf("GET /Rojo/down")>=0){
              Serial.println("Decrementa color Rojo");
              Estado_LED_R="down";
              contR--;
              ledcWrite(0,contR);
            }else if(header.indexOf("GET /Verde/up")>=0){
              Serial.println("Incrementa color Verde");
              Estado_LED_G="up";
              contG++;
              ledcWrite(1,contG);
            }else if (header.indexOf("GET /Verde/down")>=0){
              Serial.println("Decrementa color Verde");
              Estado_LED_G="down";
              contG--;
              ledcWrite(1,contG);
            }if(header.indexOf("GET /Azul/up")>=0){
              Serial.println("Incrementa color Azul");
              Estado_LED_B="up";
              contB++;
              ledcWrite(2,contB);
            }else if (header.indexOf("GET /Azul/down")>=0){
              Serial.println("Decrementa color Azul");
              Estado_LED_B="down";
              contB--;
              ledcWrite(2,contB);
            }

            //Mostrar la página Web HTML embebida en el ESP32
            //La página Web se envía al cliente utilizando la función client.println()
            //Se debe introducir como argumento lo que se quiera enviar a cliente

            client.println("<!DOCTYPE html><html>"); //Indica al cliente que se está enviado HTML
            client.println("<head<meta name=\"viewport\" content=\"device-width,initial-scale=1\">"); //Hacer que la página Web responda a cualquier navegador Web
            client.println("<link rel=\"icon\" href=\"data:,\">"); //Evitar peticiones en el favicon

            //Texto CSS para darle apariencia a los botones utilizados en la página Web
            //Se elige fuente Helvetica, el contenido se muestra como un bloque y alineado al centro
            client.println("<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            //Se asigna a todos los botones los siguientes parámetros:
            //sin borde, texto en color blanco y tamaño 16px 2px
            client.println(".button { border: none; color: white; padding: 16px 2px; display: inline-block; border-radius: 12px");
            //Se establece el text-decoration a none, tamaño de fuente 25px, margen 4px x 8px, ancho 92px y cursor a un puntero
            client.println("text-decoration: none; font-size: 25px; margin: 4px 8px; width: 92px; cursor: pointer;}");

            //Se asigna color Rojo (#D1213D) al primer botón, con las propiedades definidas anteriormente
            client.println(".button1 {background-color: #D1213D;}");
            //Se asigna color Verde (#4CAF50) al segundo botón, con las propiedades definidas anteriormente
            client.println(".button2 {background-color: #4CAF50;}");
            //Se asigna color Azul (#3B83BD) al tercer botón, con las propiedades definidas anteriormente
            client.println(".button3 {background-color: #3B83BD;}</style></head>");
            
            client.println("<body><h1><font color=#FF00FF>ESP32 Station</font>"); //Titulo de la página Web
            client.println("<font color=#FF0000>R</font><font color=#00FF00>G</font><font color=#0000FF>B</font>");
            client.println("<font color=#FF00FF>Web Server</font></h1>");
            client.println("<br/>");

            client.println("<a href=\"/Rojo/up\"><button class=\"button button1\">UP</button></a>");
            client.println("<a href=\"/Verde/up\"><button class=\"button button2\">UP</button></a>");
            client.println("<a href=\"/Azul/up\"><button class=\"button button3\">UP</button></a>");
            client.println("<br/>");
            client.println("<a href=\"/Rojo/down\"><button class=\"button button1\">DOWN</button></a>");
            client.println("<a href=\"/Verde/down\"><button class=\"button button2\">DOWN</button></a>");
            client.println("<a href=\"/Azul/down\"><button class=\"button button3\">DOWN</button></a>");
            client.println("<br/>");

            client.println("<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            //Se asigna a todos los botones los siguientes parámetros:
            //color de fondo blanco, sin borde, texto en color negro y tamaño 8px 2px
            client.println(".button4 { background-color: white; border: none; color: black; padding: 8px 2px; display: inline-block;");
            //Se establece el text-decoration a none, tamaño de fuente 18px, margen 4px x 8px, ancho 92px y sin cursor
            client.println("text-decoration: none; font-size: 18px; margin: 4px 8px; width: 92px; cursor: none;}");
            client.println("</style>");
            
            client.println("<button class=\"button button4\">"+String(contR,HEX)+"</button>");
            client.println("<button class=\"button button4\">"+String(contG,HEX)+"</button>");
            client.println("<button class=\"button button4\">"+String(contB,HEX)+"</button>");
            client.println("<br/>");
            client.println("<button class=\"button button4\">"+String(contR)+"</button>");
            client.println("<button class=\"button button4\">"+String(contG)+"</button>");
            client.println("<button class=\"button button4\">"+String(contB)+"</button>");
            client.println("<br/>");

            client.println("<style> .button5 { background-color: rgb("+String(contR)+","+String(contG)+","+String(contB)+");");
            client.println("border: 2px solid #050505; padding: 100px 100px; cursor: none;}</style>");
            client.println("<button class=\"button5\"></button>");
        
            client.println("</body></html>");
            client.println();
            break; //Salir del bucle while
          }else{ //Si se tiene una nueva linea, se borra DataIn
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
    Serial.println("R="+String(contR)+" G="+String(contR)+" B="+String(contB));
    tft.fillScreen(tft.Color24To565(contR*65536+contG*256+contB)); //Envia a la LCD el color en formato RGB565
  }
}
