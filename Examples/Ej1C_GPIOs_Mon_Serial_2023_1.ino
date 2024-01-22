  #define LED 2 //Define GPIO2
  #define pulsador 14 //Define GPIO14

uint8_t cont;  

void setup() {
  Serial.begin(115200); //Habilitar comuniciación serial con el Monitor Serie del IDE de Arduino a 115200bps
  pinMode(LED,OUTPUT); //Configurar GPIO2 como salida para controlar LED Azul de la tarjeta
  pinMode(pulsador,INPUT_PULLUP); //Configurar GPIO14 como entrada para leer estado de pulsador N.A.
  cont=0;
}

void loop() {
  if(digitalRead(pulsador)==0){ //Verificar si se oprimió el pulsador
    digitalWrite(LED,!digitalRead(LED)); //Conmutar el estado actual del LED
    cont++;
    Serial.println("LED cambió de estado");
    Serial.print("No. de veces que se ha oprimido el pulsador: ");
    Serial.println(cont);
    while(digitalRead(pulsador)==0);
    delay(500); //Esperar para eliminar rebote del pulsador
  }
}
