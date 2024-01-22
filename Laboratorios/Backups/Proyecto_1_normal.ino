
//################### 1.Definición de Librerias ###################
using namespace std;
#include <LiquidCrystal.h>

//################### 2. Definición de Variables ###################

//Pines de las Columnas
#define pinC1 27
#define pinC2 14
#define pinC3 12
#define pinC4 13
#define pinC5 23
#define pinC6 22
#define pinC7 1
#define pinC8 3

//Pines de las filas
#define pinSA 21
#define pinSB 19
#define pinSC 18
#define pinSD 5

/*
  Pines con resistencia de pull-up interna (INPUT_PULLUP):
  GPIO14, GPIO16, GPIO17, GPIO18, GPIO19, GPIO21, GPIO22 y GPIO23.
*/


//Pines de los Pulsadores
#define pinP1 16 //Pulsador de Inicio 
#define pinP2 17 //Pulsador de Arriba
#define pinP3 18 //Pulsador de Abajo
#define pinP4 19 //Pulsador de Izquierda
#define pinP5 21 //Pulsador de Derecha

// ----------- PRUEBAS  -------------------
#define LED 2 //Define GPIO2



//Pines de la Pantalla

//Define los pines utilizados del ESP32 de acuerdo a la sintaxis de la libreria
const uint8_t RS = 15, EN = 4, D4 = 26, D5 = 25, D6 = 33, D7 = 32;

//################### 3.Inicialización de Variables ###################

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //Define el objeto "lcd"


int Velocidad = 1;
int num_fig_ale;

int x = 0;
int y = 0;
int n = 3;
int Nivel = 0;

String Figura_Random;




// Definición de Figuras


// Figura 1
int L[3][4] = {
  { 1, 0, 0, 0},  // 1
  { 1, 0, 0, 0},  // 2
  { 1, 1, 0, 0},  // 3
};

// Figura 2
int Linv[3][4] = {
  { 0, 1, 0, 0 },  // 1
  { 0, 1, 0, 0 },  // 2
  { 1, 1, 0, 0 },  // 3
};

// Figura 3
int Z[3][4] = {
  { 1, 1, 0, 0 },  // 1
  { 0, 1, 1, 0 },  // 2
  { 0, 0, 0, 0 },  // 2
};

// Figura 4
int Zinv[3][4] = {
  { 0, 1, 1, 0 },  // 1
  { 1, 1, 0, 0 },  // 2
  { 0, 0, 0, 0 },  // 2
};

// Figura 5
int line[4][4] = {
  { 1, 0, 0, 0 },  // 1
  { 1, 0, 0, 0 },  // 2
  { 1, 0, 0, 0 },  // 3
  { 1, 0, 0, 0 },  // 4
};

// Figura 6
int T[3][4] = {
  { 0, 1, 0, 0 },  // 1
  { 1, 1, 1, 0 },  // 2
  { 0, 0, 0, 0 },  // 3
};

// Figura 7
int sqr[2][4] = {
  { 1, 1, 0, 0 },  // 1
  { 1, 1, 0, 0 },  // 2
};

int mem[16][8] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 1
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 2
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 3
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 4
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 5
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 6
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 7
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 8
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 9
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 10
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 11
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 12
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 13
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 14
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 15
  { 0, 0, 0, 0, 0, 0, 0, 0 }   // 16
};

int canvas[16][8] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 1
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 2
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 3
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 4
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 5
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 6
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 7
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 8
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 9
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 10
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 11
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 12
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 13
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 14
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 15
  { 0, 0, 0, 0, 0, 0, 0, 0 }   // 16
};



// DEFINICION INTERRUPCIONES :


//Interrupcion
volatile uint8_t bandera; //Indica el ingreso a la rutina de int. del Timer
volatile uint16_t tiempo; //Contador de tiempo (número de interrupciones generadas por el Timer)
hw_timer_t *timer=NULL;   //Se crea el objeto "timer"
hw_timer_t *timer1=NULL;
volatile int rotation=0;

void IRAM_ATTR Int_Timer(){
  //digitalWrite(LED,!digitalRead(LED));
  tiempo++;
  bandera=1;
}
void IRAM_ATTR Int_Timer1(){
  // digitalWrite(LED,!digitalRead(LED));
  
//  stepDown(T, 3, "T", rotation);
}

void rotacion(string figName){
  if (figName == "L" or figName == "Linv" or figName == "T"){
    if(rotation<3){
      rotation++;      
    }else{
      rotation = 0;
    }

  }else if (figName == "Z" or figName == "Zinv"){
    if(rotation<1){
      rotation++;
    }else{
      rotation = 0;
    }
  }else{
      rotation = 0;
  }
}
//Pulsadores

volatile uint8_t bandera1;
volatile uint8_t Rebote;
volatile uint8_t cont1;

void IRAM_ATTR Pulsador1(){
  digitalWrite(LED,!digitalRead(LED));
}
/*
void IRAM_ATTR Pulsador2(){
  Rebote = millis();
  bandera1 = 1;
  if(posFil<16){
    posFil = posFil+1;
  }
}

void IRAM_ATTR Pulsador3(){
  Rebote = millis();
  if(posFil>0){
    posCol = posCol+1;
  }
  bandera1 = 1;
  cont1 = 3;
}

void IRAM_ATTR Pulsador4(){
  Rebote = millis();
  if(posFil>0){
    posCol = posCol-1;
  }
  bandera1 = 1;
  cont1 = 4;
}
*/

void setup() {
  lcd.begin(16, 2); //Configurar LCD de tamaño 16x2

  //Configuracion Pulsadores
  pinMode(pinP1, INPUT_PULLUP); //Configurar GPIO16 como entrada para leer estado de pulsador N.A.
  pinMode(pinP2, INPUT_PULLUP); //Configurar GPIO17 como entrada
  pinMode(pinP3, INPUT_PULLUP); //Configurar GPIO18 como entrada
  pinMode(pinP4, INPUT_PULLUP); //Configurar GPIO19 como entrada
  pinMode(pinP5, INPUT_PULLUP); //Configurar GPIO21 como entrada

  //Configuracion de las Columnas
  pinMode(pinC1, OUTPUT);
  pinMode(pinC2, OUTPUT);
  pinMode(pinC3, OUTPUT);
  pinMode(pinC4, OUTPUT);
  pinMode(pinC5, OUTPUT);
  pinMode(pinC6, OUTPUT);
  pinMode(pinC7, OUTPUT);
  pinMode(pinC8, OUTPUT);

  //Configuracion de las Filas
  pinMode(pinSA, OUTPUT);
  pinMode(pinSB, OUTPUT);
  pinMode(pinSC, OUTPUT);
  pinMode(pinSD, OUTPUT);

pinMode(LED, OUTPUT);
  //-----------------PRUEBAS --------------------

  pinMode(LED, OUTPUT);

  //Configuración Interrupciones
 attachInterrupt(digitalPinToInterrupt(pinP1),Pulsador1,FALLING);
  timer = timerBegin(0, 80, true); //Configurar Timer 0 con preesc. x80 (1MHz) y conteo ascendente
  timerAlarmWrite(timer, 1000000, true); //Timer 0 conf. a 1s (1000000us) y con autorecarga
  timerAttachInterrupt(timer, Int_Timer, true); //Hab.int. del Timer 0
  timerAlarmEnable(timer); //Habilitar el Timer 0
  
}

void loop() {
  Pantalla_Inicio();

  //Inicio Juego
  while (digitalRead(pinP1) == 1); //Esperar hasta que se oprima el pulsador (se inicie el juego)
  Pantalla_Selector_Nivel();

 Pantalla_Nivel();
  for (int i = 1; i < 6; i++) {
    if (i == 5) {
      Nivel = 0;
    } else {
      while (digitalRead(pinP2) == 1);
      digitalWrite(LED, !digitalRead(LED));
      Nivel++;
      lcd.setCursor(8, 0);
      lcd.print(Nivel);
    }
  }

 
  /*
  if (!digitalRead(pinP1) == 1) {
    //Se selecciono Nivel 1
    lcd.setCursor(8, 0);
    lcd.print("1");
    Velocidad = 1;
    delay(2000);
  }
  if (!digitalRead(pinP2) == 1) {
    //Se selecciono Nivel 2
    lcd.setCursor(8, 0);
    lcd.print("2");
    Velocidad = 2;
    delay(2000);
  }
  if (!digitalRead(pinP3) == 1) {
    //Se selecciono Nivel 3
    lcd.setCursor(8, 0);
    lcd.print("3");
    Velocidad = 3;
    delay(2000);
  }
  if (!digitalRead(pinP4) == 1) {
    //Se selecciono Nivel 4
    lcd.setCursor(8, 0);
    lcd.print("4");
    Velocidad = 4;
    delay(2000);
  }
  if (!digitalRead(pinP5) == 1) {
    //Se selecciono Nivel 5
    lcd.setCursor(8, 0);
    lcd.print("5");
    Velocidad = 5;
    delay(2000);

    }*/

}



void printFig(int x, int y, int fig[][4], int t, string figName, int rotation) {
  for (int i = 0; i < t; i++) {
    for (int j = 0; j < t; j++) {
      if (figName == "L" or figName == "Linv" or figName == "T") {
        switch (rotation) {
          case 0:
            canvas[x + i][y + j] = fig[i][j];
            break;
          case 1:
            canvas[x + i][y + j] = fig[j][t - 1 - i];
            break;
          case 2:
            canvas[x + i][y + j] = fig[t - 1 - i][t - 1 - j];
            break;
          case 3:
            canvas[x + i][y + j] = fig[t - 1 - j][i];
            break;
        }
      } else if (figName == "Z" or figName == "Zinv") {
        switch (rotation) {
          case 0:
            canvas[x + i][y + j] = fig[i][j];
            break;
          case 1:
            canvas[x + i][y + j] = fig[j][t - 1 - i];
            break;
        }
      } else {
        canvas[x + i][y + j] = fig[i][j];
      }
    }
  }
}

void printDisplay() {
  //Controlador del 74LS154
  int f = 0;
  int c = 1;
  for (int fil = 0; fil < 16; fil++) {
    for (int col = 0; col < 8; col++) {
      if (canvas[fil][col] == 1) {
        setCol(c);
        setFil(fil);
        delay(1);
      }
      c <<= 1;
    }
    c = 1;
  }
}
/*
  void Generacion_Figura() {
  int Matriz_impresion[][];
  num_fig_ale = random(1, 7);
  switch (num_fig_ale) {
    case 1:
      Figura_Random = "L";
      Matriz_impresion = L;
      break;
    case 2:
      Figura_Random = "Linv";
      Matriz_impresion = Linv;
      break;
    case 3:
      Figura_Random = "Z";
      Matriz_impresion = Z;
      break;
    case 4:
      Figura_Random = "Zinv";
      Matriz_impresion = Zinv;
      break;
    case 5:
      Figura_Random = "Line";
      Matriz_impresion = line;
      break;
    case 6:
      Figura_Random = "T";
      Matriz_impresion = T;
      break;
    case 7:
      Figura_Random = "Cube";
      Matriz_impresion = sqr;
      break;
  }
  return Matriz_impresion;
  }
*/

void setOFF() {
  digitalWrite(pinC1, LOW);
  digitalWrite(pinC2, LOW);
  digitalWrite(pinC3, LOW);
  digitalWrite(pinC4, LOW);
  digitalWrite(pinC5, LOW);
  digitalWrite(pinC6, LOW);
  digitalWrite(pinC7, LOW);
  digitalWrite(pinC8, LOW);
}
void setCol(int col) {
  digitalWrite(pinC1, col & 0x01);
  digitalWrite(pinC2, col & 0x02);
  digitalWrite(pinC3, col & 0x04);
  digitalWrite(pinC4, col & 0x08);
  digitalWrite(pinC5, col & 0x10);
  digitalWrite(pinC6, col & 0x20);
  digitalWrite(pinC7, col & 0x40);
  digitalWrite(pinC8, col & 0x80);
}
void setFil(int fil) {
  digitalWrite(pinSA, fil & 0x01);
  digitalWrite(pinSB, fil & 0x02);
  digitalWrite(pinSC, fil & 0x04);
  digitalWrite(pinSD, fil & 0x08);
}
void Pantalla_Inicio() {
  lcd.clear();
  lcd.setCursor(2, 0); //Ubicar cursor en la columna 3 fila 0
  lcd.print("!Bienvenido¡"); //Imprimir mensaje en la LCD
  lcd.setCursor(2, 1); //Ubicar cursor en la columna 3 fila 0
  lcd.print("PULSE INICIO"); //Imprimir mensaje en la LCD
}
void Pantalla_Selector_Nivel() {
  lcd.clear();
  lcd.setCursor(0, 0); //Ubicar cursor en la columna 3 fila 0
  lcd.print("Seleccione"); //Imprimir mensaje en la LCD
  lcd.setCursor(4, 1); //Ubicar cursor en la columna 3 fila 0
  lcd.print("Nivel"); //Imprimir mensaje en la LCD
  delay(1000);
}
void Pantalla_Nivel() {
  lcd.clear();
  lcd.setCursor(0, 0); //Ubicar cursor en la columna 3 fila 0
  lcd.print("Nivel:"); //Imprimir mensaje en la LCD
  lcd.setCursor(10, 0);
  lcd.print("Maximo:"); //Imprimir mensaje en la LCD
  lcd.setCursor(0, 1);
  lcd.print("Score:"); //Imprimir mensaje en la LCD
}
