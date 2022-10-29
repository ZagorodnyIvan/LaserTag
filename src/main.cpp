#include <Arduino.h>

#define L0 D2
#define L1 D3
#define I0 dpins[0]
const int tickrate = 20;

const uint8_t dpins[10]={
  5,4,0,2,14,12,13,15,3,1
};
unsigned long c[] = {
  0
};
const bool debug = true;
const int bam = 1;
const int cam = 1;
unsigned long myTime = 0;
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
void Vars(int stage){
  if (stage == 0){
    for (unsigned int i = 0; i < bam; i++){
      vars[i][0] = !digitalRead(dpins[i]);
    }
    myTime = millis();
  }
  else if (stage == 1){
    for (unsigned int i = 0; i < bam; i++){
      vars[i][1] = vars[i][0];
    }
    // unsigned long newTime = millis();
    // if (newTime - myTime > 1000/tickrate) myTime = newTime;
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
  Vars(0);

  if (alive) Alive();
  else Dead();
  
  if(OnPress(0)){
    alive = !alive;
  }
  
  //Counters

    //Serial.printf("%li\n", millis()-myTime);
  
  if (myTime >= c[0])
  {
    c[0] = myTime + 500;
    l = !l;
  }
  //Debug
  if(debug) {
    //Serial.printf("light: %d \n", alive);
    //Serial.printf("tick: %d \n", 1000000 / (tickrate*1000));
  }

  Vars(1);
  //delayMicroseconds(1000000 / tickrate);
}