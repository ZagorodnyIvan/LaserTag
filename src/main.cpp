#include <Arduino.h>

#define L0 D2
#define L1 D3
#define I0 dpins[0]
const int tickrate = 100;

const uint8_t dpins[10]={
  5,4,0,2,14,12,13,15,3,1
};
int c[] = {
  0
};
const bool debug = true;
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
void Alive(){
  digitalWrite(L1, LOW);
  digitalWrite(L0, l);
}
void Dead(){
  digitalWrite(L0, LOW);
  digitalWrite(L1, l);
}
void loop() {
  Vars0();

  if (alive) Alive();
  else Dead();
  
  if(OnPress(0)){
    alive = !alive;
  }
  
  //Counters
  for(int i = 0; i < cam; i++){
    c[i] += 10;
  }
  
  if (c[0] >= 1000)
  {
    c[0] = 0;
    l = !l;
  }
  //Debug
  if(debug) {
    //Serial.printf("light: %d \n", alive);
    //Serial.printf("tick: %d \n", 1000000 / (tickrate*1000));
  }

  Vars1();
  delayMicroseconds(1000000 / tickrate);
}