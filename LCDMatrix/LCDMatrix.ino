#include <LedControl.h>

//Red wire from GPS
int neutralAnalogPin = A0;
//Blue wire from GPS
int gearAnalogPin = A1;
//BW Wire goes to 5V
int gearAnalogReading, neutralAnalogReading;
char realGear;

int DIN = 12;
int CS =  11;
int CLK = 10;

byte N[8] = {0xE3,0xF3,0xF3,0xDB,0xDB,0xCF,0xCF,0xC7};
byte one[8] = {0x08,0x18,0x38,0x18,0x18,0x18,0x3C,0x3C};
byte two[8] = {0x3C,0x7E,0x66,0x06,0x0C,0x18,0x3E,0x7E};
byte three[8] = {0x3C,0x7E,0x66,0x0E,0x0C,0x66,0x7E,0x3C};
byte four[8] = {0x1C,0x3C,0x6C,0xCC,0xFF,0xFF,0x0C,0x0C};
byte five[8] = {0x7E,0x7E,0x60,0x78,0x1C,0x46,0x7E,0x3C};
byte six[8] = {0x3C,0x7E,0x60,0x7C,0x7E,0x66,0x7E,0x3C};
byte FT[8] = {0xFF,0xFF,0xC6,0xF6,0xF6,0xC6,0xC6,0xC6};
byte dash[8] = {0x00,0x00,0x00,0x3C,0x3C,0x00,0x00,0x00};


LedControl lc=LedControl(DIN,CLK,CS,0);

void setup(){
  lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0,15);      // Set the brightness to maximum value
  lc.clearDisplay(0);         // and clear the display
  Serial.begin(9600);
  pinMode(gearAnalogPin, INPUT);
  pinMode(neutralAnalogPin, INPUT);
  printByte(FT);
  delay(5000);
}

void loop(){ 
/*
    printByte(FT);
    delay(500);
    printByte(one);
    delay(500);
    printByte(two);
    delay(500);
    printByte(three);
    delay(500);
    printByte(four);
    delay(500);
    printByte(five);
    delay(500);
    printByte(six);
    delay(500);
*/
  gearAnalogReading = analogRead(gearAnalogPin);
  neutralAnalogReading = analogRead(neutralAnalogPin);
  

  //Figure out what gear it's in
  if(neutralAnalogReading >= 1000){
    realGear = 'N';
    printByte(N);
  }
  else if(gearAnalogReading > 989 && gearAnalogReading < 1020){
    realGear = '1';
    printByte(one);
  }
  else if(gearAnalogReading > 962 && gearAnalogReading < 989){
    realGear = '2';
    printByte(two);
  }
  else if(gearAnalogReading > 919 && gearAnalogReading < 962){
    realGear = '3';
    printByte(three);
  }
  else if(gearAnalogReading > 848 && gearAnalogReading < 919){
    realGear = '4';
    printByte(four);
  }
  else if(gearAnalogReading > 707 && gearAnalogReading < 848){
    realGear = '5';
    printByte(five);
  }
  else if(gearAnalogReading > 100 && gearAnalogReading < 707){
    realGear = '6';
    printByte(six);
  }
  else{
    realGear = '-';
    printByte(dash);
  }

  //Output that data
  
//  Serial.print("Gear reading = ");
//  Serial.print(gearAnalogReading);
//  Serial.print("  Neutral reading = ");
//  Serial.print(neutralAnalogReading);
//  Serial.print("  Actual Gear =  ");
//  Serial.println(realGear);
//  delay(100);

}


void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
