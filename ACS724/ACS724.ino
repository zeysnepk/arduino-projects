#include <Wire.h>

const int sensorPin = A0; // Pin connected to the ACS724 sensor
const float sensitivity = 0.02; // Sensitivity for ACS724-50A (V/A)
const float Vref = 2.5; // Reference voltage for ACS724 (typically 2.5V)
const float supplyVoltage = 5.0; // Supply voltage (5V)
float power = 0;

void setup() {
  Serial.begin(9600); // Start serial communication
  analogReference(DEFAULT); // Use default analog reference (5V)
  Wire.begin(9); // Initialize I2C with address 8
  Wire.onRequest(requestEvent); // Set up I2C request event
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Read the sensor value
  float voltage = (sensorValue / 1023.0) * supplyVoltage; // Convert ADC value to voltage
  float current = (voltage - Vref) / sensitivity; // Calculate current (difference from Vref / sensitivity)
  power = voltage * current; // Calculate power (P = V * I)

  Serial.print("Voltage: ");
  Serial.print(voltage, 2); // Print voltage with 2 decimal places
  Serial.print(" V, ");

  Serial.print("Current: ");
  Serial.print(current, 2); 
  Serial.print(" A, ");

  Serial.print("Power: ");
  Serial.print(power, 2); 
  Serial.println(" W");

  delay(1000);
}
void requestEvent() {
  // Send data over I2C
  Wire.write((byte*)&power, sizeof(power));
}
