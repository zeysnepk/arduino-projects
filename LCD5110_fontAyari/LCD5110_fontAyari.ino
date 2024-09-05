#include <LCD5110_Basic.h>

int clk=8;
int Din=9;
int Dc=10;
int RST=11;
int CE=12;

LCD5110 ekran(8,9,10,11,12); //nesne importlama

extern uint8_t SmallFont[]; //fontları ekleme
extern uint8_t MediumFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

void setup() {
  ekran.InitLCD(); //ekran başlatma
  ekran.setContrast(70); //kontrast ayarı 0-127
}

void loop() {
  ekran.setFont(SmallFont);
  ekran.print("Cumhuriyet'in",CENTER,8); //x  -->ekseni merkezde, y --> 2.satır

  ekran.setFont(MediumNumbers);
  ekran.print("96.",0,16); // y --> 3.satır

  ekran.setFont(SmallFont);
  ekran.print("YILI",33,24); // y --> 4.satır
}
