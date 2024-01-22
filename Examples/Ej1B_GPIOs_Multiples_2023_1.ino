  #define LED 2 //Define GPIO2
  #define pulsadorOn 14 //Define GPIO14
  #define pulsadorOff 16 //Define GPIO16

void setup() {
  pinMode(LED,OUTPUT); //Configurar GPIO2 como salida para controlar LED Azul de la tarjeta
  pinMode(pulsadorOn,INPUT_PULLUP); //Configurar GPIO14 como entrada para leer estado de pulsador N.A.
  pinMode(pulsadorOff,INPUT_PULLUP); //Configurar GPIO16 como entrada

}

void loop() {
  if(digitalRead(pulsadorOn)==0){digitalWrite(LED,HIGH);} //Verifica si se oprimió pulsador para encendido, si es así, enciende el LED
  if(digitalRead(pulsadorOff)==0){digitalWrite(LED,LOW);} //Verifica si se oprimió pulsador para apagado, si es así, apaga
}
