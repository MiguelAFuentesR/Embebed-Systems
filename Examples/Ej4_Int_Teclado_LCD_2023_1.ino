#include <LiquidCrystal.h>

//Define los pines utilizados del ESP32 de acuerdo a la sintaxis de la libreria
const uint8_t RS=15,EN=4,D4=26,D5=25,D6=33,D7=32; 

LiquidCrystal lcd(RS,EN,D4,D5,D6,D7); //Define el objeto "lcd"

#define C0 13 //Salidas para las columnas
#define C1 12
#define C2 14
#define C3 27
#define F0 16 //Entradas con pull-up para las filas
#define F1 17
#define F2 19
#define F3 21

volatile uint8_t t,bandera,key,key_f;
volatile uint32_t rebote;
uint8_t scan;
uint32_t t_actual,t_anterior;

void IRAM_ATTR Int_F0(){
  switch(t){
    case 0:
      key='1';
    break;
    case 1:
      key='2';
    break;
    case 2:
      key='3';
    break;
    case 3:
      key='A';
    break;
  }
  key_f=1; //Indica que se oprimió una tecla
  detachInterrupt(digitalPinToInterrupt(F0));
  bandera=1;
  rebote=millis();
}

void IRAM_ATTR Int_F1(){
  switch(t){
    case 0:
      key='4';
    break;
    case 1:
      key='5';
    break;
    case 2:
      key='6';
    break;
    case 3:
      key='B';
    break;
  }
  key_f=1; //Indica que se oprimió una tecla
  detachInterrupt(digitalPinToInterrupt(F1));
  bandera=1;
  rebote=millis();
}

void IRAM_ATTR Int_F2(){
  switch(t){
    case 0:
      key='7';
    break;
    case 1:
      key='8';
    break;
    case 2:
      key='9';
    break;
    case 3:
      key='C';
    break;
  }
  key_f=1; //Indica que se oprimió una tecla
  detachInterrupt(digitalPinToInterrupt(F2));
  bandera=1;
  rebote=millis();
}

void IRAM_ATTR Int_F3(){
  switch(t){
    case 0:
      key='*';
    break;
    case 1:
      key='0';
    break;
    case 2:
      key='#';
    break;
    case 3:
      key='D';
    break;
  }
  key_f=1; //Indica que se oprimió una tecla
  detachInterrupt(digitalPinToInterrupt(F3));
  bandera=1;
  rebote=millis();
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16,2); //Configurar LCD de tamaño 16x2
  pinMode(C0,OUTPUT); pinMode(C1,OUTPUT); pinMode(C2,OUTPUT); pinMode(C3,OUTPUT);
  pinMode(F0,INPUT_PULLUP); pinMode(F1,INPUT_PULLUP); pinMode(F2,INPUT_PULLUP); pinMode(F3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(F0),Int_F0,FALLING); 
  attachInterrupt(digitalPinToInterrupt(F1),Int_F1,FALLING);
  attachInterrupt(digitalPinToInterrupt(F2),Int_F2,FALLING);
  attachInterrupt(digitalPinToInterrupt(F3),Int_F3,FALLING);
  digitalWrite(C0,0); digitalWrite(C1,1); digitalWrite(C2,1); digitalWrite(C3,1);
  t=0;
  t_anterior=0;
  key_f=0;
  bandera=0;
  scan=10; //Barrido del teclado (10ms)
}

void loop() {
  t_actual=millis();
  if(t_actual-t_anterior>scan){
    t++;
    if(t==4){t=0;} //Verificar si finaliza el escaneo de las columnas del teclado y lo reinicia
    t_anterior=t_actual;
    switch(t){
      case 0:
        digitalWrite(C0,0); digitalWrite(C1,1); digitalWrite(C2,1); digitalWrite(C3,1);
      break; 
      case 1:
        digitalWrite(C0,1); digitalWrite(C1,0); digitalWrite(C2,1); digitalWrite(C3,1);
      break; 
      case 2:
        digitalWrite(C0,1); digitalWrite(C1,1); digitalWrite(C2,0); digitalWrite(C3,1);
      break;     
      case 3:
        digitalWrite(C0,1); digitalWrite(C1,1); digitalWrite(C2,1); digitalWrite(C3,0);
      break;
    }
    if(key_f==1){ //Si se oprimió tecla...
      Serial.println(char(key)); //Enviar el valor de la tecla oprimida
      lcd.setCursor(0,0);
      lcd.print(char(key)); //Visualizar en la LCD el valor de la tecla oprimida
      key_f=0;
    }
    if(millis()-rebote>300&&bandera){
      attachInterrupt(digitalPinToInterrupt(F0),Int_F0,FALLING);
      attachInterrupt(digitalPinToInterrupt(F1),Int_F1,FALLING);
      attachInterrupt(digitalPinToInterrupt(F2),Int_F2,FALLING);
      attachInterrupt(digitalPinToInterrupt(F3),Int_F3,FALLING);
      bandera=0;
    }
  }
}
