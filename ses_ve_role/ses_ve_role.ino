
const byte ses_pin=2;
const byte role=3;
byte durum=0;
byte sensor_veri=0;

void setup() {
  pinMode(ses_pin, INPUT);
  pinMode(role, INPUT);
}

void loop() {
  sensor_veri=digitalRead(ses_pin);
  if(sensor_veri == LOW){
    durum++;
    if(durum == 1){
      digitalWrite(role, HIGH);
    }
    else if(durum == 2){
      digitalWrite(role, LOW);
      durum=0;
    }
    delay(500);
  }
}
