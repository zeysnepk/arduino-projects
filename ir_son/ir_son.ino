#include <Wire.h>

const int irSensor = A0;  // sensörün bağlı olduğu pin
const int threshold = 512;  // Eşik değeri (0-1023 arası)

int irSensorDurumu = 0;      // Sensörün şu anki durumu
unsigned long t_zaman = 0;
unsigned long g_zaman = 0;

float SeritSayisi = 0;  // okunan şerit sayısı
float konum = 0; 
int mesafe = 0;
int oncekiDurum = 0;

float v_anlik = 0;  // anlık ve ortalama hız
float v_ort = 0;

unsigned long lastPressTime = 0;  // Bir önceki HIGH sinyali zamanı

void setup() 
{
    Serial.begin(9600);
    pinMode(irSensor, INPUT);
    Wire.begin(0x08);  // I2C adresini belirle
    Wire.onRequest(requestEvent);
}

void loop() 
{
    // Zamanı güncelle
    unsigned long currentTime = millis();
    t_zaman = currentTime;  // Toplam geçen süre

    // Analog okuma yap ve dijital duruma dönüştür
    int analogValue = analogRead(irSensor);
    irSensorDurumu = (analogValue > threshold) ? HIGH : LOW;
    oncekiDurum = (analogValue > threshold) ? HIGH : LOW;

    // Sensörün durumu HIGH olduğunda
    if (oncekiDurum == LOW && irSensorDurumu == HIGH) 
    {
        g_zaman = currentTime - lastPressTime;  // İki HIGH arası geçen süre
        lastPressTime = currentTime;

        SeritSayisi++;
        if (SeritSayisi <= 75) {
            if (SeritSayisi == 1)
            {
                konum += 6;
            }
            if (SeritSayisi > 1 && SeritSayisi <= 21)
            {
                konum += 4;
            }
            if (SeritSayisi > 21 && SeritSayisi <= 41)
            {
                konum += 0.1;
            }
            if (SeritSayisi == 42)
            {
                konum += 2;
            }
            if (SeritSayisi > 42 && SeritSayisi  <= 54)
            {
                konum += 4;
            }
            if (SeritSayisi > 54 && SeritSayisi <= 64)
            {
                konum += 0.1;
            }
            if (SeritSayisi == 64)
            {
                konum += 3;
            }
            if (SeritSayisi > 64 && SeritSayisi <= 75)
            {
                konum += 4;
            }

            oncekiDurum = irSensorDurumu;

            v_anlik = (float)mesafe / (g_zaman / 1000.0);  // milisaniye cinsinden zamanı saniyeye çevir
            v_ort = (float)konum / (t_zaman / 1000.0);

            Serial.print("Okunan şerit sayısı = ");
            Serial.println(SeritSayisi);
            Serial.print("Konum = ");
            Serial.println(konum);
            Serial.print("Toplam zaman = ");
            Serial.println(t_zaman / 1000.0);  // milisaniyeyi saniyeye çevir
            Serial.print("Ortalama hız = ");
            Serial.println(v_ort);
            Serial.print("Anlık hız = ");
            Serial.println(v_anlik);
            Serial.print("Geçen zaman = ");
            Serial.println(g_zaman / 1000.0);  // milisaniyeyi saniyeye çevir
            Serial.println("--------------------------------------");
        }
    }
}

void requestEvent() {
    Wire.write((byte*)&SeritSayisi, 4);
    Wire.write((byte*)&konum, 4);
    Wire.write((byte*)&v_ort, 4);
}
