//sensor tarro

//freno izquierdo
const int frenoizquierdo = 5;


//freno derecho
const int frenoderecho = 6;

//secuencia retirar tarro
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


void setup()

{
  Serial.begin(19200);
  pinMode(prueba, INPUT);
  pinMode(frenoizquierdo, OUTPUT);
  digitalWrite(frenoizquierdo, HIGH);
  pinMode(frenoderecho, OUTPUT);
  digitalWrite(frenoderecho, HIGH);
}

void tarea3() {
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
  //  tarea1(); //Activar freno derecho, leer sensor de tarro y activar sensor freno izquierdo mientras ve el tarro. En caso
  //que no vea tarro, entonces desactiva freno izquierdo.
  //tarea2();  //secuencia de llenado, se activa plato tolva con delay y se para con delay cuando el sensor ya observo la leva.
  tarea3();  //secuencia de salida de tarro.
}
