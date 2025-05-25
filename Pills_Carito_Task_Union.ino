//sensor tarro
const int sensortarro = 12;
bool bitSiSensorTarroTarea11 = false;
bool bitSiSensorTarroTarea12 = false;
unsigned long tiempoSiSensorTarroTarea1 = 10000;
unsigned long tiempoNoSensorTarroTarea1 = 5000;
unsigned long tiempoInicioTarea11 = millis();
unsigned long tiempoInicioTarea12 = millis();
const int confirmacionlectura = 7;
bool bitconfirmacionlectura = false;

//freno izquierdo
const int frenoizquierdo = 5;

//freno derecho
const int frenoderecho = 6;

//secuencia de llenado
const int motorPin = 4;


// const int iniciosecuenciallenado = 10;
bool iniciosecuenciallenado;
const int sensorPin = 8;
const unsigned long tiempoInicioMotor = 5000;
const unsigned long tiempoParadaMotor = 3000;
unsigned long tiempoInicio = 0;
unsigned long tiempoDeteccionLeva = 0;
bool motorActivo = false;
bool esperandoParo = false;
bool finsecuenciallenado = false;

//secuencia liberación tarro
unsigned long tiempoInicioDerechoTarea3;
const unsigned long tiempoAperturaDerechoTarea3 = 5000;    // Retardo para abrir el cilindro derecho (en milisegundos)
const unsigned long tiempoCerrarDerechoTarea3 = 5000;      // Tiempo de apertura del cilindro derecho (en milisegundos)
const unsigned long tiempoAperturaIzquierdoTarea3 = 5000;  // Tiempo de apertura del cilindro izquierdo (en milisegundos)
const unsigned long tiempoCerrarIzquierdoTarea3 = 5000;
bool estadoDerecho = false;
bool estadoIzquierdo = false;
bool finalestadoDerecho = false;
bool finalestadoIzquierdo = false;
const int prueba = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(1200);
  pinMode(sensortarro, INPUT);
  pinMode(frenoizquierdo, OUTPUT);  //relacionado con cilindro izquierdo
  pinMode(frenoderecho, OUTPUT);
  pinMode(prueba, INPUT);
  pinMode(confirmacionlectura, OUTPUT);
  digitalWrite(frenoderecho, HIGH);
  // pinMode(iniciosecuenciallenado, INPUT);
  // digitalRead(iniciosecuenciallenado);
  pinMode(motorPin, OUTPUT);  // Configurar el pin del motor como salida
  pinMode(sensorPin, INPUT);  // Configurar el pin del sensor como entrada
  tiempoInicio = millis();    // Registrar el tiempo inicial
}

void tarea10() {
  if (digitalRead(sensortarro) && !bitSiSensorTarroTarea11 && millis() - tiempoInicioTarea11 >= tiempoSiSensorTarroTarea1) {
    //Se cumple si sensor ve tarro por tiempoSi y si bitSiSensor es false
    Serial.println("Presencia de tarro 11");
    bitconfirmacionlectura = true;
    digitalWrite(confirmacionlectura, HIGH);  // si sensor ve por tiempoSi entonces activa LED,
                                              // este codigo es representación visual de lectura
    bitSiSensorTarroTarea11 = true;           // es verdadera para que condicional no se repita y se active el condicional que
                                              // ve si el tarro una vez esta en posición se mueve por un tiempo tiempoNoSensor
    digitalWrite(frenoizquierdo, HIGH);
    bitSiSensorTarroTarea12 = false;  //codigo necesario para activar tarea 2
  } else {
    if (!digitalRead(sensortarro)) {
      tiempoInicioTarea11 = millis();  //si sensor no ve nada, el tiempo incial es igual a millis
    }
  }
  if (bitSiSensorTarroTarea11 && !bitSiSensorTarroTarea12 && !digitalRead(sensortarro) && millis() - tiempoInicioTarea12 >= tiempoNoSensorTarroTarea1) {
    bitconfirmacionlectura = false;
    Serial.println("Se perdio tarro");
    digitalWrite(confirmacionlectura, LOW);  // si sensor NO ve por tiempoNO entonces desactiva LED,
    bitSiSensorTarroTarea12 = true;          //para inhabilitar esta condicional o tarea.
    digitalWrite(frenoizquierdo, LOW);       // este codigo puede abrir el cilindro para que entre otro tarro}
                                             // tambien puede ser usado para detener el proceso de llenado, por ejemplo detener la tolva y el motor.
    bitSiSensorTarroTarea11 = false;         //codigo necesario para habilitar tarea 1
  } else {
    if (digitalRead(sensortarro)) {
      tiempoInicioTarea12 = millis();
    }
  }
}

void tarea20() {
  if (bitconfirmacionlectura /*digitalRead(iniciosecuenciallenado)*/) {
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

void tarea30() {
  if (digitalRead(prueba)) {
    // Manejo del cilindro derecho
    if (!finalestadoDerecho && !estadoDerecho && millis() - tiempoInicioDerechoTarea3 >= tiempoAperturaDerechoTarea3) {
      digitalWrite(frenoderecho, LOW);  // Abrir cilindro derecho
      Serial.println("Abrir cilindro derecho");
      estadoDerecho = true;
    }
    if (!finalestadoDerecho && estadoDerecho && millis() - tiempoInicioDerechoTarea3 - tiempoAperturaDerechoTarea3 >= tiempoCerrarDerechoTarea3) {
      digitalWrite(frenoderecho, HIGH);  // Abrir cilindro derecho
      Serial.println("Cerrar cilindro derecho");
      finalestadoDerecho = true;
    }
    if (!finalestadoIzquierdo && finalestadoDerecho && !estadoIzquierdo && millis() - tiempoInicioDerechoTarea3 - tiempoAperturaDerechoTarea3 - tiempoCerrarDerechoTarea3 >= tiempoAperturaIzquierdoTarea3) {
      digitalWrite(frenoizquierdo, LOW);  // Abrir cilindro derecho
      Serial.println("Abrir cilindro izquierdo");
      estadoIzquierdo = true;
    }
    if (!finalestadoIzquierdo && finalestadoDerecho && estadoIzquierdo && millis() - tiempoInicioDerechoTarea3 - tiempoAperturaDerechoTarea3 - tiempoCerrarDerechoTarea3 - tiempoAperturaIzquierdoTarea3 >= tiempoCerrarIzquierdoTarea3) {
      digitalWrite(frenoizquierdo, HIGH);  // Abrir cilindro derecho
      Serial.println("Cerrar cilindro izquierdo");
      finalestadoIzquierdo = true;
    }
  } else {
    tiempoInicioDerechoTarea3 = millis();
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("loop");
  tarea10();  //Activar freno derecho, leer sensor de tarro y activar sensor freno izquierdo mientras ve el tarro. En caso
              //que no vea tarro, entonces desactiva freno izquierdo.
  tarea20();  //secuencia de llenado, se activa plato tolva con delay y se para con delay cuando el sensor ya observo la leva.
  tarea30();  //secuencia de salida de tarro.
}
