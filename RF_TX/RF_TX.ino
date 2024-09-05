#include <VirtualWire.h>

char *message;
int button=3;
int button_stat=0;

void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT);

  vw_set_ptt_inverted(true);
  vw_set_tx_pin(2);
  vw_setup(4000);
}

void loop() {
  button_stat = digitalRead(button);

  if(button_stat){
    message = "1";
  }
  else{
    message = "0";
  }
  Serial.println(message);

  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
  delay(100);

}
