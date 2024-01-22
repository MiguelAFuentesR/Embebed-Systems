void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT); //Configura GPIO2 como pin de salida
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(2,HIGH); //Encender LED Azul
  delay(1000);          //Esperar un segundo
  digitalWrite(2,LOW);  //Apagar el LED Azul
  delay(1000);
}
