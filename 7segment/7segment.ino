int a = 2, b = 3, c = 4, d = 5, e = 6, f = 7, g = 8;
int button_increase = 10, button_decrease = 11;
int i;
int num = 0;
byte num_table[10][7] = {
  {0,0,0,0,0,0,1}, //0
  {1,0,0,1,1,1,1}, //1
  {0,0,1,0,0,1,0}, //2
  {0,0,0,0,1,1,0}, //3
  {1,0,0,1,1,0,0}, //4
  {0,1,0,0,1,0,0}, //5
  {0,1,0,0,0,0,0}, //6
  {0,0,0,1,1,1,1}, //7
  {0,0,0,0,0,0,0}, //8
  {0,0,0,0,1,0,0}  //9
};

void setup() {
  for(i=2;i<9;i++){
    pinMode(i, OUTPUT);
  }
  pinMode(button_increase, INPUT);
  pinMode(button_decrease, INPUT);
}

void loop() {
  if(digitalRead(button_increase) == 1){
    num++;
  }
  if(digitalRead(button_decrease) == 1){
    num--;
  }
  if(num < 0){
    num = 0;
  }
  if(num > 9){
    num = 9;
  }

  for(i=0;i<7;i++){
    digitalWrite(i+2,num_table[num][i]);
  }
  delay(150);
}
