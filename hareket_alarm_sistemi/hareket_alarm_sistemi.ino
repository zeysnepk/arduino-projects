const int red=4, green=3, buzzer=10, open_button=11, close_button=12, pir=2;
bool alarm=false;

void setup() {
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(open_button,INPUT);
  pinMode(close_button,INPUT);
  pinMode(pir,INPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(open_button) == 1){
    alarm=true;
    delay(5000);
  }
  if(digitalRead(close_button) == 1){
    alarm=false;
  }
  Serial.println("ALarm: ");
  Serial.println(alarm);

  if(alarm == true){
    digitalWrite(green,HIGH);
    digitalWrite(red,LOW);
    if(digitalRead(pir) == 1){
      while(digitalRead(close_button) == 0){
        digitalWrite(buzzer,HIGH);
        delay(250);
        digitalWrite(buzzer,LOW);
        delay(250);
      }
    }
  }
  else{
    digitalWrite(green,LOW);
    digitalWrite(red,HIGH);
  }

}
