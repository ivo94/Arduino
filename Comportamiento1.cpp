
/* Constantes que no cambian y son usadas para setear el numero de los pines */
#define motorIzqPinA  10  // el numero del pin de uno de los cables de motor
#define motorIzqPinB  9   // el numero del pin del otro cable del motor
#define motorDerPinA  5   // el numero del pin de uno de los cables de motor
#define motorDerPinB  6   // el numero del pin del otro cable del motor
#define sensorIzq  3      // el numero del pin del sensor izquierdo, en el enunciado esta al reves que en el circuito (2)
#define sensorDer  2      // el numero del pin del sensor derecho, segun el enunciado (3)
#define pulsador   12     // el numero del pin del pulsador

/*variables que cambian su valor*/

bool detenido = false;
bool girarDer = true;
bool girarIzq = false;

/* setup inicial*/
void setup() {
  pinMode(motorIzqPinA,OUTPUT);
  pinMode(motorIzqPinB,OUTPUT); //masa motor izquierdo
  analogWrite(motorIzqPinB, 0); //seteo a 0 pin masa motor izquierdo
  pinMode(motorDerPinA,OUTPUT);
  pinMode(motorDerPinB,OUTPUT); //masa motor derecho
  analogWrite(motorDerPinB, 0); //seteo a 0 pin masa motor derecho
  pinMode(sensorIzq, INPUT_PULLUP);
  pinMode(sensorDer, INPUT_PULLUP);
  pinMode(pulsador, INPUT_PULLUP); 
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensorIzq), RutinaDeInterrupcion, CHANGE);
 
														 
}

/* loop del programa */
void loop(){
	if (digitalRead(pulsador)){
		detenido = false;
	}
	else { 
		detenido = true;
	}
actualizarEstado();
}



void actualizarEstado(){

	if (detenido){
		analogWrite(motorIzqPinA, 0);
		analogWrite(motorDerPinA, 0);
		Serial.println("detenido");
	}
	else {
		if (girarDer){
		analogWrite(motorIzqPinA, 130);
		analogWrite(motorDerPinA, 75);
		Serial.println("girando a la derecha");
		}
		if (girarIzq){ 
		analogWrite(motorIzqPinA, 75);
		analogWrite(motorDerPinA, 130);
		Serial.println("girando a la izquierda");
		}
	}
}


void RutinaDeInterrupcion(){
	if (girarIzq){
	girarDer = true;
	girarIzq = false;
	}
	else {
		if (girarDer){
		girarIzq = true;
		girarDer = false;
		}
	}
}


