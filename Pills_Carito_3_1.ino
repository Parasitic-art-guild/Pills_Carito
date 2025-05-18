//freno izquierdo
const int iniciosecuenciallenado = 10;

//Secuencia llenado
const int motorPin = 4;                        // Pin al que está conectado el motor
const int sensorPin = 8;                       // Pin del sensor que detecta la leva
const unsigned long tiempoInicioMotor = 5000;  // Tiempo de espera para activar el motor (en milisegundos)
const unsigned long tiempoParadaMotor = 3000;  // Tiempo que el motor se mantiene encendido tras detectar la leva

unsigned long tiempoInicio = 0;
unsigned long tiempoDeteccionLeva = 0;
bool motorActivo = false;
bool esperandoParo = false;
bool finsecuenciallenado = false;

  void setup() {
  Serial.begin(19200);
  pinMode(iniciosecuenciallenado, INPUT);
  digitalRead(iniciosecuenciallenado);
  pinMode(motorPin, OUTPUT);  // Configurar el pin del motor como salida
  pinMode(sensorPin, INPUT);  // Configurar el pin del sensor como entrada
  tiempoInicio = millis();    // Registrar el tiempo inicial
}

void tarea4() {
  if (digitalRead(iniciosecuenciallenado)) {
    // Activar el motor después de un tiempo de espera
    if (!finsecuenciallenado && !motorActivo && millis() - tiempoInicio >= tiempoInicioMotor) {
      digitalWrite(motorPin, HIGH);
      motorActivo = true;
      Serial.println("Motor activado.");
    }

    // Detectar la leva y preparar el paro del motor
    if (!finsecuenciallenado && motorActivo && !esperandoParo && digitalRead(sensorPin) == HIGH) {
      Serial.println("Leva detectada. Preparando para detener el motor...");
      tiempoDeteccionLeva = millis();  // Registrar el momento en que se detectó la leva
      esperandoParo = true;
    }
    // Detener el motor después del tiempoParadaMotor
    if (!finsecuenciallenado && esperandoParo && millis() - tiempoDeteccionLeva >= tiempoParadaMotor) {
      digitalWrite(motorPin, LOW);  // Apagar el motor
      motorActivo = false;          // Resetear estado del motor


      esperandoParo = false;    // Resetear estado de espera
      tiempoInicio = millis();  // Reiniciar el tiempo inicial
      Serial.println("Motor detenido.");
      finsecuenciallenado = true;
    }
  } else {
    tiempoInicio = millis();
    finsecuenciallenado = false;
  }
}

void loop() {
  tarea4();  //secuencia de llenado, se activa plato tolva con delay y se para con delay cuando el sensor ya observo la leva.
}
