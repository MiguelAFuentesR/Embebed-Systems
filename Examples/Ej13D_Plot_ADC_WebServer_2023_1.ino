#include <WiFi.h>
#include <WebServer.h>

//Credenciales de la red WiFi a conectarse:
const char* ssid="Invitados_UDistrital";
const char* password="1nv1tad0s";

WebServer server(80); //Establecer el número del puerto del servidor Web

#define LED_B 2 //GPIO2

String out="";
uint16_t x,y,y2;

void handleRoot() {
  digitalWrite(LED_B,HIGH);
  char temp[800];
  uint8_t sec=millis()/1000;
  uint8_t min=sec/60;
  uint8_t hr=min/60;

  //Almacenar el código HTML a enviar al cliente en la variable temp.
  //La función snprintf() se utiliza para que la salida sea enviada a una cadena de caracteres, especificamente a temp.
  snprintf(temp, 800,
  "<html>\
    <head>\
      <meta http-equiv='refresh' content='2'/>\
      <title>ESP32 Plot ADC</title>\
      <style>\
        body { background-color: #CCCCCC; font-family: Arial, Helvetica, Sans-Serif; color: #000088; }\
      </style>\
    </head>\
    <body>\
      <h1><font color=#770077>Servidor Web Avanzado Embebido en el ESP32</font></h1>\
      <p>Tiempo desde el Inicio: <font color=#FF8000>%02d:%02d:%02d</font></p>\
      <p><font color=#444444>Datos anteriores: --</font> Voltaje: <font color=#449944>%1.2fv</font> x:<font color=#FF0000>%d</font> y:<font color=#806050>%d</font></p>\ 
      <img src=\"/grafica\" alt=\"Grafica de voltaje\" title=\"Datos del ADC\"/>\      
    </body>\
  </html>",
           hr,min%60,sec%60,y*3.3/255.0,x-10,y
          );
  server.send(200,"text/html",temp);
  digitalWrite(LED_B,LOW);
}

//Gráfica en formato SVG (Scalable Vector Graphics), formato gráfico basado en XML para crear archivos vectoriales en 2D
void drawGraph(){
  char temp[200];
  if(x==0){
    //Etiqueta XML para generar el espacio de la imagen SVG (el orden de los atributos no importa),
    //opcional: coordenadas x,y empiezan en la esquina superior izquierda (por defecto 0,0),
    //tamaño del espacio de trabajo: width y height en pixeles
    out+="<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\" width=\"840\" height=\"300\">\n";
    //Etiqueta XML para generar un rectangulo en el espacio de trabajo, width y height en pixeles,
    //fill: color de relleno rgb, stroke: color del perímetro rgb, stroke-width: grosor del perímetro,
    //opcional: coordenadas x,y empiezan en la esquina superior izquierda (por defecto 0,0),
    //opcional: esquinas redondeadas se agrega parámetro rx=# donde # representa el radio del
    //redondeado  
    out+="<rect width=\"800\" height=\"260\" fill=\"rgb(200,230,250)\" stroke-width=\"1\" stroke=\"rgb(0,0,0)\" />\n";
    out+="<rect x=\"810\" y=\"3\" width=\"20\" height=\"257\" fill=\"yellow\" stroke-width=\"1\" stroke=\"red\" />\n";
    for(uint16_t xc=10;xc<800;xc+=10){
      sprintf(temp,"<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"rgb(245,245,245)\" stroke-width=\"1\" />\n", xc,1,xc,259);
      out+=temp;
    }
    for(uint16_t yc=10;yc<260;yc+=10){
      sprintf(temp,"<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"rgb(245,245,245)\" stroke-width=\"1\" />\n", 1,yc,799,yc);
      out+=temp;
    }
  }

  y2=analogRead(34)/16;
  sprintf(temp,"<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"blue\" stroke-width=\"1\" />\n", x,260-y,x+10,260-y2);
  out+=temp;
  y=y2;
  Serial.println(y);
  uint16_t tam=out.length();
  sprintf(temp,"<rect x=\"811\" y=\"4\" width=\"18\" height=\"%d\" fill=\"white\" stroke-width=\"1\" stroke=\"white\" />\n", 255-y);
  out+=temp;
  out+="<text x=\"0\" y=\"280\" font-family=\"Arial, Helvetica, sans-serif\">Voltaje:</text>\n";  
  sprintf(temp,"<text x=\"55\" y=\"280\" font-family=\"Arial, Helvetica, sans-serif\" fill=\"green\">%1.2fv</text>\n", y*3.3/255.0);
  out+=temp;
  out+="<text x=\"100\" y=\"280\" font-family=\"Arial, Helvetica, sans-serif\">x:</text>\n";  
  sprintf(temp,"<text x=\"115\" y=\"280\" font-family=\"Arial, Helvetica, sans-serif\" font-style=\"italic\" fill=\"red\">%d</text>\n", x);
  out+=temp;
  out+="<text x=\"150\" y=\"280\" font-family=\"Arial, Helvetica, sans-serif\">y:</text>\n";
  sprintf(temp,"<text x=\"165\" y=\"280\" font-family=\"Arial, Helvetica, sans-serif\" font-style=\"italic\" fill=\"magenta\">%d</text>\n", y);
  out+=temp;
  out+="</svg>\n";
  server.send(200,"image/svg+xml",out);
  out.remove(tam,out.length()-tam);
  //Serial.println(out);

  x+=10;
  if(x==800){
    x=0;
    out="";
  }  
}

void drawLogo(){
String logo="";
  logo+="<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"350\" height=\"250\">\n";
  logo+="<text x=\"10\" y=\"30\" font-family=\"sans-serif\" font-style=\"italic\" font-size=\"13px\">Esta</text>\n";
  logo+="<text x=\"40\" y=\"32\" font-family=\"sans-serif\" font-style=\"bold\" font-size=\"30px\" fill=\"blue\">es</text>\n";
  logo+="<text x=\"30\" y=\"50\" font-family=\"sans-serif\" font-style=\"italic\" font-size=\"13px\">una</text>\n";
  logo+="<text x=\"55\" y=\"55\" font-family=\"serif\" font-style=\"italic\" font-size=\"40px\" fill=\"red\">Prueba</text>\n";
  logo+="<text x=\"180\" y=\"50\" font-family=\"sans-serif\" font-style=\"italic\" font-size=\"13px\" transform=\"rotate(315 180 50)\">con</text>\n";
  logo+="<text x=\"195\" y=\"40\" font-family=\"serif\" font-style=\"italic\" font-size=\"35px\" transform=\"rotate(5 195 40)\" fill=\"green\">imágenes!</text>\n";
  logo+="<image x=\"180\" y=\"60\" width=\"128\" height=\"146\" transform=\"rotate(45 180 60)\" xlink:href=\"https://developer.mozilla.org/en-US/docs/Web/SVG/Element/image/mdn_logo_only_color.png\" />\n";
  logo+="</svg>\n";
  server.send(200,"image/svg+xml",logo);
}

void handleADC(){
  server.send(200,"text/plain","Valor del ADC: " + String(y));
}

void handleNotFound() {
  digitalWrite(LED_B,HIGH);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404,"text/plain",message);
  digitalWrite(LED_B,LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_B,LOW);

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

  server.on("/",handleRoot);
  server.on("/grafica",drawGraph);
  server.on("/logoX",drawLogo);
  server.on("/ADC",handleADC);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Servidor HTTP iniciado");
  x=0;
  y=analogRead(34)/16;
  Serial.println(y);
}

void loop() {
  server.handleClient();
  delay(20);
}
