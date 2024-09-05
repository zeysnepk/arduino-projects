const int motor_1=2, motor_2=3;

void setup() {
  pinMode(motor_1, OUTPUT);
  pinMode(motor_2, OUTPUT);
}

void loop() {
  while(analogRead(A0) <= 500){
    digitalWrite(motor_1,HIGH);
    digitalWrite(motor_2,LOW);
  }

  while(analogRead(A0) > 500){
    digitalWrite(motor_2,HIGH);
    digitalWrite(motor_1,LOW);
  }
}
