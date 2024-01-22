#define LED 2
#define PWMChannel 0 //Canal PWM utilizado (valor entre 0 y 15)
#define PWMResolution 12 // Resolución de 12 (valor entre 1 y 16)
#define PWMFreq 5000 //Frecuencia del PWM a 5KHz
#define ADC1_CH6 34 //Canal 6 del ADC1

void setup() {
  Serial.begin(115200);
  ledcSetup(PWMChannel,PWMFreq,PWMResolution); //Configurar canal 0 del PWM
  ledcAttachPin(LED,PWMChannel); //Asociar el pin LED (GPIO2) al canal 0 del PWM
  ledcWrite(PWMChannel,0); //Valor inicial del ciclo útil del PWM
}

void loop() {
  uint16_t ciclo=analogRead(ADC1_CH6);
  ledcWrite(PWMChannel,ciclo); //Actualizar ciclo útil entre 0.0% y 100.0%
  Serial.print((ciclo*100/4095.0),1); //Escalizar ciclo útil entre 0.0% y 100.0%
  Serial.println('%');
  delay(1000);
}
