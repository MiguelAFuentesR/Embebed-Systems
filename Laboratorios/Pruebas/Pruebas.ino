
//################### 1.Definición de Librerias ###################
using namespace std;
#include <LiquidCrystal.h>
#include <Preferences.h>

Preferences preferences;
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
#define pinSC 5
#define pinSD 17

/*
  Pines con resistencia de pull-up interna (INPUT_PULLUP):
  GPIO14, GPIO16, GPIO17, GPIO18, GPIO19, GPIO21, GPIO22 y GPIO23.
*/


//Pines de los Pulsadores



//#define pinP1 16 //Pulsador de Inicio
#define pinP1 21 //Pulsador de Inicio 

#define pinP2 34 //Pulsador de Arriba     Sentido = 1
#define pinP3 19 //Pulsador de Abajo       Sentido = 2 
#define pinP4 18//Pulsador de Derecha         Sentido = 3
#define pinP5 35 //Pulsador de Izquierda        Sentido = 4


// ----------- PRUEBAS  -------------------
//#define LED 2 //Define GPIO2



//Pines de la Pantalla

//Define los pines utilizados del ESP32 de acuerdo a la sintaxis de la libreria
const uint8_t RS = 15, EN = 4, D4 = 26, D5 = 25, D6 = 33, D7 = 32;

//################### 3.Inicialización de Variables ###################

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //Define el objeto "lcd"

// Memoria
unsigned int puntaje_maximo;


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

//Banderas

bool Pantalla_inicio = true;
bool Seleccion_Nivel = false;
bool Inicio_Juego = false;
bool Pausa_Juego = false;
bool Siguiente_Figura = false;

int Velocidad = 2000000;
int Score = 0;
int num_fig_ale;

int posFil = -1;
int posCol = 0;
int contG = 0;


int Tiempo_Rebote = 250;
int Tiempo_Rebote_sup = 300;
int Tiempo_Rebote_inf = 100;

int x = 0;
int y = 0;
int n = 3;

int Columnas_Encendidas = 0;
int Filas_Llenas = 0;

bool Eliminar_Fila = false;
int Fila_Borrada = 0;
int Filas_Eliminadas = 0;


int limite = 8;
//************* Matrices **********************
volatile int rotation = 0;
//********************** TIMMERS ******************************
volatile uint8_t bandera; //
volatile uint8_t bandera1; //
volatile uint16_t tiempo; //

hw_timer_t *timer1 = NULL;


// Definición de Figuras
String Figura_Random;

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

int mem[17][8] = {
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
  { 0, 0, 0, 0, 0, 0, 0, 0 },  // 16
  { 1, 1, 1, 1, 1, 1, 1, 1 }
};

int canvas[17][8] = {
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
  { 0, 0, 0, 0, 0, 0, 0, 0 }, // 16
  { 1, 1, 1, 1, 1, 1, 1, 1 }
};





//auxiliar
int figRotate[4][4] = {
  { 0, 0, 0, 0 },  // 1
  { 0, 0, 0, 0 },  // 2
  { 0, 0, 0, 0 },  // 3
  { 0, 0, 0, 0 },  // 4
};



// DEFINICION INTERRUPCIONES :



//********************** PARA PULSADORES **********************
void IRAM_ATTR Int_P1() {
  contador_P1++;
  Rebote_P1();

  // 1 Funcionalidad : Iniciar el Juego
  if (Pantalla_inicio) {
    //Nivel = contador_P1;
    contador_P1 = 0;
    contador_P2 = 0;
    contador_P3 = 0;
    contador_P4 = 0;
    contador_P5 = 0;
    Cambio_Nivel();
    Velocidad_Nivel();
    Seleccion_Nivel = false;
    Pantalla_inicio = false;
    Inicio_Juego = true;
    delay(1000);
    Pantalla_Juego(Nivel);
    lcd.setCursor(11, 1);
    lcd.print(puntaje_maximo);
  }

  // 2 Funcionalidad : Boton de Pausa

  if (Inicio_Juego) {
    //Se activa la Funcionalidad de Pausa y Despausa
    if (contador_P1 > 0) {

      if (Pausa_Juego) {
        Pausa_Juego = false;
        Pantalla_Juego(Nivel);
      } else {
        Pausa_Juego = true;
        Desactivar_Timer();
        Pantalla_Pausa();
      }
    }

  }
}

void doRotable() {
  if (num_fig_ale == 1 || num_fig_ale == 2) { // L Linv
    if (posCol == 6 ) {
      if (rotation == 0 || rotation == 2) {
          posCol--;
      }
    }
   }else if (num_fig_ale == 6) { //T
      if (posCol == 6 ) {
        if (rotation == 1 || rotation == 3) {
            posCol--;
        }
      }
    }else if (num_fig_ale == 3 || num_fig_ale == 4) { // Z Zinv
      if (posCol == 6 ) {
        if (rotation == 1) {
            posCol--;
        }
      }
    }else if (num_fig_ale == 5) {// Line
      if (posCol == 7 ) {
        if (rotation == 0 || rotation == 2) {
            posCol-= 3;
        }
      }
    }
}

void IRAM_ATTR Int_P2() {
  contador_P2++;
  Rebote_P2();
  // 1 Funcionalidad : Boton de arriba
  if (Inicio_Juego) {

    if (Pausa_Juego) {

    } else {
      //doRotable();
      switch (num_fig_ale) {
        case 1:
          rotacion("L");
          break;
        case 2:
          rotacion("Linv");
          break;
        case 3:
          rotacion("Z");
          break;
        case 4:
          rotacion("Zinv");
          break;
        case 5:
          rotacion("Line");
          break;
        case 6:
          rotacion("T");
          break;
        case 7:
          rotacion("Cube");
          break;
      }

      Sentido = 1; //Arriba
    }
  }
}
void IRAM_ATTR Int_P3() {
  contador_P3++;
  Rebote_P3();
  // 1 Funcionalidad : Boton Abajo
  if (Inicio_Juego) {
    if (Pausa_Juego) {
      Sentido = 0;
    } else {
      Sentido = 2; //Abajo
      if (posFil < 16) {
        posFil = posFil + 1;
      }
    }
  }
}

void IRAM_ATTR Int_P4() {
  contador_P4++;
  Rebote_P4();
// 1 Funcionalidad : Boton Derecha
  if (Inicio_Juego) {
    if (Pausa_Juego) {
      Sentido = 0;
    } else {
      Sentido = 3; //Derecha
      if (posFil > 0) {
        if (posCol < 7) {
          posCol = posCol + 1;
        }
      }
    }
  }
}



//void IRAM_ATTR Int_P4() {
//  contador_P4++;
//  Rebote_P4();
//  // 1 Funcionalidad : Boton Derecha
//  if (Inicio_Juego) {
//    if (Pausa_Juego) {
//      Sentido = 0;
//    } else {
//      posCol++;
//      Sentido = 3; //Derecha
//      if (posCol >= 0) {
////        if (num_fig_ale == 1 || num_fig_ale == 2) { // L Linv
//////          if (rotation == 0 || rotation == 2) {
//////              if (posCol < 7 ) {
//////                posCol++;
//////              }
//////          }else{
//////            if (posCol < 6 ) {
//////                posCol++;
//////              }
//////          }
////          posCol++;
////        }else if (num_fig_ale == 6) { //T
////          if (rotation == 1 || rotation == 3) {
////              if (posCol < 6 ) {
////                posCol++;
////              }
////          }else{
////            if (posCol < 5 ) {
////                posCol++;
////              }
////          }
////        }else if (num_fig_ale == 3 || num_fig_ale == 4) { // Z Zinv
////          if (rotation == 1) {
////              if (posCol < 6 ) {
////                posCol++;
////              }
////          }else{
////              if (posCol < 5 ) {
////                posCol++;
////              }
////          }
////        }else if (num_fig_ale == 5) {// Line
////          if (rotation == 0) {
////              if (posCol < 7 ) {
////                posCol++;
////              }
////          }else{
////            if (posCol < 4 ) {
////                posCol++;
////              }
////          }
////        }else if (num_fig_ale == 7) {// Square
////          if (posCol < 6 ) {
////            posCol++;
////          }
////        }
//      }
//    }
//  }
//}

void IRAM_ATTR Int_P5() {
  contador_P5++;
  Rebote_P5();
  // 1 Funcionalidad : Boton Izquierda
  if (Inicio_Juego) {
    if (Pausa_Juego) {
      Sentido = 0;
    } else {
      Sentido = 4; //Izquierda
      if (posFil > 0) {
        if (posCol > 0) {
          posCol = posCol - 1;
        }
      }
    }
  }
}
//******************* TIMMERS *******************************

void IRAM_ATTR Int_Timer1() {
  Generacion_Figura();
  Siguiente_Figura = true;
}


void setup() {
  lcd.begin(16, 2); //Configurar LCD de tamaño 16x2

  //Configuracion Pulsadores
  pinMode(pinP1, INPUT_PULLUP); 
  pinMode(pinP2, INPUT_PULLUP);
  pinMode(pinP3, INPUT_PULLUP); 
  pinMode(pinP4, INPUT_PULLUP); 
  pinMode(pinP5, INPUT_PULLUP); 

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
  tiempo_P1 = Tiempo_Rebote; tiempo_P2 = Tiempo_Rebote; tiempo_P3 = Tiempo_Rebote; tiempo_P4 = Tiempo_Rebote; tiempo_P5 = Tiempo_Rebote;
  bandera_P1 = 0; bandera_P2 = 0; bandera_P3 = 0; bandera_P4 = 0; bandera_P5 = 0;


  bandera = 0; tiempo = 0; bandera1 = 0;
  timer1 = timerBegin(1, 80, true); //Configura Timer 1 con preesc.x80 (=1MHz) y cambio por flanco de bajada
  //Serial.begin(115200);
  Lectura_memoria();

}

void loop() {
  /*lcd.setCursor(0, 0); //Ubicar cursor en la columna 3 fila 0
    lcd.print("Maximo : "); //Imprimir mensaje en la LCD
    lcd.print(puntaje_maximo);*/

  if (Pantalla_inicio) {
    Pantalla_Inicio();
  }

  if (Inicio_Juego) {
    contador_P1 = 0;
    contador_P2 = 0;
    contador_P3 = 0;
    contador_P4 = 0;
    contador_P5 = 0;
    if (Pausa_Juego) {
    } else {
      if (posFil == -1) {
        num_fig_ale = random(1, 8);
        posCol = 4;
        rotation = 0;
        perdiste();
      }
      Activar_Timer();
    }
  }
  printDisplay();
  Pulsadores();
}

void perdiste() {
  for (int c = 0; c < 8; c++) {
    if ((canvas[1][c]) == 1) {
      Desactivar_Timer();
      lcd.clear();
      lcd.setCursor(3, 0); 
      lcd.print(" PERDISTE "); 
      clearcanvas();
      Score = 0;
      Nivel = 1;
      delay(1000);
      Pantalla_Juego(Nivel);
      if (Score > puntaje_maximo) {  
        puntaje_maximo = Score;
        Escritura_memoria();
      }
    }
  }
}

void Cambio_Nivel() {
  if (Score >= 20 && Score < 50) {
    //Entrar a nivel 2
    Nivel = 2;
  } else if (Score >= 50 && Score < 100) {
    //Entrar a nivel 3
    Nivel = 3;
  } else if (Score >= 100 && Score < 150) {
    //Entrar a nivel 4
    Nivel = 4;
  } else if (Score >= 150) {
    //Entrar a nivel 5
    Nivel = 5;
  } else {
    Nivel = 1;
  }
}

void Lectura_memoria() {
  preferences.begin("puntaje_maximo", false);
  puntaje_maximo = preferences.getUInt("puntaje_maximo", 0);
  preferences.end();

}
void Escritura_memoria() {
  preferences.begin("puntaje_maximo", false);
  preferences.putUInt("puntaje_maximo", puntaje_maximo);
  preferences.end();
}

void Activar_Timer() {

  timerAttachInterrupt(timer1, Int_Timer1, true); //Hab. int del Timer 1
  timerAlarmWrite(timer1, Velocidad, true); 
  timerAlarmEnable(timer1); //Habilitar el Timer 1
}
void Desactivar_Timer() {
  timerRestart(timer1);
  timerAlarmDisable(timer1); //Habilitar el Timer 1
}

int checkRowAll() {
  for (int f = 0; f < 16; f++) {
    if (canvas[f][0] & canvas[f][1] & canvas[f][2] & canvas[f][3] & canvas[f][4] & canvas[f][5] & canvas[f][6] & canvas[f][7]) {
      return f;
    }
  }
  return -1;
}

void downCanvas(int row) {
  for (int f = row; f > 0; f--) {
    canvas[f][0] = canvas[f - 1][0];
    canvas[f][1] = canvas[f - 1][1];
    canvas[f][2] = canvas[f - 1][2];
    canvas[f][3] = canvas[f - 1][3];
    canvas[f][4] = canvas[f - 1][4];
    canvas[f][5] = canvas[f - 1][5];
    canvas[f][6] = canvas[f - 1][6];
    canvas[f][7] = canvas[f - 1][7];
  }
  for (int c = 0; c < 8; c++) {
    canvas[0][c] = 0;
  }
}

void getScore() {
  uint8_t lines = 0;
  int row = 0;
  do {
    row = checkRowAll();
    if (row != -1) {
      downCanvas(row);
      lines++;
    }
  } while (row != -1);
  if (lines > 0) {
    switch (lines) {
      case 1:
        Score += 1;
        break;
      case 2:
        Score += 3;
        break;
      case 3:
        Score += 6;
        break;
      case 4:
        Score += 10;
        break;
      default:
        Score += 10;
        break;
    }
    lcd.setCursor(7, 1);
    lcd.print(Score);
    Cambio_Nivel();
    lcd.setCursor(7, 0);
    lcd.print(Nivel);
  }

}


void Velocidad_Nivel() {

  switch (Nivel) {
    case 1:
      Velocidad = 500000;
      break;
    case 2:
      Velocidad = 400000;
      break;
    case 3:
      Velocidad = 350000;
      break;
    case 4:
      Velocidad = 300000;
      break;
    case 5:
      Velocidad = 250000;
      break;
  }
}

void Generacion_Figura() {
  doRotable();
  switch (num_fig_ale) {
    case 1:
      Figura_Random = "L";
      stepDown(L, 3, "L", rotation);
      break;
    case 2:
      Figura_Random = "Linv";
      stepDown(Linv, 3, "Linv", rotation);
      break;
    case 3:
      Figura_Random = "Z";
      stepDown(Z, 3, "Z", rotation);
      break;
    case 4:
      Figura_Random = "Zinv";
      stepDown(Zinv, 3, "Zinv", rotation);
      break;
    case 5:
      Figura_Random = "Line";
      stepDown(line, 4, "Line", rotation);
      break;
    case 6:
      Figura_Random = "T";
      stepDown(T, 3, "T", rotation);
      break;
    case 7:
      Figura_Random = "Cube";
      stepDown(sqr, 2, "Cube", rotation);
      break;
  }
}


void Pulsadores() {
  if (bandera_P1) {
    Pulsador1_();
  } else if (bandera_P2) {
    Pulsador2_();
  } else if (bandera_P3) {
    Pulsador3_();
  } else if (bandera_P4) {
    Pulsador4_();
  } else if (bandera_P5) {
    Pulsador5_();
  }
}

//----------------------------------------------FUNCIONES MATRICES ------------------------------

bool rowIsUsed(uint8_t row) {
  for (int col = 0; col < 8; col++) {
    if (canvas[row][col] == 1) return true;
  }
}

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
  digitalWrite(pinSA, (15 - fil) & 0x01);
  digitalWrite(pinSB, (15 - fil) & 0x02);
  digitalWrite(pinSC, (15 - fil) & 0x04);
  digitalWrite(pinSD, (15 - fil) & 0x08);
}

void printDisplay() {
  int f = 0;
  int c = 1;
  for (int fil = 0; fil < 16; fil++) {
    for (int col = 0; col < 8; col++) {
      if (canvas[fil][col] == 1 || mem[fil][col] == 1) {
        //Serial.print("ON");
        setCol(c);
        setFil(fil);
        delayMicroseconds(110);
      }else{
        setOFF();
      }
      c <<= 1;
    }
    c = 1;
  }
  setOFF();
}
void clearmem() {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 8; j++) {
      mem[i][j] = 0;
    }
  }

}
void clearcanvas() {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 8; j++) {
      canvas[i][j] = 0;
    }
  }

}
void stepDown(int fig[][4], int t, string figName, int rotation) {
  createRotation(fig, t, figName, rotation);
  if (check_printFig(posFil + 1, posCol, t)) {
    posFil++;
    clearmem();
    printFig(posFil, posCol, t);

  } else {
    mem_to_canvas();
    posFil = -1;
  }
  getScore();
}

//void createRotation(int fig[][4], int t, string figName, int rotation) {
//  clear_figRotate();
//  for (int i = 0; i < t; i++) {
//    for (int j = 0; j < t; j++) {
//      if (figName == "L" or figName == "Linv" or figName == "T") {
//        switch (rotation) {
//          case 0:
//            figRotate[i][j] = fig[i][j];
//            break;
//          case 1:
//            figRotate[i][j] = fig[j][t - 1 - i];
//            break;
//          case 2:
//            if(j != 0 && (figName == "Linv" || figName == "L")){
//              figRotate[i][j-1] = fig[t - 1 - i][t - 1 - j];
//            }else{
//              figRotate[i][j] = fig[t - 1 - i][t - 1 - j];
//            }
//            break;
//          case 3:
//            if(j != 0 && figName == "T"){
//              figRotate[i][j-1] = fig[t - 1 - j][i];
//            }else{
//              figRotate[i][j] = fig[t - 1 - j][i];
//            }
//            
//            break;
//        }
//      } else if (figName == "Z" or figName == "Zinv" or figName == "Line") {
//        switch (rotation) {
//          case 0:
//            figRotate[i][j] = fig[i][j];
//            break;
//          case 1:
//            figRotate[i][j] = fig[j][t - 1 - i];
//            break;
//        }
//      } else {
//        figRotate[i][j] = fig[i][j];
//      }
//    }
//  }
//}


void createRotation(int fig[][4], int t, string figName, int rotation) {
  clear_figRotate();
  for (int i = 0; i < t; i++) {
    for (int j = 0; j < t; j++) {
      if (figName == "L" or figName == "Linv" or figName == "T") {
        switch (rotation) {
          case 0:
            figRotate[i][j] = fig[i][j];
            break;
          case 1:
            figRotate[i][j] = fig[j][t - 1 - i];
            break;
          case 2:
            figRotate[i][j] = fig[t - 1 - i][t - 1 - j];
            break;
          case 3:
            figRotate[i][j] = fig[t - 1 - j][i];
            break;
        }
      } else if (figName == "Z" or figName == "Zinv") {
        switch (rotation) {
          case 0:
            figRotate[i][j] = fig[i][j];
            break;
          case 1:
            figRotate[i][j] = fig[j][t - 1 - i];
            break;
        }
      } else {
        figRotate[i][j] = fig[i][j];
      }
    }
  }
}


void clear_figRotate() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figRotate[i][j] = 0;
    }
  }
}

bool check_printFig(int x, int y, int t) {
  for (int f = 0; f < t; f++) {
    for (int c = 0; c < t; c++) {
      if (figRotate[f][c] == 1) {
        if (canvas[x + f][y + c] == 1) {
          return false;
        }
      }
    }
  }
  return true;
}

void mem_to_canvas() {
  for (int f = 0; f < 16; f++) {
    for (int c = 0; c < 8; c++) {
      if (mem[f][c] == 1) {
        canvas[f][c] = 1;
      }
    }
  }
}
bool printFig(int x, int y, int t) {
  for (int f = 0; f < t; f++) {
    for (int c = 0; c < t; c++) {
      if (figRotate[f][c] == 1) {
        mem[x + f][y + c] = 1;
      }
    }
  }
}

void rotacion(string figName) {
  if (figName == "L" or figName == "Linv" or figName == "T") {
    if (rotation < 3) {
      rotation++;
    } else {
      rotation = 0;
    }

  } else if (figName == "Z" or figName == "Zinv" or figName == "Line") {
    if (rotation < 1) {
      rotation++;
    } else {
      rotation = 0;
    }
  } else {
    rotation = 0;
  }
}



void Pantalla_Inicio() {

  lcd.setCursor(2, 0); 
  lcd.print("Bienvenido"); 
  lcd.setCursor(2, 1); 
  lcd.print("Pulse P1"); 
}

void Pantalla_Nivel() {
  delay(1000);

  lcd.setCursor(2, 0);
  lcd.print("Nivel: "); 
  lcd.setCursor(4, 1);
  lcd.print("Jugar(P2)"); 
}
void Pantalla_Juego(int nivel) {
  //delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Nivel: "); 
  lcd.print(nivel); 
  lcd.setCursor(10, 0);
  lcd.print("Maximo:"); 
  lcd.setCursor(0, 1);
  lcd.print("Score: "); 
  lcd.print(Score);
  lcd.setCursor(11, 1);
  lcd.print(puntaje_maximo);
}

void Pantalla_Pausa() {
  lcd.clear();
  lcd.setCursor(2, 0); 
  lcd.print("Juego Pausado"); 
  lcd.setCursor(2, 1);
  lcd.print("Reanudar (P1)"); 
}


//*************** PULSADORES *************************

void Pulsador1_() {

  //delay(tiempo_P1);
  if (millis() - rebote_P1 > Tiempo_Rebote_sup && bandera_P1) {
    bandera_P1 = 0;
    attachInterrupt(digitalPinToInterrupt(pinP1), Int_P1, FALLING); 
  }
}
void Pulsador2_() {

  //delay(tiempo_P2);
  if (millis() - rebote_P2 > Tiempo_Rebote_sup && bandera_P2) {
    bandera_P2 = 0;
    attachInterrupt(digitalPinToInterrupt(pinP2), Int_P2, FALLING); 
  }
}
void Pulsador3_() {

  //delay(tiempo_P3);
  if (millis() - rebote_P3 > Tiempo_Rebote_sup && bandera_P3) {
    bandera_P3 = 0;
    attachInterrupt(digitalPinToInterrupt(pinP3), Int_P3, FALLING); 
  }
}
void Pulsador4_() {

  if (millis() - rebote_P4 > Tiempo_Rebote_sup && bandera_P4) {
    bandera_P4 = 0;
    attachInterrupt(digitalPinToInterrupt(pinP4), Int_P4, FALLING); 
  }
}
void Pulsador5_() {

  //delay(tiempo_P5);
  if (millis() - rebote_P5 > Tiempo_Rebote_sup && bandera_P5) {
    bandera_P5 = 0;
    attachInterrupt(digitalPinToInterrupt(pinP5), Int_P5, FALLING); 
  }
}
void Rebote_P1() {
  if (tiempo_P1 == Tiempo_Rebote) {
    tiempo_P1 = Tiempo_Rebote_inf;
  } else {
    tiempo_P1 = Tiempo_Rebote;
  }
  bandera_P1 = 1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote_P1 = millis(); //Lee el valor actual de la función millis()
  detachInterrupt(digitalPinToInterrupt(pinP1)); 
}

void Rebote_P2() {
  if (tiempo_P2 == Tiempo_Rebote) {
    tiempo_P2 = Tiempo_Rebote_inf;
  } else {
    tiempo_P2 = Tiempo_Rebote;
  }
  bandera_P2 = 1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote_P2 = millis(); //Lee el valor actual de la función millis()
  detachInterrupt(digitalPinToInterrupt(pinP2)); 
}
void Rebote_P3() {
  if (tiempo_P3 == Tiempo_Rebote) {
    tiempo_P3 = Tiempo_Rebote_inf;
  } else {
    tiempo_P3 = Tiempo_Rebote;
  }
  bandera_P3 = 1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote_P3 = millis(); //Lee el valor actual de la función millis()
  detachInterrupt(digitalPinToInterrupt(pinP3)); 
}
void Rebote_P4() {
  if (tiempo_P4 == Tiempo_Rebote) {
    tiempo_P4 = Tiempo_Rebote_inf;
  } else {
    tiempo_P4 = Tiempo_Rebote;
  }
  bandera_P4 = 1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote_P4 = millis(); //Lee el valor actual de la función millis()
  detachInterrupt(digitalPinToInterrupt(pinP4));
}
void Rebote_P5() {
  if (tiempo_P5 == Tiempo_Rebote) {
    tiempo_P5 = Tiempo_Rebote_inf;
  } else {
    tiempo_P5 = Tiempo_Rebote;
  }
  bandera_P5 = 1; //Activa bandera para indicar ingreso a rutina de interrupción
  rebote_P5 = millis(); //Lee el valor actual de la función millis()
  detachInterrupt(digitalPinToInterrupt(pinP5)); 
}
