
#include <LiquidCrystal.h>
int led=8, buzzer=9, echo=6, trig=7;
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);
long time, distance;
int division;
void setup()
{
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
  lcd_1.begin(16, 2); 
  lcd_1.setCursor(0,0);
  lcd_1.print("Distance:");
}

void loop()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  time = pulseIn(echo, HIGH);
  distance = (time/2)/29.154;
  lcd_1.setCursor(9, 0);
  lcd_1.print(distance);
  division=distance/10;
  lcd_1.setCursor(11+division,0);
  lcd_1.print("cm");
  division=distance/5;
  digitalWrite(buzzer, HIGH);
  digitalWrite(led, HIGH);
  delay(division*20);
  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);
  delay(division*20);
  
  delay(10);
}