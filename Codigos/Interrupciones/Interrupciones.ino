#define pulsador 16
#define LED 2

volatile uint8_t bandera;
volatile uint16_t tiempo;
volatile uint32_t rebote;


void IRAM_ATTR Int_SW(){

  if(tiempo==250){
    tiempo = 100;
    }else{
      tiempo = 250;
   }

   //Para evitar el rebote se propone desactivar la interrupcion y luego volverla a activar
   //1.Se hace pensar que se activo la interrupcion
   bandera = 1; // Indicar ingreso a rutina de interrupción --> Se oprimio el pulsador
   rebote = millis(); //Se lee el valor actual de la funcion millis()
  
  Serial.println("Tiempo= "+(String)tiempo+" ms");
  Serial.println(rebote);
  attachInterrupt(digitalPinToInterrupt(pulsador));

   
}
void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  pinMode(pulsador,INPUT_PULLUP); 

//Desactiar Interrupcion
  attachInterrupt(digitalPinToInterrupt(pulsador),Int_SW,FALLING);
  tiempo = 250;
  bandera = 0;
  
}

void loop() {
  //Rutina para Elimnar Rebotes
    digitalWrite(LED,digitalRead(LED)); //Conmutar el estado actual del led
    delay(tiempo);
    if(millis()-rebote>300&&bandera){
      //Se activa unicamente cuando han pasado 300 segundos luego de pulsar el pulsador
       bandera = 0;
      attachInterrupt(digitalPinToInterrupt(pulsador),Int_SW,FALLING); //Habilitar Interrupcion

      }

}
