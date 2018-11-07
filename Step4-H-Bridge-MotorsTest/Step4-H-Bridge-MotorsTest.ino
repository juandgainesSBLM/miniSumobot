const int PWMB=9;
const int PWMA=10;
const int AIN1=5;
const int AIN2=4;
const int BIN1=6;
const int BIN2=7;

unsigned char speed_motors=255;

void setup() {
  // put your setup code here, to run once:

  pinMode(PWMB,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  forward();
  Serial.println("Forward");
  delay(5000);

  turn_left();
  Serial.println("Left");
  delay(5000);

  turn_right();
  Serial.println("Right");
  delay(5000);
  
  backward();
  Serial.println("Backward");
  delay(5000);
  

}


void forward(){
  //right Motor 
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN1,HIGH);
  //left motor
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  
  delay(1);
  //set pwms
  analogWrite(PWMB,speed_motors);
  analogWrite(PWMA,speed_motors);
  
  }

void backward(){
  //right Motor 
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN1,LOW);
  //left motor
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  
  delay(1);
  //set pwms
  analogWrite(PWMB,speed_motors);
  analogWrite(PWMA,speed_motors);
  
  }


void turn_left(){
  //right motor
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN1,HIGH);
  //left motor
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  
  delay(1);
  //set pwms
  analogWrite(PWMB,speed_motors);
  analogWrite(PWMA,speed_motors);
  
  }

void turn_right(){
  //right motor
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN1,LOW);
  //left motor
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  
  delay(1);
  //set pwms
  analogWrite(PWMB,speed_motors);
  analogWrite(PWMA,speed_motors);
  
  }


