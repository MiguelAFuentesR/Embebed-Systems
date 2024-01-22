/*
#include <Preferences.h>

Preferences preferences;

String Data[8] = {"", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};
String Days = "1,2,3,4;5,6;2,6;8,9";
String Datos;

String Estado_Leida;
String Evento_Leida;
String Interruptor_Leida;
String Fecha_Leida;
String Hora_Leida;
int cantidad_eventos_Leida;

String Estado_Memoria;// ON - OFF
String Evento_Memoria;// Programacion - Temporizador
String Interruptor_Memoria;//Pulsador - Conmutador
String Fecha_Memoria;
String Hora_Memoria;
int cantidad_eventos=0;



void setup() {
  Estado_Memoria = "0;1;1;0;1;0;0;0;1;1";
  Evento_Memoria = "1;1;1;1;1;0;0;0;0;0";
  Interruptor_Memoria = "0;0;0;0;0;1;1;1;1;1";
  Fecha_Memoria = "1,2,3,4;5,6;7,5;4,2;1,2,3,4;1,2,3,4;1,2,3,4;1,2,3,4;1,2,3,4;1,2,3,4;";
  Hora_Memoria = "86400;52084;52084;52084;52084;52084;52084;52084;52084;52084;52084";
  
  Serial.begin(115200);
  Serial.println();


  preferences.begin("Estado", false); // ON - OFF
  preferences.begin("Evento", false); // Programacion - Temporizador
  preferences.begin("Interruptor", false); //Pulsador - Conmutador
  preferences.begin("Fecha", false);
  preferences.begin("Hora", false);
  preferences.begin("cantidadeventos", false);
  

  
    //Leer
  Estado_Leida = preferences.getString("Estado", "");
  Evento_Leida = preferences.getString("Evento", "");
  Interruptor_Leida = preferences.getString("Interruptor", "");
  Fecha_Leida = preferences.getString("Fecha", "");
  Hora_Leida = preferences.getString("Hora", "");
  cantidad_eventos = preferences.getInt("cantidadeventos",0);

  cantidad_eventos++;
  
  //Almacenar
  preferences.putString("Estado", Estado_Memoria);
  preferences.putString("Evento", Evento_Memoria);
  preferences.putString("Interruptor", Interruptor_Memoria);
  preferences.putString("Fecha", Fecha_Memoria);
  preferences.putString("Hora", Hora_Memoria);
  preferences.putInt("cantidadeventos",cantidad_eventos);


  //Cerrar lectura de memoria
  preferences.end();

  Serial.println(Estado_Leida);
  Serial.println(Evento_Leida);
  Serial.println(Interruptor_Leida);
  Serial.println(Fecha_Leida);
  Serial.println(Hora_Leida);
  Serial.println(String(cantidad_eventos));
  Serial.println("You can restart the device now.");


}

void loop() {
  // put your main code here, to run repeatedly:

}
*/
// Para reriniciar la memoria :

  #include <nvs_flash.h>

  void setup() {
  nvs_flash_erase(); // erase the NVS partition and...
  nvs_flash_init(); // initialize the NVS partition.
  while (true);
  }

  void loop() {

  }
