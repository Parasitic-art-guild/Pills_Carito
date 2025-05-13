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


void setup()

{
  Serial.begin(19200);
  pinMode(4, OUTPUT); //confirmación de lectura no intermitente 
  pinMode(sensortarro, INPUT);
  pinMode(frenoizquierdo, OUTPUT); //relacionado con cilindro izquierdo  
  digitalWrite(frenoizquierdo, LOW); //estado inicial cilindro izquierdo
  pinMode(frenoderecho, OUTPUT);
  digitalWrite(frenoderecho, HIGH);

  tiempoInicioTarea11 = millis();
}





void loop() {
  tarea2();  //Activar freno derecho, leer sensor de tarro y activar sensor freno izquierdo mientras ve el tarro. En caso
  //que no vea tarro, entonces desactiva freno izquierdo.
}
void tarea2() {
  if (digitalRead(sensortarro) && !bitSiSensorTarroTarea11 && millis() - tiempoInicioTarea11 >= tiempoSiSensorTarroTarea1) {
    //Se cumple si sensor ve tarro por tiempoSi y si bitSiSensor es false
    Serial.println("Presencia de tarro 11");
    digitalWrite(4, HIGH);           // si sensor ve por tiempoSi entonces activa LED,
                                     // este codigo es representación visual de lectura
    bitSiSensorTarroTarea11 = true;  // es verdadera para que condicional no se repita y se active el condicional que
                                     // ve si el tarro una vez esta en posición se mueve por un tiempo tiempoNoSensor
    digitalWrite(frenoizquierdo, HIGH);
    bitSiSensorTarroTarea12 = false;  //codigo necesario para activar tarea 2
  } else {
     if (!digitalRead(sensortarro)) {
      tiempoInicioTarea11 = millis();  //si sensor no ve nada, el tiempo incial es igual a millis
    }
  }
  if (bitSiSensorTarroTarea11 && !bitSiSensorTarroTarea12 && !digitalRead(sensortarro) && millis() - tiempoInicioTarea12 >= tiempoNoSensorTarroTarea1) {
    Serial.println("Se perdio tarro");
    digitalWrite(4, LOW);             // si sensor NO ve por tiempoNO entonces desactiva LED,
    bitSiSensorTarroTarea12 = true;   //para inhabilitar esta condicional o tarea.
    digitalWrite(frenoizquierdo, LOW);             // este codigo puede abrir el cilindro para que entre otro tarro}
                                      // tambien puede ser usado para detener el proceso de llenado, por ejemplo detener la tolva y el motor.
    bitSiSensorTarroTarea11 = false;  //codigo necesario para habilitar tarea 1
  } else {
    if (digitalRead(sensortarro)) {
      tiempoInicioTarea12 = millis();
    }
  }
}