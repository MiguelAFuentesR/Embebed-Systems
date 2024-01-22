  #define LED 2 //Define GPIO2
  #define pulsador 14 //Define GPIO14

void setup() {
  pinMode(LED,OUTPUT); //Configurar GPIO2 como salida para controlar LED Azul de la tarjeta
  pinMode(pulsador,INPUT_PULLUP); //Configurar GPIO14 como entrada para leer estado de pulsador N.A.
}

void loop() {
  if(digitalRead(pulsador)==0){ //Verificar si se oprimió el pulsador
    digitalWrite(LED,!digitalRead(LED)); //Conmutar el estado actual del LED
    while(digitalRead(pulsador)==0);
    delay(500); //Esperar para eliminar rebote del pulsador
  }
}
