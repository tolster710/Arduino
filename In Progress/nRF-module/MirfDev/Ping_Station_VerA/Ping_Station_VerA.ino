//Server - Arduino Uno on Breadboard
//DHT11 pin 6
/**
 * An Mirf example which copies back the data it recives.
 *
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 *
 */

#include <SPI.h>
#include "DHT.h"
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include "string.h"

void setup(){
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  /*
   * Set the SPI Driver.
   */

  Mirf.spi = &MirfHardwareSpi;
  
  /*
   * Setup pins / SPI.
   */
   
  Mirf.init();
  
  /*
   * Configure reciving address.
   */
   
  Mirf.setRADDR((byte *)"sens1");
  
  /*
   * Set the payload length to sizeof(unsigned long) the
   * return type of millis().
   *
   * NB: payload on client and server must be the same.
   */
   
  Mirf.payload = 16; //SET TO 16
  
  /*
   * Write channel and payload config then power up reciver.
   */
   Mirf.channel = 90;
  Mirf.config();
  
  Serial.println("Listening..."); 
}



//LOOP______________________________________

void loop(){
  /*
   * A buffer to store the data.
   */
   digitalWrite(4, LOW);
  byte data[Mirf.payload];
  
  /*
   * If a packet has been recived.
   *
   * isSending also restores listening mode when it 
   * transitions from true to false.
   */
   
  if(!Mirf.isSending() && Mirf.dataReady()){
    Serial.println("Got packet");
    digitalWrite(4, HIGH);
    
    /*
     * Get load the packet into the buffer.
     */
     
    Mirf.getData(data);
    Serial.println(*data);
    
    /*
     * Set the send address.
     */
     
     
    Mirf.setTADDR((byte *)"clie1");
    
    /*
     * Send the data back to the client.
     */
     
    Mirf.send(data);
    
    
    /*
     * Wait untill sending has finished
     *
     * NB: isSending returns the chip to receving after returning true.
     */
      
   //Serial.println("Reply sent.");
  }
}
