// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
DateTime lastPicture;
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int shutter = 7;  // canon shutter pin 7

void setup () {
  Serial.begin(57600);
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();
  
    // initialize the shutter pin as an output.
  pinMode(shutter, OUTPUT);  
   
}


void loop () {
    DateTime now = rtc.now();
        
    uint32_t diff = now.unixtime() - lastPicture.unixtime();
   if ( diff > 120 
        && ( now.hour() > 5 && now.hour() < 20 ) 
        && ( now.minute() == 0 || now.minute() == 15 || now.minute() == 30 || now.minute() == 45 ) )
    {
           digitalWrite(shutter, HIGH);   // turn the LED on (HIGH is the voltage level)
           delay(1000);               // wait for a second
           digitalWrite(shutter, LOW);    // turn the LED off by making the voltage LOW
           lastPicture = now;
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  }
    
    delay(1000);
}
