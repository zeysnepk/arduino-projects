#include <Wire.h>
#include <DHT.h>

#define DHTPIN 2     
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

const int I2C_SLAVE_ADDRESS = 0x08; 

void setup() {
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  delay(100); 
  requestEvent();
}

void requestEvent() {
  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println("DHT sensöründen okuma başarısız!");
    return;
  }
  else{
    Serial.println(t);

    byte data[4];
    memcpy(data, &t, 4);
    Wire.write(data, 4); 
  }
}

