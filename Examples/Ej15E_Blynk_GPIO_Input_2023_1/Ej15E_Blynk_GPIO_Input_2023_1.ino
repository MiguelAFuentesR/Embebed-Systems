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
char auth[] = "HdQUUaFlIrKyh0uCkTTgELC2TYRalaVX";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "POCO X3 GT";
char pass[] = "15jcamargo";

#define LEDB 2 //Define GPIO2
#define SW 14//Define GPIO14

uint8_t flag;

WidgetLED LED_R(V0); //Widget tipo LED ubicado en el pin virtual V0 en Blynk

BlynkTimer timer; //Generar el evento de Timer de Blynk denominado "timer"

BLYNK_CONNECTED(){ //Sincronizar todo los widgets de la aplicación al conectar el ESP32
  Blynk.syncAll();
}

void leerPin(){
  if(digitalRead(SW)==0){ //Si pulsador oprimido...
    flag+=5;
    if(flag==4){flag=0;}
    Blynk.virtualWrite(V0,flag);
    LED_R.setValue(flag); //Asignar el nivel de brillo del LED virtual
    Serial.print("Valor del LED Rojo en V0:");
    Serial.println(flag);
    if(flag==125){
      Blynk.notify("LED Rojo en V0 con brillo medio");
    }else if(flag==255){
      Blynk.notify("LED Rojo en V0 con brillo máximo");
    }
    digitalWrite(LEDB,HIGH);
    delay(50);
    digitalWrite(LEDB,LOW);
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass,"iot.laserud.co",8080);
  pinMode(LEDB,OUTPUT);
  pinMode(SW,INPUT_PULLUP); //Pulsador N.A. conectado al GPIO14
  timer.setInterval(200,leerPin); //Asignar el intervalo de tiempo y definir la rutina asociada al evento de tiempo
  flag=0;
  Blynk.virtualWrite(V0,flag);
  Blynk.notify("Atención... reinicio del Hardware");
}

void loop()
{
  Blynk.run();
  timer.run();
}
