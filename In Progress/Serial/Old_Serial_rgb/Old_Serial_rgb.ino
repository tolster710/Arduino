

//int leds[3] = {9,10,11};





/*
RGB color gamut (mouse control)

 The circuit:
 Sparkfun Three LED breakout board KIT-10111
 * RED on Arduino pin 9
 * GRN on Arduino pin 10
 * BLU on Arduino pin 11
 
 AMC Dawes (dawes@pacificu.edu)
 dawes.wordpress.com
 Created 4 Jan 2011
 Based on sample code "Fading" By David A. Mellis
 
 */


int redPin = 9;
int grnPin = 10;
int bluPin = 11;
int ledbargPin = 3;
int ledbarrPin = 2;

int startbyte;
int userInput[5];
int i;
int red = 0;
int green = 0;
int blue = 0;
int ledbarred = 0;
int ledbargreen = 0;

void setup()  { 
  Serial.begin(57600); // initialize serial connection 
  //pinMode(ledbargPin, OUTPUT);
  pinMode(ledbarrPin, OUTPUT);
}

void loop()  { 
  if (Serial.available() > 3) {
    // Read the first byte
    startbyte = Serial.read();
    // If it's really the startbyte (0x73 or ASCII "s") ...
    if (startbyte == 0x73) {
      // ... then get the next three bytes
      for (i=0;i<5;i++) {
        userInput[i] = Serial.read();
        //if (userInput[i] == ) {break;} // just in case
      }
      // First byte = red
      red = userInput[0];
      // Second byte = green
      green = userInput[1];
      // Third byte = blue
      blue = userInput[2];
      ledbarred = userInput[3];
      ledbargreen = userInput[4];
    }
    analogWrite(redPin, red % 255); // mod 255 just in case
    analogWrite(grnPin, green % 255); 
    analogWrite(bluPin, blue % 255);
    analogWrite(ledbargPin, ledbargreen % 255);
    if ( ledbarred >= 128){
        digitalWrite(ledbarrPin, 1);}
     else{ digitalWrite(ledbarrPin, 0);}
    // some serial output for debugging:
    
    Serial.print("red: ");
    Serial.println(red);
    Serial.print("green: ");
    Serial.println(green);
    Serial.print("blue: ");
    Serial.println(blue);
    Serial.println("------------");
  }   
}
