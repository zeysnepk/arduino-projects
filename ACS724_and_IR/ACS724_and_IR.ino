#include <Wire.h>

const int irSensor = 3;  // Pin where the IR sensor is connected
const int powerSensor = A0; // Pin connected to the ACS724 sensor
const float sensitivity = 0.02; // Sensitivity for ACS724-50A (V/A)
const float Vref = 2.5; // Reference voltage for ACS724 (typically 2.5V)
const float supplyVoltage = 5.0; // Supply voltage (5V)

int irSensorStat = 0;  // Current status of the IR sensor
unsigned long lastDetectionTime = 0; // Time of the last detection
int lanes = 0;  // Number of lanes detected
float position = 0; // Position in the track
int beforeIrStat = 0;
float instantaneousSpeed = 0;  // Instantaneous speed
float distance = 0;
float power = 0;

unsigned long lastPowerReadTime = 0;
const unsigned long powerReadInterval = 1000; // Read power every 1 second

void setup() {
  Serial.begin(9600);
  pinMode(irSensor, INPUT);
  analogReference(DEFAULT); // Use default analog reference (5V)
  Wire.begin(8);  // Initialize I2C with address 8
  Wire.onRequest(requestEvent); // Set up I2C request event
}

void loop() {
  unsigned long currentTime = millis();
  
  // IR Sensor logic
  irSensorStat = digitalRead(irSensor);
  if (beforeIrStat == LOW && irSensorStat == HIGH) {
    if (lastDetectionTime != 0) {
      unsigned long timeDiff = currentTime - lastDetectionTime;
      
      if (lanes <= 75) {
        if (lanes == 1) distance = 6;
        else if (lanes <= 21) distance = 4;
        else if (lanes <= 41) distance = 0.1;
        else if (lanes == 42) distance = 2;
        else if (lanes <= 54) distance = 4;
        else if (lanes <= 64) distance = 0.1;
        else if (lanes == 65) distance = 3;
        else distance = 4;
        
        position += distance;
        
        // Calculate instantaneous speed in units per second
        instantaneousSpeed = (distance * 1000.0) / timeDiff;
      }
    }
    
    lanes++;
    lastDetectionTime = currentTime;
    
    printLaneData(currentTime);
  }
  beforeIrStat = irSensorStat;
  
  // Power Sensor logic - read every powerReadInterval
  if (currentTime - lastPowerReadTime >= powerReadInterval) {
    int sensorValue = analogRead(powerSensor);
    float voltage = (sensorValue / 1023.0) * supplyVoltage;
    float current = (voltage - Vref) / sensitivity;
    power = voltage * current;
    
    printPowerData(voltage, current, power);
    
    lastPowerReadTime = currentTime;
  }
}

void printLaneData(unsigned long currentTime) {
  Serial.print("Lane Count = ");
  Serial.println(lanes);
  Serial.print("Position = ");
  Serial.println(position);
  Serial.print("Total Time (s) = ");
  Serial.println(currentTime / 1000.0);
  Serial.print("Instantaneous Speed (units/s) = ");
  Serial.println(instantaneousSpeed);
  Serial.println("--------------------------------------");
}

void printPowerData(float voltage, float current, float power) {
  Serial.print("Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V, Current: ");
  Serial.print(current, 2);
  Serial.print(" A, Power: ");
  Serial.print(power, 2);
  Serial.println(" W");
}

void requestEvent() {
  Wire.write((byte*)&lanes, sizeof(lanes));
  Wire.write((byte*)&position, sizeof(position));
  Wire.write((byte*)&instantaneousSpeed, sizeof(instantaneousSpeed));
  Wire.write((byte*)&power, sizeof(power));
}