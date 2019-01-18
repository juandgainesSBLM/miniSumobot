int triggerPin = 12;
int echoPin = 11;

#define SURVIVE 0
#define HUNT 1
#define TARGET 2
#define ATTACK 3

#define SHARP_THRESHOLD 300

#define WHITE 0
#define BLACK 1

#define NO_OBJECT -1

/*
  Codigo para un robot Minisumo con 2 sensores sharp y 2 sensores QTR
*/
int speedSumo = 200;
//Declaracion de pines para sensores
int SharpDer = A1;
int SharpIzq = A0;
int QtrDer   = 3;
int QtrIzq   = 2;



//Sensor Variables to save the data 
int Sizq = 0; // Detect oponent left side.
int Sder = 0; // Detect oponent right side.

int Qder = 0;// Detect the edge from right side
int Qizq = 0;// Detect the edge from left side
int distance = 0;// Distance between opponent 

//Arduino pins

int Ain1 = 5;//Left motor Input 1
int Ain2 = 4;//Left motor Input 2
int PwmLeft = 10;//Left motor speed
int Bin1 = 6; //Right motor Input 1
int Bin2 = 7; //Right motor Input 2
int PwmRight = 9;//Right motor speed

int Led = 13;

// Auxiliary variables
int stateVariable = HUNT;// State machine current state
char rotation = 'n';// Rotation direction when changing state from HUNT to TARGET

void setup() {
  Serial.begin(9600);
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(PwmLeft, OUTPUT);
  pinMode(PwmRight, OUTPUT);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, HIGH);   // set the LED on
  delay(5000);  // Tiempo de Seguriadad
  
}

void loop() {
   sensores();
  
  switch (stateVariable) {

    case SURVIVE:

      Serial.println("S:SURVIVE");
      if (Qder == BLACK && Qizq == BLACK) {
        
        //TODO:After the Serial.println, add the corresponding actions
        Serial.println("CS: SURVIVE->HUNT");
        stateVariable = HUNT;

      }
      else if (Qder == BLACK && Qizq == WHITE) {
        //TODO:After the Serial.println, add the corresponding actions
        Serial.println("ACTION: Giro derecha...");

      }

      else if (Qder == WHITE && Qizq == BLACK) {
        //TODO:After the Serial.println, add the corresponding actions
        Serial.println("ACTION: Giro izquierda...");

      }
      else if (Qder == WHITE && Qizq == WHITE) {
        //TODO:After the Serial.println, add the corresponding actions
        Serial.print("ACTION: Atras y...");
        Serial.println("ACTION: Giro derecha...");
      }

      break;

    case HUNT:
      Serial.println("S:HUNT");
      // When edge detected change of state
      if (Qder == WHITE || Qizq == WHITE) {

        // Add transition to SURVIVE state
        Serial.println("CS: HUNT->SURVIVE");
        stateVariable = SURVIVE;
        break;

      }
      //When opponent detected to left
      else if (Sizq < SHARP_THRESHOLD) {
        //Set the direction of roration trhough the direction variable  roration='l' or roration='r'
        //Change state to target
        rotation = 'l';
        Serial.println("DETECTION: ENEMY LEFT");
        stateVariable = TARGET;
        Serial.println("CS: HUNT->TARGET");
      }

      //When opponent detected to right
      else if (Sder < SHARP_THRESHOLD) {

        //Set the direction of roration trhough the direction variable  roration='l' or roration='r'
        //Change state to target
        rotation = 'r';
        Serial.println("DETECTION: ENEMY RIGHT");
        stateVariable = TARGET;
        Serial.println("CS: HUNT->TARGET");

      }

      else {
        //TODO:After the Serial.println, add the corresponding actions
        Serial.println("ACTION: ARCING MOVEMENT");
      }
      break;
      
    case TARGET:
      Serial.println("S:TARGET");
      // When edge detected change of state
      if (Qder == WHITE || Qizq == WHITE) {

        // Add transition to SURVIVE state
        Serial.println("CS: TARGET->SURVIVE");
        stateVariable = SURVIVE;

        break;
      }

      if (rotation == 'l') {
        //TODO:After the Serial.println, add the corresponding actions
        Serial.println("ACTION: Giro izquierda...");
        if (distance != NO_OBJECT ) {

          //go to attack state
          stateVariable = ATTACK;
          rotation = 'n';
        }

      }
      else if (rotation == 'r') {
        Serial.println("ACTION: Giro derecha...");
        if (distance != NO_OBJECT ) {
          stateVariable = ATTACK;
          //go to attack state
          rotation = 'n';
        }
      }




      break;
    case ATTACK:
      Serial.println("S:ATTACK");

      if (Qder == WHITE || Qizq == WHITE) {
        //Move to SURVIVE state
        stateVariable = SURVIVE;
        speedSumo = 200;

      }

      break;
  }
}

// Lectura de Sensores
void sensores () {
  Sder = analogRead(SharpDer);
  Sizq = analogRead(SharpIzq);
  Qder = digitalRead(QtrDer);
  Qizq = digitalRead(QtrIzq);
  distance = measureDistanceCm();
  delay(1);
}

void adelante() {
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(PwmRight, speedSumo);
  digitalWrite(Ain2, HIGH);
  digitalWrite(Ain1, LOW);
  analogWrite(PwmLeft, speedSumo);
}

void atras() {
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, HIGH);
  analogWrite(PwmRight, speedSumo);
  digitalWrite(Ain2, LOW);
  digitalWrite(Ain1, HIGH);
  analogWrite(PwmLeft, speedSumo);
}
void parar() {
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);
  analogWrite(PwmRight, speedSumo);
  digitalWrite(Ain2, LOW);
  digitalWrite(Ain1, LOW);
  analogWrite(PwmLeft, speedSumo);
}

void derecha(int secondTurn) {
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, HIGH);
  analogWrite(PwmRight, speedSumo);
  digitalWrite(Ain2, HIGH);
  digitalWrite(Ain1, LOW);
  analogWrite(PwmLeft, speedSumo);
  delay(secondTurn);
  parar();
}
void izquierda(int secondTurn) {
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(PwmRight, speedSumo);
  digitalWrite(Ain2, LOW);
  digitalWrite(Ain1, HIGH);
  analogWrite(PwmLeft, speedSumo);
  delay(secondTurn);
  parar();
}
void derechaArc() {
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, HIGH);
  analogWrite(PwmRight, 150);
  digitalWrite(Ain2, HIGH);
  digitalWrite(Ain1, LOW);
  analogWrite(PwmLeft, 200);
}
void izquierdaArc() {
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(PwmRight, 200);
  digitalWrite(Ain2, LOW);
  digitalWrite(Ain1, HIGH);
  analogWrite(PwmLeft, 150);
}

double measureDistanceCm() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  unsigned long durationMicroSec = pulseIn(echoPin, HIGH);
  double distanceCm = durationMicroSec / 2.0 * 0.0343;
  if (distanceCm == 0 || distanceCm > 328) {
    return -1.0 ;
  } else {
    return distanceCm;
  }
}
