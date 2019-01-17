/*
 Codigo para un robot Minisumo con 2 sensores sharp y 2 sensores QTR  
 */
int speedSumo=200;
//Declaracion de pines para sensores
int SharpDer = A1; 
int SharpIzq = A0;
int QtrDer   = 3;
int QtrIzq   =2;



//Declaracion de variables para leer los valores de los sensores
int Sizq = 0;
int Sder = 0;

int Qder = 0;
int Qizq = 0;

//Declaracion de pines para los motores

//Left motor
int Ain1=5;
int Ain2=4;
int PwmLeft=10;

//Right Motor
int Bin1=6;
int Bin2=7;
int PwmRight=9;

int Mder1 = 4;
int Mder2 = 5;

int Mizq1 = 6;
int Mizq2 = 7;


int Led = 8;

void setup() {                
  
   pinMode(Mder1, OUTPUT);     
   pinMode(Mder2, OUTPUT); 
   pinMode(Mizq1, OUTPUT);
   pinMode(Mizq2, OUTPUT); 
   pinMode(Led, OUTPUT); 
   digitalWrite(Led, HIGH);   // set the LED on
   delay(5000);  // Tiempo de Seguriadad
}

void loop() {
  sensores();
  // Estos valores de 300 pueden cambiar dependiendo de cada sensor, cuando es menor a 300 se refiere a que no detecta nada, y mayor a 300 es que el sensor esta detectando algo
  // sin embargo eso lo debes comprobar tu mismo con tus sensores.
  if((Sizq<=300)&&(Sder<=300)){derechasuave();}   // 0 0 0 0=> elegir entre ir adelante o dar vueltas
  if((Sizq<=300)&&(Sder<=300)){derechafuerte();}  // 0 0 0 1
  if((SLadoizq<=300)&&(Sizq<=300)&&(Sder>=300)&&(SLadoder<=300)){derechasuave();}   // 0 0 1 0
  if((SLadoizq<=300)&&(Sizq>=300)&&(Sder<=300)&&(SLadoder<=300)){izquierdasuave();} // 0 1 0 0
  if((SLadoizq<=300)&&(Sizq>=300)&&(Sder>=300)&&(SLadoder<=300)){adelante();}       // 0 1 1 0
  if((SLadoizq>=300)&&(Sizq<=300)&&(Sder<=300)&&(SLadoder<=300)){izquierdafuerte();}// 1 0 0 0 
  
  //Para los sensores QTR los valores menores a 500 indican que detecto la liena blanca, por lo que si cualquiera de los 2 sensores detecta la linea blanca el robot debe regresar
  // Tu decides si quieres que solo regrese o tambien quieres que gire a la derecha o izquierda
  
  if((Qder<=500)||(Qizq<=500)){atras();delay(200);}   //el tiempo del delay depende de que tan rapido sea tu robot
  
}


// Lectura de Sensores
void sensores (){
 Sder = analogRead(SharpDer);  
 Sizq = analogRead(SharpIzq); 
 Qder = analogRead(QtrDer); 
 Qizq = analogRead(QtrIzq); 
 delay(1);   
}

void adelante(){
digitalWrite(Bin1, HIGH);
digitalWrite(Bin2,LOW);
analogWrite(PwmRight,speedSumo);
digitalWrite(Ain2, HIGH);
digitalWrite(Ain1, LOW);
analogWrite(PwmLeft,speedSumo);
}

void atras(){
digitalWrite(Bin1, LOW);
digitalWrite(Bin2,HIGH);
analogWrite(PwmRight,speedSumo);
digitalWrite(Ain2, LOW);
digitalWrite(Ain1, HIGH);
analogWrite(PwmLeft,speedSumo);
}
void parar(){
digitalWrite(Bin1, LOW);
digitalWrite(Bin2,LOW);
analogWrite(PwmRight,speedSumo);
digitalWrite(Ain2, LOW);
digitalWrite(Ain1, LOW);
analogWrite(PwmLeft,speedSumo);
}

void derecha(int secondTurn){
digitalWrite(Bin1, LOW);
digitalWrite(Bin2,HIGH);
analogWrite(PwmRight,speedSumo);
digitalWrite(Ain2, HIGH);
digitalWrite(Ain1, LOW);
analogWrite(PwmLeft,speedSumo);
delay(secondTurn*1000);
parar();
}
void izquierda(int secondTurn){
digitalWrite(Bin1, HIGH);
digitalWrite(Bin2,LOW);
analogWrite(PwmRight,speedSumo);
digitalWrite(Ain2, LOW);
digitalWrite(Ain1, HIGH);
analogWrite(PwmLeft,speedSumo);
delay(secondTurn*1000);
}
void derechaArc(){
digitalWrite(Bin1, LOW);
digitalWrite(Bin2,HIGH);
analogWrite(PwmRight,150);
digitalWrite(Ain2, HIGH);
digitalWrite(Ain1, LOW);
analogWrite(PwmLeft,200);
delay(secondTurn*1000);
parar();
}
void izquierdaArc(int secondTurn){
digitalWrite(Bin1, HIGH);
digitalWrite(Bin2,LOW);
analogWrite(PwmRight,200);
digitalWrite(Ain2, LOW);
digitalWrite(Ain1, HIGH);
analogWrite(PwmLeft,1150);
delay(secondTurn*1000);
}



