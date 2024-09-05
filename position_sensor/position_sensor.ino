const int irSensor = 3;  // sensörün bağlı olduğu pin
int led = 4;

int irSensorDurumu = 0;      // Butonun şu anki durumu
unsigned long t_zaman = 0;
unsigned long g_zaman = 0;

int SeritSayisi = 0;  // okunan şerit sayısı
int konum = 0; 
int mesafe = 0;

float v_anlik = 0;  // anlık ve ortalama hız
float v_ort = 0;

unsigned long lastPressTime = 0;  // Bir önceki HIGH sinyali zamanı

void setup() 
{
    Serial.begin(9600);
    pinMode(irSensor, INPUT);
    pinMode(led, OUTPUT);
}

void loop() 
{
    // Zamanı güncelle
    unsigned long currentTime = millis();
    t_zaman = currentTime;  // Toplam geçen süre

    irSensorDurumu = digitalRead(irSensor);

    // Sensörün durumu HIGH olduğunda
    if (irSensorDurumu == LOW) 
    {
        g_zaman = currentTime - lastPressTime;  // İki HIGH arası geçen süre
        lastPressTime = currentTime;

        SeritSayisi++;

        if (SeritSayisi <= 9) 
        {
            konum += 12;
            mesafe = 12;
        }
        else if (SeritSayisi <= 15) 
        {
            konum += 6;
            mesafe = 6;
        }

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

        digitalWrite(led, HIGH);
        delay(1000);
        digitalWrite(led, LOW);
    }
}