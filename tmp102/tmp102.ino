
//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Simple code for the TMP102, simply prints temperature via serial
//////////////////////////////////////////////////////////////////

#include <Wire.h>
int tmp102Address = 0x48;
byte res;
int val;

int yellowOn = 1;
const int yellowLED = 8;
float setTemp = 0.0;
void setup(){
  
  // initialize the yellow led
  pinMode(yellowLED, OUTPUT);      

  Serial.begin(9600);
  Wire.begin();
}

void loop(){
  Wire.requestFrom(tmp102Address,2); 
    
  byte MSB = Wire.read();
  byte LSB = Wire.read();
  
  int TemperatureSum = (MSB << 4) + (LSB >> 4);
  float celcius;
  float fahrenheit;
  
  if(TemperatureSum & 0b100000000000){

    TemperatureSum -= 1;
    TemperatureSum = ~ TemperatureSum;
    TemperatureSum = TemperatureSum & 0b111111111111;
    
    celcius = TemperatureSum * -0.0625;
    fahrenheit = (TemperatureSum * -0.1125) + 32;  
    
  
  }else{
   celcius = TemperatureSum*0.0625;
   fahrenheit = (TemperatureSum*0.1125) + 32;  
  }
  
  if ( setTemp == 0.0 ) {
    setTemp = fahrenheit;
  }
  
  
   float diff = fahrenheit - setTemp; 
  
  Serial.print("Celcius: ");
  Serial.println(celcius);
  
  Serial.print("Fahrenheit: ");
  Serial.println(fahrenheit);
  
  Serial.print("Set: ");
  Serial.println(setTemp);
  
  
  Serial.print("Diff: ");
  Serial.println(diff);

  
  if ( diff <  -2.0 ) yellowOn = 0;
   if (yellowOn == 1  ) {     
    // turn LED on:
    digitalWrite(yellowLED, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(yellowLED, LOW); 
  }

  
  delay(1000);
}



