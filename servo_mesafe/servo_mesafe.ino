#include <Servo.h>

const byte trig_pin=6, echo_pin=7, buzzer=4;
long sure;
int mesafe;
Servo motor;

void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  motor.attach(5);
}

void loop() {
  for(int konum=15;konum<=165;konum++){
    motor.write(konum);
    delay(150);
    mesafe = mesafe_hesapla()
    ekrana_yazdir(konum, mesafe);
    if(mesafe <= 25){
      digital.Write(buzzer, HIGH);
      delay(100);
      digital.Write(buzzer, LOW);
      delay(100);
    }
  }
  for(int konum=164;konum>15;konum--){
    motor.write(konum);
    delay(150);
    mesafe = mesafe_hesapla()
    ekrana_yazdir(konum, mesafe);
    if(mesafe <= 25){
      digital.Write(buzzer, HIGH);
      delay(100);
      digital.Write(buzzer, LOW);
      delay(100);
    }
  }
}

int mesafe_hesapla(){
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_Pin, LOW);
  sure = pulseIn(echo_pin, HIGH);
  mesafe = sure/2 * 0.034;
  return mesafe;
}

void ekrana_yazdir(int konum, int mesafe){
  Serial.print("Konum(Deerece): ");
  Serial.print(konum);
  Serial.print("---------------------------"),
  Serial.print("Mesafe: ");
  Serial.println(mesafe);
}
