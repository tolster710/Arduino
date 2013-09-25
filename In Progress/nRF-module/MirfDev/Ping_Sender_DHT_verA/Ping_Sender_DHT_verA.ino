//Arduino standalone with SPI LCD
//DHT11 Pin 6


//12-18-12 working!!! nothing special
// adding DHT11

/**
 * A Mirf example to test the latency between two Ardunio.
 *MIRF PINS:
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 * Configurable:
 * CE -> 8
 * CSN -> 7
 *
 * DHT PINS:
 *DHT11 --> 6
 *
 * Note: To see best case latency comment out all Serial.println
 * statements not displaying the result and load 
 * 'ping_server_interupt' on the server.
 */

#include <SPI.h>
#include "DHT.h"
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include "string.h"

#define DHTPIN 6 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);


void setup(){
  dht.begin();
  Serial.begin(9600);
  /*
   * Setup pins / SPI.
   */
   
  /* To change CE / CSN Pins:
   * 
   * Mirf.csnPin = 9;
   * Mirf.cePin = 7;
   */
  /*
  Mirf.cePin = 7;
  Mirf.csnPin = 8;
  */
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  /*
   * Configure reciving address.
   */
   
  Mirf.setRADDR((byte *)"disp1");
  
  /*
   * Set the payload length to sizeof(unsigned long) the
   * return type of millis().
   *
   * NB: payload on client and server must be the same.
   */
   
  Mirf.payload = 16;
  
  /*
   * Write channel and payload config then power up reciver.
   */
   
  /*
   * To change channel:
   * 
    Mirf.channel = 10;
   *
   * NB: Make sure channel is legal in your area.
   */
  // Mirf.channel = 90;
  Mirf.config();
  
  Serial.println("Beginning ... "); 
  
  
  double h = dht.readHumidity();
  double t = dht.readTemperature();
  //initialize variables
}




//LOOP
void loop(){
  unsigned long time = millis();
  double h = dht.readHumidity();
  double t = dht.readTemperature();
  
  
  
 mirfSendVar("sens1", h);
 mirfSendVar("sens1", t);
  
 
  Serial.println("Finished sending");
  delay(10);
  
  while(!Mirf.dataReady()){
    //Serial.println("Waiting");
    if ( ( millis() - time ) > 1000 ) {
      Serial.println("Timeout on response from server!");
      return;
    }
  }
  
  //Mirf.getData((byte *) &time);
  
Serial.print("Pinged!");
//  Serial.println((millis() - time));
  
  delay(5000);
} 
  
  void mirfSendVar(char *addr, byte data){
    Mirf.setTADDR((byte *)"sens1");
    Mirf.send((byte *)&data);
     while(Mirf.isSending()){
  }
  }
  
