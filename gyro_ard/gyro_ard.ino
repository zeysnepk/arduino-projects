#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// MPU6050 sensör nesnesini oluştur
Adafruit_MPU6050 mpu;

float acc_x = 0.0;
float acc_y = 0.0;
float acc_z = 0.0;

float gyro_x = 0.0;
float gyro_y = 0.0;
float gyro_z = 0.0;

void setup() {
  Serial.begin(9600);
  Wire.begin(8); // I2C adresini belirle
  Wire.onRequest(requestEvent);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("MPU6050 test!");

  // MPU6050 sensörünü başlat
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Sensörü ayarla
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);  // İvmeölçerin aralığı ±2g
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);       // Jiroskopun aralığı ±250°/s
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);    // Düşük geçiş filtresi 21 Hz

  delay(1000);  // Sensörün başlatılması için kısa bir bekleme
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // İvme verilerini yazdır
  Serial.print("AccelX: ");
  Serial.print(a.acceleration.x);
  Serial.print(" m/s^2, ");
  Serial.print("AccelY: ");
  Serial.print(a.acceleration.y);
  Serial.print(" m/s^2, ");
  Serial.print("AccelZ: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  // Jiroskop verilerini yazdır
  Serial.print("GyroX: ");
  Serial.print(g.gyro.x);
  Serial.print(" rad/s, ");
  Serial.print("GyroY: ");
  Serial.print(g.gyro.y);
  Serial.print(" rad/s, ");
  Serial.print("GyroZ: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  acc_x = a.acceleration.x;
  acc_y = a.acceleration.y;
  acc_z = a.acceleration.z;

  gyro_x = g.gyro.x;
  gyro_y = g.gyro.y;
  gyro_z = g.gyro.z;

  delay(500);  // Verileri 500 ms aralıklarla güncelle
}
void requestEvent() {
  Wire.write((byte*)&acc_x, 4);
  Wire.write((byte*)&acc_y, 4);
  Wire.write((byte*)&acc_z, 4);
  Wire.write((byte*)&gyro_x, 4);
  Wire.write((byte*)&gyro_y, 4);
  Wire.write((byte*)&gyro_z, 4);
}