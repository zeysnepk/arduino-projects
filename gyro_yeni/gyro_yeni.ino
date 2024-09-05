#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

float roll = 0.0, pitch = 0.0, yaw = 0.0;
float velocityX = 0.0, velocityY = 0.0, velocityZ = 0.0;
float positionX = 0.0, positionY = 0.0, positionZ = 0.0;
float gravityX = 0.0, gravityY = 0.0, gravityZ = 9.81;
float accelX, accelY, accelZ;
float alpha = 0.8; // Filtreleme katsayısı
unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);

  // MPU6050'i başlat
  if (!mpu.begin()) {
    Serial.println("MPU6050 başlatılamadı!");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 Başlatıldı!");

  lastTime = millis(); // İlk zaman damgasını al
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Zaman farkını hesapla
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0; // milisaniyeyi saniyeye çevir
  lastTime = currentTime;

  // Jiroskop verilerinden açısal hızları (rad/s) alın
  float gyroX = g.gyro.x;
  float gyroY = g.gyro.y;
  float gyroZ = g.gyro.z;

  // Yerçekimi bileşenlerini filtrele
  gravityX = alpha * gravityX + (1 - alpha) * a.acceleration.x;
  gravityY = alpha * gravityY + (1 - alpha) * a.acceleration.y;
  gravityZ = alpha * gravityZ + (1 - alpha) * a.acceleration.z;

  // Yerçekiminden arındırılmış ivme hesapla
  accelX = a.acceleration.x - gravityX;
  accelY = a.acceleration.y - gravityY;
  accelZ = a.acceleration.z - gravityZ;

  // İvmeden hızı hesapla (integrasyon)
  velocityX += accelX * deltaTime;
  velocityY += accelY * deltaTime;
  velocityZ += accelZ * deltaTime;


  positionX += velocityX * deltaTime;
  positionY += velocityY * deltaTime;
  positionZ += velocityZ * deltaTime;

  // Jiroskop verilerini dereceye çevir ve deltaTime ile çarparak açıları güncelle
  roll += gyroX * 180.0 / M_PI * deltaTime;
  pitch += gyroY * 180.0 / M_PI * deltaTime;
  yaw += gyroZ * 180.0 / M_PI * deltaTime;

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

  // Sonuçları yazdır
   Serial.print("İvme X: "); Serial.print(accelX); Serial.print(" m/s2, ");
  Serial.print("İvme Y: "); Serial.print(accelY); Serial.print(" m/s2, ");
  Serial.print("İvme Z: "); Serial.print(accelZ); Serial.println(" m/s2");

  Serial.print("Hız X: "); Serial.print(velocityX); Serial.print(" m/s, ");
  Serial.print("Hız Y: "); Serial.print(velocityY); Serial.print(" m/s, ");
  Serial.print("Hız Z: "); Serial.print(velocityZ); Serial.println(" m/s");

   Serial.print("Konum X: "); Serial.print(positionX); Serial.print(" m, ");
  Serial.print("Konum Y: "); Serial.print(positionY); Serial.print(" m, ");
  Serial.print("Konum Z: "); Serial.print(positionZ); Serial.println(" m");

  delay(500); // Kısa bir gecikme
}
