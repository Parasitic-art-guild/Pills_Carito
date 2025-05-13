//sensor tarro
const int sensortarro = 9;
unsigned long tiempoInicioTarea1 = 0;
const unsigned int tiemposensortarrot1 = 5000;
bool inputActivesensortarro = false;

//freno izquierdo
const int frenoizquierdo = 5;
const int iniciosecuenciallenado = 10;


//freno derecho
const int frenoderecho = 6;
bool bitfrenoderecho = false;


//Secuencia llenado
const int motorPin = 4;                              // Pin al que está conectado el motor
const int sensorPin = 8;                             // Pin del sensor que detecta la leva
const unsigned long tiempoInicioTarea2Motor = 5000;  // Tiempo de espera para activar el motor (en milisegundos)
const unsigned long tiempoParadaMotor = 5000;        // Tiempo que el motor se mantiene encendido tras detectar la leva



//unsigned long tiempoActual = 0;
unsigned long tiempoInicioTarea2 = 0;
unsigned long tiempoDeteccionLeva = 0;
bool motorActivo = false;
bool esperandoParo = false;
bool finsecuenciallenado = false;


//secuencia retirar tarro


unsigned long tiempoInicioDerechoTarea3;
unsigned long tiempoInicioIzquierdoTarea3;

const unsigned long tiempoAperturaDerechoTarea3 = 5000;    // Retardo para abrir el cilindro derecho (en milisegundos)
const unsigned long tiempoCerrarDerechoTarea3 = 5000;      // Tiempo de apertura del cilindro derecho (en milisegundos)
const unsigned long tiempoAperturaIzquierdoTarea3 = 5000;  // Tiempo de apertura del cilindro izquierdo (en milisegundos)
const unsigned long tiempoCerrarIzquierdoTarea3 = 5000;

bool estadoDerecho = false;
bool estadoIzquierdo = false;
bool finalestadoDerecho = false;
bool finalestadoIzquierdo = false;


bool secuenciaretirartarro = false;
bool secuenciaretirartarroderecho = false;
bool secuenciaretirartarroizquierdo = false;

const int ledprueba = 3;



void setup()

{
  Serial.begin(19200);
  pinMode(sensortarro, INPUT);
  pinMode(ledprueba, INPUT);
  //digitalWrite(ledprueba, LOW);
  pinMode(iniciosecuenciallenado, INPUT);
  digitalRead(iniciosecuenciallenado);
  pinMode(frenoizquierdo, OUTPUT);
  digitalWrite(frenoizquierdo, HIGH);
  pinMode(frenoderecho, OUTPUT);
  digitalWrite(frenoderecho, HIGH);

  pinMode(motorPin, OUTPUT);      // Configurar el pin del motor como salida
  pinMode(sensorPin, INPUT);      // Configurar el pin del sensor como entrada
  tiempoInicioTarea2 = millis();  // Registrar el tiempo inicial
}

void tarea3() {
  if (digitalRead(ledprueba)) {
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
    if (!finalestadoIzquierdo && finalestadoDerecho && !estadoIzquierdo && millis() - tiempoInicioDerechoTarea3 - tiempoAperturaDerechoTarea3 - tiempoCerrarDerechoTarea3>= tiempoAperturaIzquierdoTarea3) {
      digitalWrite(frenoizquierdo, LOW);  // Abrir cilindro derecho
      Serial.println("Abrir cilindro izquierdo");
     estadoIzquierdo = true;
    } 
if ( !finalestadoIzquierdo && finalestadoDerecho && estadoIzquierdo && millis() - tiempoInicioDerechoTarea3 - tiempoAperturaDerechoTarea3 - tiempoCerrarDerechoTarea3 - tiempoAperturaIzquierdoTarea3 >= tiempoCerrarIzquierdoTarea3) {
      digitalWrite(frenoizquierdo, HIGH);  // Abrir cilindro derecho
      Serial.println("Cerrar cilindro izquierdo");
     finalestadoIzquierdo = true;
  }}
  else {
      tiempoInicioDerechoTarea3 = millis();
    }
}



  void loop() {
    //  tarea1(); //Activar freno derecho, leer sensor de tarro y activar sensor freno izquierdo mientras ve el tarro. En caso
    //que no vea tarro, entonces desactiva freno izquierdo.
    //tarea2();  //secuencia de llenado, se activa plato tolva con delay y se para con delay cuando el sensor ya observo la leva.
    tarea3();  //secuencia de salida de tarro.
  }
