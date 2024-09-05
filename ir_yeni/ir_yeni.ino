double serit = 0.0;  // Tünelin ilk 5 metresi
int okumaSayisi = 1;
double onceki_serit = 0.0;
unsigned long onceki_zaman = 0;

const int irSensor = 3;  // sensörün bağlı olduğu pin

int irSensorDurumu = 0;  // Butonun şu anki durumu


void setup() {
  Serial.begin(9600);
  pinMode(irSensor, INPUT);
  onceki_zaman = millis();
}

void loop() {
  unsigned long simdiki_zaman = millis();
  double zaman_farki = (simdiki_zaman - onceki_zaman) / 1000.0;  // saniye cinsinden fark
  double hiz = 0.0;
  double ivme = 0.0;

  irSensorDurumu = digitalRead(irSensor);

  if (irSensorDurumu == LOW) {

    if (okumaSayisi <= 71) {
      if (okumaSayisi == 1) {
        serit += 10;
      }
      if (okumaSayisi > 1 && okumaSayisi <= 20) {
        serit += 4;
      }
      if (okumaSayisi > 20 && okumaSayisi <= 40) {
        serit += 0.1;
      }
      if (okumaSayisi == 41) {
        serit += 2;
      }
      if (okumaSayisi > 41 && okumaSayisi <= 53) {
        serit += 4;
      }
      if (okumaSayisi > 53 && okumaSayisi <= 63) {
        serit += 0.1;
      }
      if (okumaSayisi == 64) {
        serit += 3;
      }
      if (okumaSayisi > 60 && okumaSayisi <= 71) {
        serit += 4;
      }

      // Hız ve ivme hesaplamaları
      hiz = (serit - onceki_serit) / zaman_farki;
      ivme = hiz / zaman_farki;

      // Her adımda mesafe, hız, ivme ve okunan sensör sayısını yazdırma
      Serial.print("\nOkunan sensor sayisi = ");
      Serial.print(okumaSayisi);
      Serial.print("\nTunel icindeki Mesafe = ");
      Serial.print(serit, 2);
      Serial.print(" m");
      Serial.print("\nHiz = ");
      Serial.print(hiz, 2);
      Serial.print(" m/s");
      Serial.print("\nIvme = ");
      Serial.print(ivme, 2);
      Serial.print(" m/s^2");
      Serial.println("\n-------------------------------------------------------------");

      // Sonraki hesaplamalar için önceki değerleri güncelle
      onceki_serit = serit;
      onceki_zaman = simdiki_zaman;

      okumaSayisi++;
      delay(1000);  // 1 saniyelik gecikme
    } else {
      // Eğer okuma sayısı sınırı aşıldıysa durdur
      while (true) {
        // Durdurmak için sonsuz döngü
      }
    }
  }
}
