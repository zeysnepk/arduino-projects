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

int numI=1400;
int basamak_sayisi=6;
char karakter='_';

float numF=11.25;
int ondalik_sayisi=2; //1-5
char ondalik_ayirac='.';
int basamak_sayisi_o=7;
char basamak_tamamlayici='-';

void setup() {
  ekran.InitLCD(); //ekran başlatma
  ekran.setContrast(70); //kontrast ayarı 0-127
}

void loop() {
  ekran.setFont(SmallFont);

  //basamak_sayisi ve karakter opsiyonel
  ekran.printNumI(numI,CENTER,0,basamak_sayisi,karakter); // __1400

  ekran.setFont(BigNumbers); //, ve _ desteklenmez
  //ondalik_ayirac ve basamak_sayisi_o ve basamak_tamamlayici
  ekran.printNumF(numF,ondalik_sayisi,CENTER,8,ondalik_ayirac,basamak_sayisi_o,basamak_tamamlayici); // -11.25

  ekran.setFont(SmallFont);
  ekran.printNumF(-10.5,2,CENTER,16,',',7,'_'); //-_10,50 !basamak ayiraci negatif isaretten sonra geldiğinde negatiflerde basamak ayiraci yazilmasa daha iyi olur!
}
