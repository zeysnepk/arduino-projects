#include <IRremote.h>

#define yukari_tus 16736925 //ileri gitme
#define asagi_tus 16754775 //geri gitme
#define sag_tus 16761405 //sağa dönme
#define sol_tus 16720605 //sola dçnme
#define kare 16732845 //hız arttırma
#define yildiz 16728765 //hız azaltma
#define sifir 16730805 //durdurma

const int ir_pin=2;
const int out_1=5;
const int out_2=6;
const int out_3=7;
const int out_4=8;
const int motor_kontrol_1=9;
const int motor_kontrol_2=10;
const int echo_pin=11;
const int trig_pin=12;
int hiz=80;
long sure,mesafe;

IRrecv ir_sensor(ir_pin);
decode_results sonuc;


void setup() {
  Serial.begin(9600);
  Serial.println("IR Alıcı etkinleştiriliyor...");
  ir_sensor.enableIRIn();
  Serial.println("IR Alıcı etkinleştirildi.");

  pinMode(out_1, OUTPUT);
  pinMode(out_2, OUTPUT);
  pinMode(out_3, OUTPUT);
  pinMode(out_4, OUTPUT);
  pinMode(motor_kontrol_1, OUTPUT);
  pinMode(motor_kontrol_1, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);

  digitalWrite(motor_kontrol_1, 0);
  digitalWrite(motor_kontrol_2, 0);
  digitalWrite(out_1, 0);
  digitalWrite(out_2, 0);
  digitalWrite(out_3, 0);
  digitalWrite(out_4, 0);
}

void loop() {
  mesafe = mesafeOlcum();
  if(mesafe > 40){
    if(ir_sensor.decode(&sonuc)){
      switch(sonuc.value){
        case kare: if(hiz < 255) hiz += 5; break;
        case yildiz: if(hiz > 80) hiz -= 5; break;
        case yukari_tus: motorHareket(1, 0, 0, 1, hiz); break;
        case asagi_tus: motorHareket(0, 1, 1, 0, hiz); break;
        case sag_tus: motorHareket(0, 1, 0, 1, hiz); break;
        case sol_tus: motorHareket(1, 0, 1, 0, hiz); break;
        case sifir: motorHareket(0, 0, 0, 0, 0); break;
      }
      ir_sensor.resume();
    }
  }
  else{
    motorHareket(0, 1, 1, 0, hiz);
    delay(500);
    motorHareket(0, 0, 0, 0, 0);
  }
}

int mesafeOlcum(){
  digitalWrite(trig_pin, 0);
  delayMicroseconds(2);
  digitalWrite(trig_pin, 1);
  delayMicroseconds(10);
  digitalWrite(trig_pin, 0);

  sure = pulseIn(echo_pin, 1);
  mesafe = sure / 29.1 / 2;
  delay(50);

  return mesafe;
}

void motorHareket(int deger_1, int deger_2, int deger_3, int deger_4, int hiz){
  digitalWrite(out_1, deger_1);
  digitalWrite(out_2, deger_2);
  digitalWrite(out_3, deger_3);
  digitalWrite(out_4, deger_4);
  analogWrite(motor_kontrol_1, hiz);
  analogWrite(motor_kontrol_2, hiz);
}
