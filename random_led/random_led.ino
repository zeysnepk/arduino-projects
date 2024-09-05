long analog_deger;
int rand_num;
int leds[] = {2,3,4};
int button = 7;
int i;

void setup() {
  Serial.begin(9600);
  analog_deger = analogRead(A0);
  randomSeed(analog_deger);

  for(i=0;i<3;i++){
    pinMode(leds[i], OUTPUT);
  }
  pinMode(button, INPUT);
}

void loop() {

  if (digitalRead(button) == HIGH){
    rand_num = random(0,3);
    Serial.println(rand_num);

    for(i=0;i<3;i++){
      if (i == rand_num){
         digitalWrite(leds[i], HIGH);
      }
      else{
        digitalWrite(leds[i], LOW);
      }
    }
  }
  delay(100);
}
