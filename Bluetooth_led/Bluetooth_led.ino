#include <SoftwareSerial.h>

softwareSerial port1(10,11);

char message;
const int green=2, yellow=3, white=4, red=5;

void setup() {
  pinMode(green,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(white,OUTPUT);
  pinMode(red,OUTPUT);
  Serial.begin(9600);
  port1.begin(9600);
}

void loop() {
  while(port1.available() > 0){
    message = port1.read();
    if(message == '0'){
      digitalWrite(red, HIGH);
    }
    else if(message == '1'){
      digitalWrite(red, LOW);
    }
    else if(message == '2'){
      digitalWrite(white, HIGH);
    }
    else if(message == '3'){
      digitalWrite(white, LOW);
    }
    else if(message == '4'){
      digitalWrite(yellow, HIGH);
    }
    else if(message == '5'){
      digitalWrite(yellow, LOW);
    }
    else if(message == '6'){
      digitalWrite(green, HIGH);
    }
    else if(message == '7'){
      digitalWrite(green, LOW);
    }
  }

}
