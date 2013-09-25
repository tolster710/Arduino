
 
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
  int disp[3] = {6,9,10};
  for(int i=0; i<3; i++){
  pinMode(disp[i],OUTPUT);}
   pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(13,HIGH);
  dht.begin();
  delay(500);
  lcd.clear();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
}

 
int out[3], randy[3], last[3] = {0};

int disp[3] = {6,9,10};
int disl_delay = 0;


void loop() {
  // change the colors
  
  rewrite();
  delay(1000);
  disl_delay++;
  
  
  
}


void rewrite() {
   float h= dht.readHumidity();
  float t = dht.readTemperature();
  
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C,  ");
  lcd.setCursor(0,1);
  lcd.print("Humid: ");
  lcd.print(h);
  lcd.print("%");
  if(disl_delay>5){
    disl_delay=0;
  for(int i=0; i<3; i++){
   analogWrite(disp[i], random(190,255));
   
  }
  }
}
