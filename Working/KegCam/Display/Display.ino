/*
  LiquidCrystal Library - display() and noDisplay()
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD and uses the 
 display() and noDisplay() functions to turn on and off
 the display.
 
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe 
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */
 
 #include "DHT.h"

#define DHTPIN 7     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);


// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
   Serial.begin(9600); 
  Serial.println("LCD Initialized!");
  int disp[3] = {,7,8};
  for(int i=0; i<3; i++){
  pinMode(disp[i],OUTPUT);}
   pinMode(6, OUT
  dht.begin();
  delay(500);
  lcd.clear();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
}
 float h = dht.readHumidity();
  float t = dht.readTemperature();
 
int out[3], randy[3], last[3] = {0};

void loop() {
  // change the colors
  
   h = dht.readHumidity();
t = dht.readTemperature();
  
   randy[0] = random();
   randy[1] = random();
   if (randy[0]>=randy[1]){
  randy[2] = random(randy[1], randy[0]);
   }
   else{
     randy[2] = random(randy[0],randy[1]);
   }
   for(int i=0; i<3; i++){
   last[i]= out[i]*randy[i];
   out[i] = last[1]%255;
   }
   rewrite();
  
  
}
void rewrite() {
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C,  ");
  lcd.setCursor(0,1);
  lcd.print("Humid: ");
  lcd.print(h);
  lcd.print("%");
  for(int i=0; i<3; i++){
   analogWrite(disp[i], out[i]);
  }
}
