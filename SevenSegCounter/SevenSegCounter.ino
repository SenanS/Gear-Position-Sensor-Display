//Very simple 7 segment display code, takes interrupt input from 2 buttons, debounces it and adds one to the total on the 7 seg.


#include "SevSeg.h"
SevSeg sevseg; 

#define debounceTime 3000
#define plotPin A1

void setup(){
//    byte numDigits = 1;
//    byte digitPins[] = {};
//    byte segmentPins[] = {6, 5, 11, 12, 4, 7, 8, 11};
//    bool resistorsOnSegments = true;
//
//    byte hardwareConfig = COMMON_CATHODE; 
//    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
//    sevseg.setBrightness(90);
//    attachInterrupt(digitalPinToInterrupt(3), shiftUp, RISING);
//    attachInterrupt(digitalPinToInterrupt(2), shiftDown, RISING); 
    Serial.begin(9600);
    pinMode(plotPin, INPUT);

}

int gear = 0, i = 0, debounce = 0;

void loop(){
  
//  int count = 0;
//  sevseg.setNumber(i); 
//  while(count < 32000){
//    sevseg.refreshDisplay(); 
//    count++;      
//  }
//  Serial.println(i);
//  i++;
//  if(i > 9){
//    i = 0;
//  }

//  sevseg.setNumber(gear);
//  sevseg.refreshDisplay();
//  if(debounce > 0){
//    debounce--;
//  }

  int x = analogRead(plotPin);
//  x= x*1023/5;
  Serial.println(x);

}

void shiftUp(){
  if(gear != 7 && !debounce){
    gear++;
    debounce = debounceTime;
  }
}

void shiftDown(){
  if(gear != 0 && !debounce){
    gear--;
    debounce = debounceTime;
  }
}
