byte A=2, B=3, C=4, D=5;
int list[4][4] = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
int adim=512, sayac=0;

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

}

void loop() {
  while(sayac< adim){
    for(int i=0;i<4;i++){
      digitalWrite(A, list[i][0]);
      digitalWrite(B, list[i][1]);
      digitalWrite(C, list[i][2]);
      digitalWrite(D, list[i][3]);
      delay(10);
    }
    sayac++;
  }

}
