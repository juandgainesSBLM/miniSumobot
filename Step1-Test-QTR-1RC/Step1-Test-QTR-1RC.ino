
int sensor1;
int sensor2;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  sensor1 = digitalRead(2);
  sensor2 = digitalRead(3);

  Serial.print("Right QTR sensor:");
  Serial.print(sensor2);
  Serial.print("| Left QTR sensor:");
  Serial.println(sensor1);

  delay(100);

}
