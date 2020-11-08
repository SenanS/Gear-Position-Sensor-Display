//Very simple 7 segment display code, takes interrupt input from 2 buttons, debounces it and adds one to the total on the 7 seg.


#include "SevSeg.h"
SevSeg sevseg; 

#define debounceTime 3000

//Red wire from GPS
int neutralAnalogPin = A0;
//Blue wire from GPS
int gearAnalogPin = A1;
//BW Wire goes to 5V
int gearAnalogReading, neutralAnalogReading;
char realGear;

void setup(){
   byte numDigits = 1;
   byte digitPins[] = {};
   byte segmentPins[] = {6, 5, 11, 12, 4, 7, 8, 11};
   bool resistorsOnSegments = true;

   byte hardwareConfig = COMMON_CATHODE; 
   sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
   sevseg.setBrightness(90);
//    attachInterrupt(digitalPinToInterrupt(3), shiftUp, RISING);
//    attachInterrupt(digitalPinToInterrupt(2), shiftDown, RISING); 
    Serial.begin(9600);
    pinMode(plotPin, INPUT);

}

int gear = 0, i = 0, debounce = 0;

void loop(){
  
 int count = 0;
 sevseg.setNumber(i); 
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

//   int x = analogRead(plotPin);
//  x= x*1023/5;
//   Serial.println(x);

  gearAnalogReading = analogRead(gearAnalogPin);
  neutralAnalogReading = analogRead(neutralAnalogPin);
  
  sevseg.setNumber(gear);
  sevseg.refreshDisplay();
    
  if(neutralAnalogReading >= 1000){
    realGear = 'N';
    gear = 0;
  }
  else if(gearAnalogReading > 989 && gearAnalogReading < 1020){
    realGear = '1';
    gear = 1;
  }
  else if(gearAnalogReading > 962 && gearAnalogReading < 989){
    realGear = '2';
    gear = 2;
  }
  else if(gearAnalogReading > 919 && gearAnalogReading < 962){
    realGear = '3';
    gear = 3;
  }
  else if(gearAnalogReading > 848 && gearAnalogReading < 919){
    realGear = '4';
    gear = 4;
  }
  else if(gearAnalogReading > 707 && gearAnalogReading < 848){
    realGear = '5';
    gear = 5;
  }
  else if(gearAnalogReading > 100 && gearAnalogReading < 707){
    realGear = '6';
    gear = 6;
  }
  else{
    realGear = '-';
  }
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
