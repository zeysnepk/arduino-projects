#include <VirtualWire.h>

char *message;
int ledPin = 3;

void setup() {
  pinMode(ledPin,OUTPUT);

  Serial.begin(9600);

  vw_set_ptt_inverted(true);
  vw_set_rx_pin(2);
  vw_setup(4000);
  vw_rx_start();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if(vw_get_message(buf, &buflen)){
    if(buf[0] == '0'){
      Serial.println(buf[0]);
      digitalWrite(ledPin, LOW);
    }
    if(buf[0] == '1'){
      Serial.println(buf[0]);
      digitalWrite(ledPin, HIGH);
    }
  }
}
