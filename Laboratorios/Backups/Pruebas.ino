
//Pines de los Pulsadores
#define pinP1 16 //Pulsador de Inicio 
#define pinP2 17 //Pulsador de Arriba
#define pinP3 18 //Pulsador de Abajo
#define pinP4 19 //Pulsador de Izquierda
#define pinP5 21 //Pulsador de Derecha

#define LED 2 //Define GPIO2
#include <LiquidCrystal.h>


volatile uint8_t bandera_P1, bandera_P2, bandera_P3, bandera_P4, bandera_P5 ;
volatile uint16_t tiempo_P1, tiempo_P2, tiempo_P3, tiempo_P4, tiempo_P5;
volatile uint32_t rebote_P1, rebote_P2, rebote_P3, rebote_P4, rebote_P5;
int contador_P1 = 0;
int contador_P2 = 0;
int contador_P3 = 0;
int contador_P4 = 0;
int contador_P5 = 0;

//Pines de la Pantalla

//Define los pines utilizados del ESP32 de acuerdo a la sintaxis de la libreria
const uint8_t RS = 15, EN = 4, D4 = 26, D5 = 25, D6 = 33, D7 = 32;

//################### 3.Inicialización de Variables ###################

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //Define el objeto "lcd"

void IRAM_ATTR Int_P1() {
  contador_P1++;
  Rebote_P1();
}
void IRAM_ATTR Int_P2() {
  contador_P2++;
  Rebote_P2();
}
void IRAM_ATTR Int_P3() {
  contador_P3++;
  Rebote_P3();
}
void IRAM_ATTR Int_P4() {
  contador_P4++;
  Rebote_P4();
}
void IRAM_ATTR Int_P5() {
  contador_P5++;
  Rebote_P5();
}

void setup() {
  lcd.begin(16, 2); //Configurar LCD de tamaño 16x2
  pinMode(LED, OUTPUT);
  pinMode(pinP1, INPUT_PULLUP);
  pinMode(pinP2, INPUT_PULLUP);
  pinMode(pinP3, INPUT_PULLUP);
  pinMode(pinP4, INPUT_PULLUP);
  pinMode(pinP5, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinP1), Int_P1, FALLING); //Habilita int. generada por el GPIO16
  attachInterrupt(digitalPinToInterrupt(pinP2), Int_P2, FALLING); //Habilita int. generada por el GPIO16
  attachInterrupt(digitalPinToInterrupt(pinP3), Int_P3, FALLING); //Habilita int. generada por el GPIO16
  attachInterrupt(digitalPinToInterrupt(pinP4), Int_P4, FALLING); //Habilita int. generada por el GPIO16
  attachInterrupt(digitalPinToInterrupt(pinP5), Int_P5, FALLING); //Habilita int. generada por el GPIO16

  tiempo_P1 = 250; tiempo_P2 = 250; tiempo_P3 = 250; tiempo_P4 = 250; tiempo_P5 = 250;
  bandera_P1 = 0; bandera_P2 = 0; bandera_P3 = 0; bandera_P4 = 0; bandera_P5 = 0;
}


void loop() {
  lcd.setCursor(0, 0);
  lcd.print(contador_P1);
  lcd.setCursor(3, 0);
  lcd.print(contador_P2);
  lcd.setCursor(5, 0);
  lcd.print(contador_P3);
  lcd.setCursor(7, 0);
  lcd.print(contador_P4);
  lcd.setCursor(9, 0);
  lcd.print(contador_P5);
  Pulsador1_();
  Pulsador2_();
  Pulsador3_();
  Pulsador4_();
  Pulsador5_();
}


void Pulsador1_() {

  delay(tiempo_P1);
  if (millis() - rebote_P1 > 300 && bandera_P1) {
    bandera_P1 = 0;
    attachInterrupt(digitalPinToInterrupt(pinP1), Int_P1, FALLING); //Habilita nuevamente int. generada por el GPIO16
  }
}
void Pulsador2_() {

  delay(tiempo_P1);
  if (millis() - rebote_P2 > 300 && bandera_P2) {
    bandera_P2 = 0;
    attachInterrupt(digitalPinToInterrupt(pinP2), Int_P2, FALLING); //Habilita nuevamente int. generada por el GPIO16
  }
}
void Pulsador3_() {

  delay(tiempo_P3);
  if (millis() - rebote_P3 > 300 && bandera_P3) {
    bandera_P3 = 0;
    attachInterrupt(digitalPinToInterrupt(pinP3), Int_P3, FALLING); //Habilita nuevamente int. generada por el GPIO16
  }
}
void Pulsador4_() {

  delay(tiempo_P1);
  if (millis() - rebote_P4 > 300 && bandera_P4) {
    bandera_P4 = 0;
    attachInterrupt(digitalPinToInterrupt(pinP4), Int_P4, FALLING); //Habilita nuevamente int. generada por el GPIO16
  }
}
void Pulsador5_() {

  delay(tiempo_P5);
  if (millis() - rebote_P5 > 300 && bandera_P5) {
    bandera_P5 = 0;
    attachInterrupt(digitalPinToInterrupt(pinP5), Int_P5, FALLING); //Habilita nuevamente int. generada por el GPIO16
  }
}
void Rebote_P1() {
  if (tiempo_P1 == 250) {
    tiempo_P1 = 100;
  } else {
    tiempo_P1 = 250;
  }
  bandera_P1 = 1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote_P1 = millis(); //Lee el valor actual de la función millis()
  detachInterrupt(digitalPinToInterrupt(pinP1)); //Deshabilita int. del GPIO16
}

void Rebote_P2() {
  if (tiempo_P2 == 250) {
    tiempo_P2 = 100;
  } else {
    tiempo_P2 = 250;
  }
  bandera_P2 = 1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote_P2 = millis(); //Lee el valor actual de la función millis()
  detachInterrupt(digitalPinToInterrupt(pinP2)); //Deshabilita int. del GPIO16
}
void Rebote_P3() {
  if (tiempo_P3 == 250) {
    tiempo_P3 = 100;
  } else {
    tiempo_P3 = 250;
  }
  bandera_P3 = 1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote_P3 = millis(); //Lee el valor actual de la función millis()
  detachInterrupt(digitalPinToInterrupt(pinP3)); //Deshabilita int. del GPIO16
}
void Rebote_P4() {
  if (tiempo_P4 == 250) {
    tiempo_P4 = 100;
  } else {
    tiempo_P4 = 250;
  }
  bandera_P4 = 1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote_P4 = millis(); //Lee el valor actual de la función millis()
  detachInterrupt(digitalPinToInterrupt(pinP4)); //Deshabilita int. del GPIO16
}
void Rebote_P5() {
  if (tiempo_P5 == 250) {
    tiempo_P5 = 100;
  } else {
    tiempo_P5 = 250;
  }
  bandera_P5 = 1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote_P5 = millis(); //Lee el valor actual de la función millis()
  detachInterrupt(digitalPinToInterrupt(pinP5)); //Deshabilita int. del GPIO16
}
