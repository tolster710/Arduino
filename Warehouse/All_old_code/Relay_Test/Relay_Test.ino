#include <SPI.h>
#include "DHT.h"
#include "string.h"

#define DHTPIN 6 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);


void setup(){
  dht.begin();
  Serial.begin(9600);
  
    Serial.println("Beginning ... "); 
  
  digitalWrite(5, HIGH);
  pinMode(5,OUTPUT);

  
  
}

void loop(){
 delay(1000);
 digitalWrite(5, LOW);
 delay(1000);
 digitalWrite(5,HIGH);
}

 
 
