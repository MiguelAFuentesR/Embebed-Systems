/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Rkkbbgxtwe-sFqXJksbjUG0EsRsSLF5h";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Familia Ramirez";
char pass[] = "FamiliaRamirezFuentes2020";


#define BLYNK_TEMPLATE_NAME "LED TEST"


#define LEDB 2 //Define GPIO2
#define SW 14//Define GPIO14

BLYNK_CONNECTED(){ //Sincronizar todo los widgets de la aplicación al conectar el ESP32
  Blynk.syncAll();
}
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass,"blynk.cloud",80);
  //pinMode(LEDB,OUTPUT);
}

void loop() {
 Blynk.run();
}
