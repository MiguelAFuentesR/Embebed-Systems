#include <WiFi.h>

// Crear las credenciales del punto de acceso

const char* ssid = "WiFi-ESP32";
const char* password = "Embebidos1";

WiFiServer server(80); //Establecer el puerto del servidor WEB, asignado al objeto creado

String header; // Almacenar las solicitudes HTTP
String Estado_LED_B = "Off"; //Almacenar el estado actual del LED Azul
String Estado_LED_R = "Off"; //Almacenar el estado actual del LED Rojo

#define LED_B 2
#define LED_R 25


void setup() {
  Serial.begin(115200);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_R, OUTPUT);

  digitalWrite(LED_B, LOW);
  digitalWrite(LED_R, LOW);

  Serial.println("Estableciendo el AP ...");
  WiFi.softAP(ssid, password);
  Serial.print("AP" + String(ssid) + "Creado Correctamente !!");
  IPAddress IP = WiFi.softAPIP(); // Obtener dirección IP del AP
  Serial.println("Direccipon IP del AP:");
  Serial.println(IP);
  server.begin();
  



}

void loop() {

}
