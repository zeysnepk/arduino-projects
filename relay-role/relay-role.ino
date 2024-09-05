const int role = 2;

void setup() {
  pinMode(role, OUTPUT);
}

void loop() {
  digitalWrite(role, HIGH);
  delay(2000);
  digitalWrite(role, LOW);
  delay(2000);
}
