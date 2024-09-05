/*a_anlik = anlık ivme
a_ort = ortalama ivme
v_anlik = anlık hız
v_ort = ortalama hız
konum = konum verisi
t_zaman = toplam geçen zaman
ir_PressTime = iki şerit arası geçen zaman
*/

#include <DS3231.h>
#include <Wire.h>
#include <DHT11.h>
#include <DFRobot_MLX90614.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

DFRobot_MLX90614_I2C sensor; 

DHT11 dht11(2);

float roll = 0.0, pitch = 0.0, yaw = 0.0;
unsigned long lastTime = 0;

float serit = 0.0;  // Tünelin ilk 5 metresi
int okumaSayisi = 1;
double onceki_serit = 0.0;
unsigned long onceki_zaman = 0;

const int irSensor = 3;  // sensörün bağlı olduğu pin

int irSensorDurumu = 0;      // Butonun şu anki durumu

float temperature = 0.0;
float objectTemp = 0.0;
float hiz = 0.0;
float ivme = 0.0;

void setup() 
{
  Serial.begin(9600);
  Wire.begin(8); // I2C adresini belirle
  Wire.onRequest(requestEvent);

//butonu giriş pinine ayarla   
  pinMode(irSensor, INPUT);

    // MPU6050'i başlat
  if (!mpu.begin()) {
    Serial.println("MPU6050 başlatılamadı!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Başlatıldı!");

  onceki_zaman = millis();

  while( NO_ERR != sensor.begin() ){
  Serial.println("Communication with device failed, please check connection");
  delay(3000);
  }
  Serial.println("Begin ok!");

  sensor.enterSleepMode();
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);

}

void loop() 
{
    delay(1000);

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
  
    unsigned long simdiki_zaman = millis();
    double zaman_farki = (simdiki_zaman - onceki_zaman) / 1000.0;  // saniye cinsinden fark

    // Jiroskop verilerinden açısal hızları (rad/s) alın
    float gyroX = g.gyro.x;
    float gyroY = g.gyro.y;
    float gyroZ = g.gyro.z;

    // Jiroskop verilerini dereceye çevir ve deltaTime ile çarparak açıları güncelle
    roll += gyroX * 180.0 / M_PI * zaman_farki;
    pitch += gyroY * 180.0 / M_PI * zaman_farki;
    yaw += gyroZ * 180.0 / M_PI * zaman_farki;

    irSensorDurumu = digitalRead(irSensor);

    // Butonun durumu HIGH olduğunda
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
      Serial.println("Şerit Siniri");
      // Eğer okuma sayısı sınırı aşıldıysa durdur
      while (true) {
        
        // Durdurmak için sonsuz döngü
      }
    }
  }


    temperature = dht11.readTemperature();

    // Okuma sonucunu kontrol edin.
    // Hata yoksa, sıcaklık değerini yazdırın.
    // Hata varsa, uygun hata mesajını yazdırın.
    if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
        Serial.print("Sıcaklık: ");
        Serial.print(temperature);
        Serial.println(" °C");
    }


     float ambientTemp = sensor.getAmbientTempCelsius();

  /**
   * get temperature of object 1, unit is Celsius
   * return value range： 
   * @n  -70.01 °C ~ 270 °C(MLX90614ESF-DCI)
   * @n  -70.01 °C ~ 380 °C(MLX90614ESF-DCC)
   */
  objectTemp = sensor.getObjectTempCelsius();

  // print measured data in Celsius
 
  Serial.print("motorun sıcaklıgı: ");  Serial.print(objectTemp);  Serial.println(" °C");

  // print measured data in Fahrenheit

  // Sonuçları seri monitörde yazdırma
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print(" derece, ");
  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print(" derece, ");
  Serial.print("Yaw: ");
  Serial.print(yaw);
  Serial.println(" derece");
 

  Serial.println();
  delay(1000);
}
void requestEvent() {
    Wire.write((byte*)&temperature, 4);
    Wire.write((byte*)&objectTemp, 4);
    Wire.write((byte*)&serit, 4);
    Wire.write((byte*)&hiz, 4);
    Wire.write((byte*)&ivme, 4);
    Wire.write((byte*)&roll, 4);
    Wire.write((byte*)&pitch, 4);
    Wire.write((byte*)&yaw, 4);
  }

