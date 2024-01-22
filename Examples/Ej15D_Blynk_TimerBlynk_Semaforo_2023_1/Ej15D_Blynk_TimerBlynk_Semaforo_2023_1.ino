/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  Note: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "9v1CkEQfasgioeluDkxSDk39fU-hQE84";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "POCO X3 GT";
char pass[] = "15jcamargo";

#define LEDB 2 //Define GPIO2

uint8_t timerID,cont;

WidgetLED LED_R(V0); //Widget tipo LED ubicado en el pin virtual V0 en Blynk
WidgetLED LED_Y(V1); //Widget tipo LED ubicado en el pin virtual V1 en Blynk
WidgetLED LED_G(V2); //Widget tipo LED ubicado en el pin virtual V2 en Blynk

BlynkTimer timer; //Generar el evento de Timer de Blynk denominado "timer"

BLYNK_CONNECTED(){ //Sincronizar todo los widgets de la aplicación al conectar el ESP32
  Blynk.syncAll();
}


void conmutarSemaforo(){
  cont++;
  digitalWrite(LEDB,!digitalRead(LEDB));
  timer.deleteTimer(timerID);
  switch(cont){
      case 1:
        LED_R.on(); LED_Y.on(); LED_G.off();
        timerID=timer.setInterval(3000,conmutarSemaforo);
        Serial.println("Tiempo 2: 3s");
      break;
      case 2:
        LED_R.off(); LED_Y.off(); LED_G.on();
        timerID=timer.setInterval(8000,conmutarSemaforo);
        Serial.println("Tiempo 3: 8s");
      break;  
      case 3:
        LED_R.off(); LED_Y.on(); LED_G.off();
        timerID=timer.setInterval(3000,conmutarSemaforo);
        Serial.println("Tiempo 4: 3s");
      break;  
      case 4:
        LED_R.on(); LED_Y.off(); LED_G.off();
        timerID=timer.setInterval(5000,conmutarSemaforo);
        Serial.println("Tiempo 1: 5s");
        cont=0;
      break;          
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass,"iot.laserud.co",8080);
  pinMode(LEDB,OUTPUT);
  LED_R.on(); LED_Y.off(); LED_G.off();
  timerID=timer.setInterval(5000,conmutarSemaforo); //Asignar el intervalo de tiempo y definir la rutina asociada al evento de tiempo
  cont=0;
  Serial.println("Tiempo 1: 5s");
}

void loop()
{
  Blynk.run();
  timer.run();
}
