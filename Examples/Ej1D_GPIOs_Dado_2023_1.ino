
#define L1 13 //Define GPIO13
#define L2 12 //Define GPIO12
#define L3 14 //Define GPIO14
#define L4 27 //Define GPIO27
#define L5 26 //Define GPIO26
#define L6 25 //Define GPIO25
#define Lanzar 16 //Define GPIO16
#define Buzzer 15 //Define GPIO15

uint8_t LEDs[]={13,12,14,27,26,25};
uint8_t i,dado;

void setup() {
  Serial.begin(115200);
  for(i=0;i<6;i++){
    pinMode(LEDs[i],OUTPUT);  //L1 a L6 configurados como salidas
  }
  pinMode(Buzzer,OUTPUT); //Buzzer para indicar que se puede realizar un nuevo lanzamiento del dado
  pinMode(Lanzar,INPUT_PULLUP); //Pulsador N.A. utilizado para generar el lanzamiento del dado
  randomSeed(10);
}

void loop() {
  while(digitalRead(Lanzar)==1); //Esperar hasta que se oprima el pulsador (se lance el dado)
  dado=random(1,6);
  Serial.print("Valor obtenido en el lanzamiento: ");
  Serial.println(dado);
  for(i=0;i<6;i++){
    digitalWrite(LEDs[i],LOW);  //Apagar todos los LEDs 
  }
  for(i=0;i<dado;i++){
    digitalWrite(LEDs[i],HIGH); //Encender cantidad de LEDs que representan el valor obtenido
  }
  delay(3000); //Esperar 3s para generar un nuevo lanzamiento
  digitalWrite(Buzzer,HIGH);
  Serial.println("Nuevo lanzamiento disponible");
  delay(100);
  digitalWrite(Buzzer,LOW);
}
