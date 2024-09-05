#include <MFRC522.h>
#include <SPI.h>

const int SDA_pin = 10;
const int RST_pin = 9;

const int yesil_led = 6;
const int kirmizi_led = 7;
const int buzzer = 8;

String kartid = "";

MFRC522 mfrc(SDA_pin, RST_pin);

void setup() {
  pinMode(yesil_led, OUTPUT);
  pinMode(kirmizi_led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc.PCD_Init();
  Serial.println("Kartınızı okuyucuya yaklaştırınız.");
  Serial.println();
}

void loop() {
  digitalWrite(yesil_led, LOW);
  digitalWrite(kirmizi_led, LOW);
  digitalWrite(buzzer, LOW);
  if(!mfrc.PICC_IsNewCardPresent()){ //kart algılanmamışsa döngüye tekrar gir
    return;
  }
  if(!mfrc.PICC_ReadCardSerial()){ //kart var ancak okunamamışsa döngüye tekrar gir
    return;
  }
  Serial.print("UID Etiketii: ");
  for(byte i=0; i<mfrc.uid.size; i++){
    kartid.concat(String(mfrc.uid.uidByte[i], HEX));
  }
  kartid.toUpperCase();
  Serial.println(kartid);

  if(kartid == "64E34729" || kartid == "E0AE5856"){
    erisimOnay();
  }
  else{
    erisimRed();
  }
}

void erisimOnay(){
  Serial.println();
  Serial.println("Mesaj: Yetkili Erişim");
  digitalWrite(yesil_led, HIGH);
  for(byte i=0; i<3; i++){
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
  }
}

void erisimRed(){
  Serial.println();
  Serial.println("Mesaj: Yetkisiz Erişim");
  digitalWrite(kirmizi_led, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(1000);
}
