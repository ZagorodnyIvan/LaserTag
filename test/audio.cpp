#include <Arduino.h>

#define L0 D2
#define L1 D3
#define I0 dpins[0]

const uint8_t dpins[10]={
  5,4,0,2,14,12,13,15,3,1
};
int c[] = {
  0
};
const bool debug = true;
const int tickrate = 150;
const int bam = 1;
const int cam = 1;
bool vars[bam][2]={
  {
    false, false
  }
};
bool alive = true;
bool l = false;
bool OnPress(int b) {
    return (vars[b][0] != vars[b][1] && vars[b][0]);
}
void Vars0(){
  for (unsigned int i = 0; i < bam; i++){
    vars[i][0] = !digitalRead(dpins[i]);
  }
}
void Vars1(){
  for (unsigned int i = 0; i < bam; i++){
    vars[i][1] = vars[i][0];
  }
}
void setup() {
  pinMode(L0, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(I0, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  Vars0();
  if(OnPress(0)){
    alive = !alive;
  }
  if (alive)
  {
    
  }
  
  //Counters
  for(int i = 0; i < cam; i++){
    c[i] += 50;
  }

  Vars1();
  //delayMicroseconds(1000000 / (tickrate*1000));
}