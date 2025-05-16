//sensor tarro
const int sensortarro = 12;
bool bitSiSensorTarroTarea11 = false;
bool bitSiSensorTarroTarea12 = false;
unsigned long tiempoSiSensorTarroTarea1 = 10000;
unsigned long tiempoNoSensorTarroTarea1 = 5000;
unsigned long tiempoInicioTarea11 = millis();
unsigned long tiempoInicioTarea12 = millis();

//freno izquierdo
const int frenoizquierdo = 5;

//freno derecho
const int frenoderecho = 6;

//secuencia de llenado
const int motorPin = 4;
/* naranja con tarea sensado tarro
pinMode(4, OUTPUT); //confirmación de lectura no intermitente
*/
const int iniciosecuenciallenado = 10;
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
const unsigned long tiempoAperturaDerechoTarea3 = 5000; // Retardo para abrir el cilindro derecho (en milisegundos)
const unsigned long tiempoCerrarDerechoTarea3 = 5000; // Tiempo de apertura del cilindro derecho (en milisegundos)
const unsigned long tiempoAperturaIzquierdoTarea3 = 5000; // Tiempo de apertura del cilindro izquierdo (en milisegundos)
const unsigned long tiempoCerrarIzquierdoTarea3 = 5000;
bool estadoDerecho = false;
bool estadoIzquierdo = false;
bool finalestadoDerecho = false;
bool finalestadoIzquierdo = false;
const int prueba = 3;

void setup() {
  // put your setup code here, to run once:
pinMode (sensortarro, INPUT);
pinMode (sensortarro, INPUT);
pinMode(frenoizquierdo, OUTPUT); //relacionado con cilindro izquierdo
pinMode(frenoderecho, OUTPUT);
pinMode(4, OUTPUT); //confirmación de lectura no intermitente
pinMode(iniciosecuenciallenado, INPUT);
digitalRead(iniciosecuenciallenado);
pinMode(motorPin, OUTPUT); // Configurar el pin del motor como salida
pinMode(sensorPin, INPUT); // Configurar el pin del sensor como entrada
tiempoInicio = millis(); // Registrar el tiempo inicial


}

void loop() {
  // put your main code here, to run repeatedly:

}
