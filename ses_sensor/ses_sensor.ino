const byte ses_pin = 2;
const byte yesil_led = 3;
const byte sari_led = 4;
const byte kirmizi_led = 5;

int sensor_veri = 0;

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
    Serial.println("Ses algılandı");
    digitalWrite(yesil_led, HIGH);
    digitalWrite(sari_led, HIGH);
    digitalWrite(kirmizi_led, HIGH);
    delay(1000);
  }
  else{
    digitalWrite(yesil_led, LOW);
    digitalWrite(sari_led, LOW);
    digitalWrite(kirmizi_led, LOW);
  }
}
