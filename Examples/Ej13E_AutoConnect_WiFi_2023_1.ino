//Uso de la libreria WiFiManager hecha por tzapu, utilizada para configurar los parámetros de red WiFi desde un móvil en un ESP32,
//rellenando un formulario en una página web embebida en el ESP32.
//Se generan mensajes que inician con *wm: Estos mensajes los escribe la librería WiFiManager, por defecto está activado el modo de
//depuración en el monitor serie. Para desactivar el modo depuración se utiliza la función wifiManager.setDebugOutput(false).

#include <WiFiManager.h>

#define LED_B 2 //Define GPIO2

hw_timer_t *timer=NULL; //Se crea el objeto "timer"

void IRAM_ATTR Int_Timer(){
  digitalWrite(LED_B,!digitalRead(LED_B));
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_B,OUTPUT);

  timer=timerBegin(0,80,true); //Configurar Timer 0 con preesc. x80 (=1MHz) y autoincremento
  timerAlarmWrite(timer,200000,true); //Timer 0 genera 200.000 de conteos (=0.2s) con autorecarga
  timerAttachInterrupt(timer,Int_Timer,true); //Hab. int. del Timer 0
  timerAlarmEnable(timer); //Habilitar el Timer
  
  WiFiManager wifiManager; //Crear el objeto de nombre "wifiManager"
 
  // Descomentar para resetear configuración
  //wifiManager.resetSettings();
 
  wifiManager.autoConnect("ESP32Temp"); //Crear AP y portal cautivo
  
  Serial.println("Conexión correcta!!");
  Serial.println("Conectado a "+String(WiFi.SSID()));
  Serial.print("Dirección IP asignada:");
  Serial.println(WiFi.localIP()); //Obtener dirección IP asignada por el router
  timerEnd(timer);
  timer=NULL;
  digitalWrite(LED_B,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
