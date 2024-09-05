#include <Wire.h>

const int irSensor = 3;  // Pin where the IR sensor is connected
int irSensorStat = 0;  // Current status of the IR sensor
unsigned long total_time = 0; // Total elapsed time
unsigned long elapsed_time = 0; // Time between two HIGH signals
int lanes = 0;  // Number of lanes detected
float position = 0; // Position in the track
int beforeIrStat = 0;
float speed = 0;  //Average speed
unsigned long lastPressTime = 0;  // Time of the last HIGH signal
float distance = 0;

void setup() {
  Serial.begin(9600);
  pinMode(irSensor, INPUT);
  Wire.begin(8);// Initialize I2C with address 8
  Wire.onRequest(requestEvent); // Set up I2C request event
}

void loop() {
   // Update the current time
  unsigned long currentTime = millis();
  total_time = currentTime;  // Update total elapsed time

  // Read the current status of the IR sensor
  irSensorStat = digitalRead(irSensor);

  // If the sensor status changes from LOW to HIGH
  if (beforeIrStat == LOW && irSensorStat == HIGH) {
    elapsed_time = currentTime - lastPressTime;  // Calculate the time between two HIGH signals
    lastPressTime = currentTime; // Update the last detection time

    lanes++; // Increment the lane count

    // Update position based on lane count
    if (lanes <= 75) {
      if (lanes == 1) {
        position += 6;
        distance = 6;
      }
      else if (lanes <= 21) {
        position += 4;
        distance = 4;
      }
      else if (lanes <= 41) {
        position += 0.1;
        distance = 0.1;
      }
      else if (lanes == 42) {
        position += 2;
        distance = 2;
      }
      else if (lanes <= 54) {
        position += 4;
        distance = 4;
      }
      else if (lanes <= 64) {
        position += 0.1;
        distance = 0.1;
      }
      else if (lanes == 65) {
        position += 3;
        distance = 3;
      }
      else if (lanes > 64 && lanes <= 75) {
        position += 4;
        distance = 4;
      }

      beforeIrStat = irSensorStat;

      // Update speed
      speed = (distance * 1000.0) / elapsed_time;  // Convert elapsed time from ms to seconds

      Serial.print("Lane Count = ");
      Serial.println(lanes);
      Serial.print("Position = ");
      Serial.println(position);
      Serial.print("Total Time = ");
      Serial.println(total_time / 1000.0);  // Convert ms to seconds
      Serial.print("Average Speed = ");
      Serial.println(speed);
      Serial.print("Elapsed Time = ");
      Serial.println(elapsed_time / 1000.0);  // Convert ms to seconds
      Serial.println("--------------------------------------");
    }
  }
}
void requestEvent() {
  // Send data over I2C
  Wire.write((byte*)&lanes, sizeof(lanes));
  Wire.write((byte*)&position, sizeof(position));
  Wire.write((byte*)&speed, sizeof(speed));
}