#include <Wire.h>

#define IR_SENSOR_PIN 3 // IR-08H sensörünün bağlı olduğu pin

float distance = 0.0; // Mesafeyi saklayacağımız değişken
const float increment = 20.0 * PI;
float sayi=0; // 20 cm * PI mesafe artışı

void setup() {
  Serial.begin(9600); // Seri iletişimi başlat
  pinMode(IR_SENSOR_PIN, INPUT); // Sensör pinini giriş olarak ayarla
  Wire.begin(8); // I2C adresini belirle
  Wire.onRequest(requestEvent);
}

void loop() {
  int sensorValue = digitalRead(IR_SENSOR_PIN); // Sensörün durumunu oku
  
  if (sensorValue == LOW) { // Eğer bir cisim algılanırsa
    distance += increment; // Mesafeyi arttır
    sayi=sayi+1;
    Serial.print("Mesafe: ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.print("Sayi: ");
    Serial.println(sayi);
    delay(1000); // 1 saniye bekle ki aynı cismi tekrar algılamasın
  }
}
void requestEvent() {
  // Verileri I2C üzerinden gönder
  Wire.write((byte*)&sayi, sizeof(sayi));
  Wire.write((byte*)&distance, sizeof(distance));
}