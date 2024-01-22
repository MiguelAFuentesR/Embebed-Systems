
// 13-02-2023 Dado Digital  

#define L1 13 
#define L2 12 
#define L3 14
#define L4 27
#define L5 26 
#define L6 25
#define Lanzar 16
#define buzzer 15

uint8_t LEDs[]={13,12,14,27,26,25};
uint8_t i,dado;


void setup() {
  Serial.begin(115200);

  for(i=0;i<6;i++){
    pinMode(LEDs[i],OUTPUT);
    }
  pinMode(buzzer,OUTPUT);
  pinMode(Lanzar,INPUT_PULLUP); 

  // Para generador de numeros aleatorios :
  randomSeed(10);

}

void loop() {
  
  while(digitalRead(Lanzar==1)); //Esperar hasta que se lance el dado 
  dado = random(1,6);
  Serial.print("El numero Aleatorio es : ");
  Serial.println(dado);
  //Empezar a encender 1 a uno los leds hasta el valor dado por el dado
  
  //1.Apagar todos los leds
  for(i=0;i<6;i++){
    digitalWrite(LEDs[i],LOW);
    }
  
  //1.Visualizar el numero aleatorio
  for(i=0;i<dado;i++){
    digitalWrite(LEDs[i],HIGH);
    }
  delay(3000); // Durante 3 Seg no se puede lanzar el dado 
  
  digitalWrite(buzzer,HIGH);
  delay(100); 
  digitalWrite(buzzer,LOW);

   
}
