int analog_deger=0;
float voltaj,santigrat,fahrenhayt;

void setup() {
  Serial.begin(9600);
}

void loop() {
  analog_deger = analogRead(A0);
  voltaj = analog_deger * (5.0 / 1023.0);
  santigrat = voltaj / 0.01;
  fahrenhayt = (santigrat * 9.0/5.0)+ 32.0
;
  Serial.print("Voltaj: ");
  Serial.print(voltaj);
  Serial.println(" V");
  Serial.print("Sicaklik: ");
  Serial.print(santigrat);
  Serial.print(" \xC2\xB0");
  Serial.println("C");
  Serial.print("Sicaklik: ");
  Serial.print(fahrenhayt);
  Serial.println(" F");
  Serial.println();
  delay(1000);
}
