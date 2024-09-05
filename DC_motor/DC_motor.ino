const int sol_dugme=2, sag_dugme=3, yesil_led=4, mavi_led=5, motor_kontrol_pin=6;
int ayar=0;

void setup() {
  pinMode(sol_dugmei INPUT);
  pinMode(sag_dugme, INPUT);
  pinMode(yesil_led, OUTPUT);
  pinMode(mavi_led, OUTPUT);
  pinMode(motor_kontrol_pin, OUTPUT);
}

void loop() {
  ayar=map(analogRead(A0),0,1023,0,255);
  if(digitalRead(sol_dugme) == false && digitalRead(sag_sugme) == false){
    analogWrite(motor_kontrol_pin, ayar);
    digitalWrite(yesil_led, LOW);
    digitalWrite(mavi_led, LOW);
    analogWrite(mavi_led, ayar);
  }
  else{
    while(digitalRead(sol_dugme) == true && digitalRead(sag_sugme) == false){
      analogWrite(motor_kontrol_pin, 127);
      digitalWrite(yesil_led, HIGH);
      digitalWrite(mavi_led, LOW);
    }
    while(digitalRead(sol_dugme) == false && digitalRead(sag_sugme) == true){
      analogWrite(motor_kontrol_pin, 255);
      digitalWrite(yesil_led, LOW);
      digitalWrite(mavi_led, HIGH);
    }
  }
}
