 // EJEMPLO 1 : 

/* 
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH);
  delay(1000);
  digitalWrite(2,LOW  );
  delay(1000); 
}*/

 // EJEMPLO 2 : 


/*
  #define LED 2 //Define GPIO2
  #define pulsador 14 //Define GPIO14
  
void setup() {  
  //Configuracion de  los GPIO 

  pinMode(LED,OUTPUT); 
  pinMode(pulsador,INPUT_PULLUP); // Leer entrada del pulsador 

}

void loop() {

  if(digitalRead(pulsador)==0){
    digitalWrite(LED,!digitalRead(LED));
    while(digitalRead(pulsador)==0);
    delay(500);
    }

}

*/

 // EJEMPLO 3 : 

/*

  #define LED 2 //Define GPIO2
  #define pulsadoron 14 //Define GPIO14
  #define pulsadoroff 16 //Define GPIO14
void setup() {  
  //Configuracion de  los GPIO 

  pinMode(LED,OUTPUT); 
  pinMode(pulsadoron,INPUT_PULLUP); // Leer entrada del pulsador 
  pinMode(pulsadoroff,INPUT_PULLUP); // Leer entrada del pulsador 

}

void loop() {

  if(digitalRead(pulsadoron)==0){digitalWrite(LED,HIGH);}
  if(digitalRead(pulsadoroff)==0){digitalWrite(LED,LOW);}


}


 */


 // EJEMPLO 4 : 


  #define LED 2 //Define GPIO2
  #define pulsador 14 //Define GPIO14
  uint8_t contador;
  
 void setup() {
  
  Serial.begin(115200);  
  pinMode(LED,OUTPUT); 
  pinMode(pulsador,INPUT_PULLUP); // Leer entrada del pulsador

  contador = 0;

}

void loop() {

 
  if(digitalRead(pulsador)==0){
    digitalWrite(LED,!digitalRead(LED));
    contador++;
    Serial.println("LED cambio de estado");
    Serial.print("No de Veces que se ha oprimido el pulsador : ");
    Serial.println(contador);
    while(digitalRead(pulsador)==0);
    delay(500);
    }

}
