/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
const int plugPin = 11;
const int buttonPin = 9;
const int yellowLED = 10;
const int greenLED = 13;

// variables will change:
int motionTime = 0;        
int buttonState = 0;
int buttonToggle = 0;
int greenOn = 1;
int yellowOn = 0;

int plugOn = 0;

int offTime = 0;

int onTime = 0;


int ALWAYS_ON     = 2;
int MOTION_DETECT = 0;
int ALWAYS_OFF    = 1;
int switchState = MOTION_DETECT;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // initialize the 120v relay pin as an output:
  pinMode(yellowLED, OUTPUT);      
  // initialize the 120v relay pin as an output:
  pinMode(plugPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  
   // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // button is press on LOW
  if ( buttonState == LOW ) {
    
    if ( switchState == MOTION_DETECT ) {
       switchState = ALWAYS_ON;
       onTime = 60 * 4;
    }
    else if ( switchState == ALWAYS_OFF ) {
      switchState = MOTION_DETECT;
    }
    else if ( switchState == ALWAYS_ON ) {
      switchState = ALWAYS_OFF;
    }
  }
  
  if ( switchState == ALWAYS_OFF ) {
    yellowOn = 0;
    greenOn = 1;
    offTime = 60 * 4;
    onTime = 0;
    motionTime = 0;
    plugOn = 0;
  }
  if ( switchState == ALWAYS_ON ) {
    
    yellowOn = 1;
    greenOn = 0;
    motionTime = 0;
    offTime = 0;
    plugOn = 1;
    onTime = 0;
  }
  
  if ( switchState == MOTION_DETECT ) {
    
    greenOn = 0;
    yellowOn = 0;
    offTime = 0;
    onTime = 0;

    // read the motion input on analog pin 0:
    int sensorValue = analogRead(A0);
    if ( offTime == 0 && sensorValue > 600 ) {
      motionTime = 60 * 4;
      plugOn = 1;
    }

  
    if ( motionTime > 0 ) 
    {
       motionTime = motionTime - 1; 
       if ( motionTime == 0 ) {
          plugOn = 0;
       }
    }   
  }
  
  if ( onTime > 0 ) {
    onTime = onTime - 1;   
    if ( onTime == 0 ) {
      plugOn = 0;
    }
  }  
 
  if ( offTime > 0 ) {
   offTime = offTime - 1;
  }
  
  if (plugOn == 1  ) {     
    // turn LED on:
    digitalWrite(plugPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(plugPin, LOW); 
  }

  if (yellowOn == 1  ) {     
    // turn LED on:
    digitalWrite(yellowLED, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(yellowLED, LOW); 
  }

  if (greenOn == 1  ) {     
    // turn LED on:
    digitalWrite(greenLED, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(greenLED, LOW); 
  }
  
  Serial.print(" onTime:");
  Serial.print(onTime);
  Serial.print(" offTime:");
  Serial.print(offTime);
  Serial.print(" motionTime:");
  Serial.print(motionTime);
  Serial.println();
  Serial.print("plugOn:");
  Serial.println();
 
  delay(250);

}
