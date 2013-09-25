/**
 * A Mirf example to test the latency between two Ardunio.
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
 * Note: To see best case latency comment out all Serial.println
 * statements not displaying the result and load 
 * 'ping_server_interupt' on the server.
 
 
 JT - 6May13 - Need to figure out how to cast and construct 
 */

#include <SPI.h>
#include <DHT.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <string.h>


  union radpack
{
  byte package[32];
  int myints[16];
  float myfloats[8];
};
radpack radio_in;
radpack radio_out;

#define DHTPIN 6     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);


void setup(){
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
   
  Mirf.setRADDR((byte *)"clie1");
  
  /*
   * Set the payload length to sizeof(unsigned long) the
   * return type of millis().
   *
   * NB: payload on client and server must be the same.
   */
   
  Mirf.payload = sizeof(radio_out);
  
  /*
   * Write channel and payload config then power up reciver.
   */
   
  /*
   * To change channel:
   * 
   * Mirf.channel = 10;
   *
   * NB: Make sure channel is legal in your area.
   */
   
  Mirf.config();
  
  Serial.println("Beginning ... "); 
}

void loop(){
  char *time ;
  double t = dht.readTemperature();
  Mirf.setTADDR((byte *)"serv1");
  String stringone = "Tolly calling breadboard..";
  String stringtwo = doubleToString(t,0);
  String string3 = stringone + stringtwo;
  char charBuf[36] = "";
  string3.toCharArray(charBuf,36);
  
  strcpy((char *)radio_out.package,charBuf);
  
  Mirf.send((byte *)&radio_out);
  
  while(Mirf.isSending()){
  }
  Serial.println("Finished sending");
  delay(10);
  while(!Mirf.dataReady()){
    //Serial.println("Waiting");
    
  }
  
  Mirf.getData((byte *) &time);
  //strcpy((char *)radio_in.package,&time);
  
  Serial.print("Ping: ");
  Serial.print((char *)&time);
  Serial.println();
  
  
  delay(1000);
} 
  
  
//Rounds down (via intermediary integer conversion truncation)
String doubleToString(double input,int decimalPlaces){
if(decimalPlaces!=0){
String string = String((int)(input*pow(10,decimalPlaces)));
if(abs(input)<1){
if(input>0)
string = "0"+string;
else if(input<0)
string = string.substring(0,1)+"0"+string.substring(1);
}
return string.substring(0,string.length()-decimalPlaces)+"."+string.substring(string.length()-decimalPlaces);
}
else {
return String((int)input);
}
}
  
