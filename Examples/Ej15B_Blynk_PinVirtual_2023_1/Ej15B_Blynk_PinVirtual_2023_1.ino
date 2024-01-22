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
char auth[] = "ZaDrFNzmONFp9BrpFim9Tmt0d-BFrGs1";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "POCO X3 GT";
char pass[] = "15jcamargo";

#define LEDB 2 //Define GPIO2

WidgetLED LED_B(V0); //Widget tipo LED ubicado en el pin virtual V0 en Blynk

BLYNK_CONNECTED(){ //Sincronizar todo los widgets de la aplicación al conectar el ESP32
  Blynk.syncAll();
}

BLYNK_WRITE(V1){ //Genera evento al oprimir el Widget Botón ubicado en el pin virtual V1 en Blynk
  int pinValue=param.asInt(); //Leer el valor del pin virtual V1
  if(pinValue==0){
    LED_B.off();
    Serial.println("LED Azul en V0: Off");  
  }else{
    LED_B.on();
    Serial.println("LED Azul en V0: On");
  }
  Serial.print("El valor de V1 es:");
  Serial.println(pinValue);
  digitalWrite(LEDB,pinValue); //Encender o apagar el LED azul conectado al GPIO2 del ESP32
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass,"iot.laserud.co",8080);
  pinMode(LEDB,OUTPUT);
}

void loop()
{
  Blynk.run();
}
