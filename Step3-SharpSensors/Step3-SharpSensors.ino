
int sensor1Sharp;
int sensor2Sharp;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  sensor1Sharp = analogRead(A0);
  sensor2Sharp = digitalRead(A1);

  Serial.print("Right QTR sensor:");
  Serial.print(sensor2Sharp);
  Serial.print("| Left QTR sensor:");
  Serial.print(sensor1Sharp);

  delay(100);

}
