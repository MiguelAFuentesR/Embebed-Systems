#define pulsador1 14 //Define GPIO14
#define pulsador2 16 //Define GPIO16
#define LED 2 //Define GPIO2

volatile uint8_t bandera;
volatile uint16_t tiempo;
volatile uint32_t rebote;

void IRAM_ATTR Int_SW1(){
  tiempo=250;
  bandera=1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote=millis(); //Lee el valor actual de la función millis()
  Serial.println("Tiempo= "+(String)tiempo+"ms");
  Serial.println(rebote);
  detachInterrupt(digitalPinToInterrupt(pulsador1)); //Deshabilita int. del GPIO14 
}

void IRAM_ATTR Int_SW2(){
  tiempo=100;
  bandera=1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote=millis(); //Lee el valor actual de la función millis()
  Serial.println("Tiempo= "+(String)tiempo+"ms");
  Serial.println(rebote);
  detachInterrupt(digitalPinToInterrupt(pulsador2)); //Deshabilita int. del GPIO16 
}

void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  pinMode(pulsador1,INPUT_PULLUP);
  pinMode(pulsador2,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulsador1),Int_SW1,FALLING); //Habilita int. generada por el GPIO14
  attachInterrupt(digitalPinToInterrupt(pulsador2),Int_SW2,FALLING); //Habilita int. generada por el GPIO16
  tiempo=250;
  bandera=0;
}

void loop() {
  digitalWrite(LED,!digitalRead(LED)); //Conmutar el estado actual del LED
  delay(tiempo);
  if(millis()-rebote>300&&bandera){
    bandera=0;
    attachInterrupt(digitalPinToInterrupt(pulsador1),Int_SW1,FALLING); //Habilita nuevamente int. generada por el GPIO14 
    attachInterrupt(digitalPinToInterrupt(pulsador2),Int_SW2,FALLING); //Habilita nuevamente int. generada por el GPIO16   
  }
}
