// AC712 Sensörü için Pin Tanımı
const int sensorPin = A0;  // AC712'nin bağlı olduğu analog pin

// Kalibrasyon için kullanacağınız besleme voltajı (Arduino'yu 5V veya 3.3V ile besliyorsanız, ona göre ayarlayın)
const float Vcc = 5.0;  // 5V besleme için
//const float Vcc = 3.3;  // 3.3V besleme için

// AC712 modeline göre hassasiyet değerini ayarlayın
const float sensitivity = 0.033;  // AC712 modeli için (30 mV/A)

const float zeroCurrentVoltage = Vcc / 2;  

void setup() {
  // Seri haberleşmeyi başlat
  Serial.begin(9600);
}

void loop() {
  // Sensörden gelen analog değeri oku
  int sensorValue = analogRead(sensorPin);

  // Analog değeri voltaja çevir
  float voltage = sensorValue * (Vcc / 1023.0);

  // Akımı hesapla
  float current = (voltage - zeroCurrentVoltage) / sensitivity;

  float power = current * voltage;

  // Seri monitörde görüntüle
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.print(" V | Current: ");
  Serial.print(current);
  Serial.println(" A");
  Serial.print(power);
  Serial.println(" W");

  // 1 saniye bekle
  delay(1000);
}