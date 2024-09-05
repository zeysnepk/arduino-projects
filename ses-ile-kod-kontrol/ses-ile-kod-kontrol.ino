const byte ses_pin = 2;
const byte yesil_led = 3;
const byte sari_led = 4;
const byte kirmizi_led = 5;

int sensor_veri = 0;
int sayac = 0;

void setup() {
  pinMode(ses_pin, INPUT);
  pinMode(yesil_led, OUTPUT);
  pinMode(sari_led, OUTPUT);
  pinMode(kirmizi_led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensor_veri = digitalRead(ses_pin);
  if(sensor_veri == LOW){
    sayac++;
    switch(sayac){
      case 1: 
        Serial.println("1.Ses algılandı!");
        digitalWrite(yesil_led, HIGH);
        delay(500);
        break;
      case 2: 
        Serial.println("2.Ses algılandı!");
        digitalWrite(sari_led, HIGH);
        delay(500);
        break;
      case 3: 
        Serial.println("3.Ses algılandı!");
        digitalWrite(kirmizi_led, HIGH);
        delay(500);
        break;
      case 4: 
        Serial.println("4.Ses algılandı!");
        digitalWrite(yesil_led, HIGH);
        digitalWrite(sari_led, HIGH);
        digitalWrite(kirmizi_led, HIGH);
        delay(500);
        sayac=0;
        break;
    }
  }
  else{
    digitalWrite(yesil_led, LOW);
    digitalWrite(sari_led, LOW);
    digitalWrite(kirmizi_led, LOW);
  }
}
