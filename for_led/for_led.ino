int leds[] = {2,3,4};
int i;

void setup() {
Serial.begin(9600);
for (i=0;i<3;i++){
  pinMode(leds[i], OUTPUT);
}
}

void loop() {
for (i=0;i<3;i++){
  digitalWrite(leds[i], HIGH);
  delay(1000);
  digitalWrite(leds[i], LOW);
}
for (i=2;i>=0;i--){
  digitalWrite(leds[i], HIGH);
  delay(1000);
  digitalWrite(leds[i], LOW);
}
}
