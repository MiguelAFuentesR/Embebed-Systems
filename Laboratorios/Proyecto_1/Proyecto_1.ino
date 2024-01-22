
//################### 1.Definición de Librerias ###################
using namespace std;
#include <LiquidCrystal.h>

//################### 2. Definición de Variables ###################

//Pines de las Columnas


#define pinC1 12
#define pinC2 1
#define pinC3 22
#define pinC4 3
#define pinC5 23
#define pinC6 13
#define pinC7 14
#define pinC8 27




//Pines de las filas
#define pinSA 2
#define pinSB 16
#define pinSC 17
#define pinSD 5

/*3
  Pines con resistencia de pull-up interna (INPUT_PULLUP):
  GPIO14, GPIO16, GPIO17, GPIO18, GPIO19, GPIO21, GPIO22 y GPIO23.
*/


//Pines de los Pulsadores
//#define pinP1 16 //Pulsador de Inicio 
#define pinP1 35 //Pulsador de Inicio 

#define pinP2 34 //Pulsador de Arriba     Sentido = 1
#define pinP3 18 //Pulsador de Abajo      Sentido = 2 
#define pinP4 19 //Pulsador de Izquierda  Sentido = 3
#define pinP5 21 //Pulsador de Derecha    Sentido = 4

// ----------- PRUEBAS  -------------------
#define LED 2 //Define GPIO2



//Pines de la Pantalla

//Define los pines utilizados del ESP32 de acuerdo a la sintaxis de la libreria
const uint8_t RS = 15, EN = 4, D4 = 26, D5 = 25, D6 = 33, D7 = 32;

//################### 3.Inicialización de Variables ###################

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //Define el objeto "lcd"


//--------------- Pulsadores -----------------
volatile uint8_t bandera_P1, bandera_P2, bandera_P3, bandera_P4, bandera_P5 ;
volatile uint16_t tiempo_P1, tiempo_P2, tiempo_P3, tiempo_P4, tiempo_P5;
volatile uint32_t rebote_P1, rebote_P2, rebote_P3, rebote_P4, rebote_P5;
int contador_P1 = 0;
int contador_P2 = 0;
int contador_P3 = 0;
int contador_P4 = 0;
int contador_P5 = 0;

//--------------------------

//Variables Auxiliares
int Nivel = 1;
int Sentido = 0;
bool Seleccion_Nivel = true;
bool Inicio_Juego = false;
bool Pausa_Juego = false;

int Velocidad = 1;
int num_fig_ale;

int x = 0;
int y = 0;
int n = 3;


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

//********************** PARA PULSADORES **********************
void IRAM_ATTR Int_P1() {
  contador_P1++;
  Rebote_P1();
  if (Inicio_Juego) {
    //Se activa la Funcionalidad de Pausa y Despausa
    if (Pausa_Juego) {
      Pausa_Juego = false;
    } else {
      Pausa_Juego = true;
    }

  }
}
void IRAM_ATTR Int_P2() {
  contador_P2++;
  Rebote_P2();

  if (Inicio_Juego) {
    if (Pausa_Juego) {
      Sentido = 0;
    } else {
      Sentido = 1; //Arriba
    }
  }


}
void IRAM_ATTR Int_P3() {
  contador_P3++;
  Rebote_P3();
  
  if (Inicio_Juego) {
    if (Pausa_Juego) {
      Sentido = 0;
    } else {
      Sentido = 2; //Abajo
    }
  }
  
}
void IRAM_ATTR Int_P4() {
  contador_P4++;
  Rebote_P4();
  
  if (Inicio_Juego) {
    if (Pausa_Juego) {
      Sentido = 0;
    } else {
      Sentido = 3; //Izquierda
    }
  }
  
}
void IRAM_ATTR Int_P5() {
  contador_P5++;
  Rebote_P5();
  
  if (Inicio_Juego) {
    if (Pausa_Juego) {
      Sentido = 0;
    } else {
      Sentido = 4; //Derecha
    }
  }
  
}
//**************************************************


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

  //Configuración Interrupciones Pulsadores
  attachInterrupt(digitalPinToInterrupt(pinP1), Int_P1, FALLING); //Habilita int. generada por el GPIO16
  attachInterrupt(digitalPinToInterrupt(pinP2), Int_P2, FALLING); //Habilita int. generada por el GPIO16
  attachInterrupt(digitalPinToInterrupt(pinP3), Int_P3, FALLING); //Habilita int. generada por el GPIO16
  attachInterrupt(digitalPinToInterrupt(pinP4), Int_P4, FALLING); //Habilita int. generada por el GPIO16
  attachInterrupt(digitalPinToInterrupt(pinP5), Int_P5, FALLING); //Habilita int. generada por el GPIO16
  tiempo_P1 = 250; tiempo_P2 = 250; tiempo_P3 = 250; tiempo_P4 = 250; tiempo_P5 = 250;
  bandera_P1 = 0; bandera_P2 = 0; bandera_P3 = 0; bandera_P4 = 0; bandera_P5 = 0;


}

void loop() {

  //Inicio Juego
  Pantalla_Inicio();
  if (Seleccion_Nivel) {
    if (contador_P1 > 0) {
      Pantalla_Nivel();
      if (contador_P1 > 5) {
        contador_P1 = 1;
      }
      lcd.setCursor(8, 0);
      lcd.print(contador_P1);

      //Selección Nivel

      if (contador_P2 > 0) {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Selecciono el ");
        lcd.setCursor(2, 1);
        lcd.print("Nivel ");
        lcd.print(contador_P1);
        delay(2000);
        Nivel = contador_P1;
        contador_P2 = 0;
        Seleccion_Nivel = false;
        Inicio_Juego = true;
      }

    } else {
      Pantalla_Selector_Nivel();
      contador_P2 = 0;
      contador_P3 = 0;
      contador_P4 = 0;
      contador_P5 = 0;

    }

  }

  if (Inicio_Juego) {
    if (Pausa_Juego) {
      Pantalla_Pausa();
    } else {
      Pantalla_Juego(Nivel);
      lcd.setCursor(7, 1);
      switch (Sentido) {
        case 0:
        lcd.print("Def");
        break;
        case 1:
        lcd.print("Up");
          break;
        case 2:
        lcd.print("Down");
          break;
        case 3:
        lcd.print("Left");
          break;
        case 4:
        lcd.print("Right");
          break;
      }

    //Pruebas Pantalla






      
    }
  }

  Pulsador1_();
  Pulsador2_();
  Pulsador3_();
  Pulsador4_();
  Pulsador5_();
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



void Pantalla_Inicio() {
  lcd.clear();
  lcd.setCursor(2, 0); //Ubicar cursor en la columna 3 fila 0
  lcd.print("Bienvenido"); //Imprimir mensaje en la LCD
  lcd.setCursor(2, 1); //Ubicar cursor en la columna 3 fila 0
  lcd.print("Pulse P1"); //Imprimir mensaje en la LCD
  lcd.clear();
}
void Pantalla_Selector_Nivel() {
  lcd.clear();
  lcd.setCursor(2, 0); //Ubicar cursor en la columna 3 fila 0
  lcd.print("Seleccione"); //Imprimir mensaje en la LCD
  lcd.setCursor(4, 1 ); //Ubicar cursor en la columna 3 fila 0
  lcd.print("Nivel con P1"); //Imprimir mensaje en la LCD
}
void Pantalla_Nivel() {
  //lcd.clear();
  lcd.setCursor(2, 0); //Ubicar cursor en la columna 3 fila 0
  lcd.print("Nivel: "); //Imprimir mensaje en la LCD
  lcd.setCursor(4, 1);
  lcd.print("Jugar(P2)"); //Imprimir mensaje en la LCD
}
void Pantalla_Juego(int nivel) {
  lcd.clear();
  lcd.setCursor(0, 0); //Ubicar cursor en la columna 3 fila 0
  lcd.print("Nivel: "); //Imprimir mensaje en la LCD
  lcd.print(nivel); //Imprimir mensaje en la LCD
  lcd.setCursor(10, 0);
  lcd.print("Maximo:"); //Imprimir mensaje en la LCD
  lcd.setCursor(0, 1);
  lcd.print("Score:"); //Imprimir mensaje en la LCD
}

void Pantalla_Pausa() {
  //lcd.clear();
  lcd.setCursor(2, 0); //Ubicar cursor en la columna 3 fila 0
  lcd.print("Juego Pausado"); //Imprimir mensaje en la LCD
  lcd.setCursor(2, 1);
  lcd.print("Reanudar (P1)"); //Imprimir mensaje en la LCD
}


//*************** PULSADORES *************************

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
