const byte led=13;
byte led_durumu=LOW;
unsigned long onceki_zaman=0;
unsigned long simdiki_zaman=0;
const long led_suresi=100;

void setup() {
  Serial.begin(9600);
  //Serial.println(millis());
  pinMode(led, OUTPUT);
}

void loop() {
  simdiki_zaman = millis();
  if(simdiki_zaman - onceki_zaman >= led_suresi){
    if(led_durumu == LOW){
      led_durumu = HIGH;
    }
    else{
      led_durumu = LOW;
    }
    digitalWrite(led, led_durumu);
    Serial.println("Simdiki Zaman: " + String(simdiki_zaman) + " Onceki Zaman: " + String(onceki_zaman) + " Fark: " + String(simdiki_zaman - onceki_zaman));
    onceki_zaman = simdiki_zaman;
  }
}
