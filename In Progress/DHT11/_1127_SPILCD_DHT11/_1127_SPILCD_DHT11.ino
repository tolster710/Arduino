/*

Same code as fermentcam - only with SPI lcd insttead of all connect

No Remote

12-18-12 Not working
--Resets the board right after the serial part starts
    Suggest selective disabling, or building from working client, checking along the way.
    
    

 Demonstration sketch for Adafruit i2c/SPI LCD backpack
 using MCP23008 I2C expander
 ( http://www.ladyada.net/products/i2cspilcdbackpack/index.html )

 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * 5V to Arduino 5V pin
 * GND to Arduino GND pin
 * CLK to Analog #5
 * DAT to Analog #4
*/

// include the library code:
#include "Wire.h"
#include "LiquidCrystal.h"
#include "DHT.h"
#include "SPI.h"
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
#include "string.h"
//#include "float2string.h"
using namespace std;

#define DHTPIN 6     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);


// Connect via i2c, default address #0 (A0-A2 not jumpered)
LiquidCrystal lcd(0);

void setup() {
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
   lcd.setBacklight(LOW);
  // Print a message to the LCD.
  lcd.print("hello, worlld!");
  
  //DHT Setup
  dht.begin();
  delay(500);
  lcd.clear();
  //Values for DHT
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  //from MIRF EXAMPLE
  Serial.begin(57600);
  Serial.println("1");

  Mirf.init();
  
  // name the receiving channel - must match tranmitter setting!
  Mirf.setRADDR((byte *)"cli1");
  // just a single byte is transmitted
  Mirf.payload = 8; //changed to 
  // we use channel 90 as it is outside of WLAN bands 
  // or channels used by wireless surveillance cameras 
  Mirf.channel = 90;
  // now config the device.... 
  Mirf.config();  
  // Set 1MHz data rate - this increases the range slightly
  Mirf.configRegister(RF_SETUP,0x06);
  
  //Experimenting with pointers
  //char* preamble = "TEMP";
  
  
  
}
//end Setup

//Make the display Change colors every N seconds
  int disl_delay=0;

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis()/1000);
  


 // lcd.setBacklight(HIGH);
 // delay(500);
  lcd.setBacklight(LOW);
  //delay(500);
  rewrite();
  disl_delay++;
  byte c;
    if( Mirf.dataReady() )
  {
     // well, get it
     Mirf.getData(&c);

    // ... and write it out to the PC
     Serial.print(c);
  }
  
}


void Sendtemp( char * temp){
  // sends temp to 
    //----ADDING MIRF
    Mirf.setTADDR((byte *)"sens1");
    
    //send temp
    
   Mirf.send((byte *)&temp);
   unsigned long time = millis();
   while(Mirf.isSending()){
  }
  Serial.println("Finished sending");
  delay(10);
  
  
  while(!Mirf.dataReady()){
    //Serial.println("Waiting");
    if ( ( millis() - time ) > 1000 ) {
      Serial.println("Timeout on response from server!");
      return;
    }
  }
}
   
   void buildpacket(char * temp){
     
     char tx_packet[30];
     
     char * pre = temp; 
     
     strcpy(tx_packet, "TEMP ");
     strcat(tx_packet,pre);
     
     Sendtemp(tx_packet);
    // strcpy ((tx_packet,"TEMP"));
   // strcat(tx_packet, temp);
     
   }
     
//rewrites the lcd with new data

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
  
  char * s;
  dtostrf(t,5, 2, s);
   //floatToString(myStr, E, 3);
  buildpacket(s);
  if(disl_delay>5){
    disl_delay=0;
  /*for(int i=0; i<3; i++){
   analogWrite(disp[i], random(190,255));
  }*/
  //Code for 3-color LED change
  }
}



