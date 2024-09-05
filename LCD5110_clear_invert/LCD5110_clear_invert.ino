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

int satir=0;
int sutun_bas=50;
int sutun_bit=80;

void setup() {
  ekran.InitLCD(); //ekran başlatma
  ekran.setContrast(70); //kontrast ayarı 0-127
  ekran.print("SAYİLAR:",LEFT,0);
}

void loop() {
  for(int i=1;i<=30;i++){
    ekran.setFont(SmallFont);
    String ifade = String(i);
    ekran.print(ifade,50,0);

    delay(500);

    //clr.Scr --> tüm ekranı siler
    ekran.clrRow(satir,sutun_bas,sutun_bit);
  }

  //invert fonksiyonu pixelleri tersine değiştirir
  ekran.invert(true);
  ekran.setFont(SmallFont);
  ekran.print("Merhaba",CENTER,8);
  ekran.setFont(BigNumbers);
  ekran.print("2024",CENTER,16);
  delay(1000);
  ekran.invert(false);
  delay(1000);

  ekran.clrScr();

  ekran.setFont(SmallFont);
  ekran.invertText(1);
  ekran.print("Merhaba",CENTER,8);
  delay(1000);
  ekran.invertText(0);
  delay(1000);

  ekran.enableSleep();
  delay(3000);
  ekran.disableSleep();
  ekran.setFont(SmallFont);
  ekran.print("Uyku Modu",CENTER,0);
  delay(1000);
  ekran.clrScr();


}
