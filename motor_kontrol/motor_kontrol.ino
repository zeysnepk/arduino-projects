#include <AFMotor.h>
#include <Servo.h>



// step motor isimli step motor nesnemizi oluşturuyoruz
//nema 17 step motor kullandığım için devir adım sayısını 200 yapıyorum
//2 yazaarak step motoru M3 | M4 klemenslerine bağlayacağımı söylüyorum
AF_Stepper step_motor(200, 2);


// dc motor için motor isimli nesne oluşturuyoruz
// dc motoru shield üzerindeki M1 klemenslerine bağlıyoruz
AF_DCMotor motor(1);

// myservo1 isimli servo nesnemizi oluşturuyoruz
Servo myservo1;

unsigned long simdiki_zaman = 0;
unsigned long gecmis_zaman1 = 0;
unsigned long gecmis_zaman2 = 0;

bool value1 = false, value2 = false;




void setup() {
  Serial.begin(9600);
  Serial.println("motor shield test!");

  // step motorun hızını belirliyoruz
  step_motor.setSpeed(150);
  // dc motorun hızını belirliyoruz
  motor.setSpeed(150);
  // ilk açılışda dc motorumuzu durduruyoruz
  motor.run(RELEASE);

  // 9 pine bağlı servomuzu başlatıyoruz
  myservo1.attach(9);
}

void loop() {

  simdiki_zaman = millis();

// her 3 saniyede bir value2 nin değerini değiştiriyoruz
  if(simdiki_zaman-gecmis_zaman2 >3000){
    value2 = !value2;
  }

  // value2 nin değeri her değişmesinde aşşağıdaki if blokların bir tanesine girip çıkıyoruz
  if(value2 == true){
    motor.run(FORWARD);
  }
  if(value2 == false){
    motor.run(BACKWARD);
  }



  // her 3 saniyede bir value1 nin değerini değiştiriyoruz
  if (simdiki_zaman - gecmis_zaman1 > 1000) {
    value1 = !value1;
    gecmis_zaman1 = simdiki_zaman;
  }

  // value1 in değerine göre if bloklarına girerek servonun açısını değiştirıyoruz
  if (value1 == false) {
    
    myservo1.write(170);
  }
  if (value1 == true) {
    
    myservo1.write(1);
  }


}