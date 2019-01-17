#include <HCSR04.h>

#define SURVIVE 0
#define HUNT 1
#define TARGET 2
#define ATTACK 3

#define SHARP_THRESHOLD 300


UltraSonicDistanceSensor distanceSensor(12, 11);
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
int distance=0;

//Declaracion de pines para los motores

//Left motor
int Ain1=5;
int Ain2=4;
int PwmLeft=10;

//Right Motor
int Bin1=6;
int Bin2=7;
int PwmRight=9;

int Led = 13;
int StateVariable=TARGET;

char rotation='n';

void setup() {                
  
   pinMode(Ain1, OUTPUT);     
   pinMode(Ain2, OUTPUT); 
   pinMode(Bin1, OUTPUT);
   pinMode(Bin2, OUTPUT);
   pinMode(PwmLeft, OUTPUT);
   pinMode(PwmRight, OUTPUT);
    
   pinMode(Led, OUTPUT); 
   digitalWrite(Led, HIGH);   // set the LED on
   delay(5000);  // Tiempo de Seguriadad
}

void loop() {
  sensores();
    switch(StateVariable){
      
      case SURVIVE:

          
          if(Qder == 1 && Qizq==1){
            //Add the actions
            
            }
          else if (Qder == 1 && Qizq==0){
            //Add the actions
            
           }

          else if (Qder == 0 && Qizq==1){
            //Add the actions
            
          }
          else if (Qder == 0 && Qizq==0){
            //Add the actions

            
          }
          
          StateVariable=HUNT;
          break;
          
      case HUNT:
          // When edge detected change of state
          if(Qder == 0 || Qizq==0){

            // Add transition to SURVIVE state
            break;
          }
          //When opponent detected to left
          else if(Sizq<SHARP_THRESHOLD){
            // Add actions
            //Set the direction of roration trhough the direction variable  roration='l' or roration='r'
            //Change state to hunt
            
            }
         
          //When opponent detected to right
          else if(Sder<SHARP_THRESHOLD){
            
            // Add actions
            //Set the direction of roration trhough the direction variable  roration='l' or roration='r'
            //Change state to hunt
            
            }

          else{
            // Add actions
            // Arcing movement to the right or left
          }

          
          break;
      case TARGET:

          // When edge detected change of state
          if(Qder == 0 || Qizq==0){

            // Add transition to SURVIVE state
            break;
          }

          if (rotation== 'l'){
              izquierda(1);
             if(distance!=0 ){
              
              //go to attack state
              rotation='n';
              }
             
            }
          else if(rotation=='r'){
            derecha(1);
             if(distance!=0 ){
              
              //go to attack state
              rotation='n';
              }
            }

           
          
          
          break;
      case ATTACK:
            // adjust speedSumo to 255speed
            //Go forward
            
            if(Qder == 0 || Qizq==0){

            // Add transition to SURVIVE state

            speedSumo=200;
            
            }
      
          break;
      }
  
}


// Lectura de Sensores
void sensores (){
 Sder = analogRead(SharpDer);  
 Sizq = analogRead(SharpIzq); 
 Qder = analogRead(QtrDer); 
 Qizq = analogRead(QtrIzq);
 distance=distanceSensor.measureDistanceCm();
  
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
delay(secondTurn);
parar();
}
void izquierda(int secondTurn){
digitalWrite(Bin1, HIGH);
digitalWrite(Bin2,LOW);
analogWrite(PwmRight,speedSumo);
digitalWrite(Ain2, LOW);
digitalWrite(Ain1, HIGH);
analogWrite(PwmLeft,speedSumo);
delay(secondTurn);
parar();
}
void derechaArc(){
digitalWrite(Bin1, LOW);
digitalWrite(Bin2,HIGH);
analogWrite(PwmRight,150);
digitalWrite(Ain2, HIGH);
digitalWrite(Ain1, LOW);
analogWrite(PwmLeft,200);
}
void izquierdaArc(){
digitalWrite(Bin1, HIGH);
digitalWrite(Bin2,LOW);
analogWrite(PwmRight,200);
digitalWrite(Ain2, LOW);
digitalWrite(Ain1, HIGH);
analogWrite(PwmLeft,150);
}
