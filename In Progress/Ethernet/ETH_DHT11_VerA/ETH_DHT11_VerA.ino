/*
  SCP1000 Barometric Pressure Sensor Display
 
 Serves the output of a Barometric Pressure Sensor as a web page.
 Uses the SPI library. For details on the sensor, see:
 http://www.sparkfun.com/commerce/product_info.php?products_id=8161
 http://www.vti.fi/en/support/obsolete_products/pressure_sensors/
 
 This sketch adapted from Nathan Seidle's SCP1000 example for PIC:
 http://www.sparkfun.com/datasheets/Sensors/SCP1000-Testing.zip
 
 Circuit:
 SCP1000 sensor attached to pins 6,7, and 11 - 13:
 DRDY: pin 6
 CSB: pin 7
 MOSI: pin 11
 MISO: pin 12
 SCK: pin 13
 
 created 31 July 2010
 by Tom Igoe
 */

#include <Ethernet.h>
// the sensor communicates using SPI, so include the library:
#include <SPI.h>
#include <DHT.h>
//DHT 11 sensor library

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// assign an IP address for the controller:
IPAddress ip(192,168,2,60);
IPAddress gateway(192,168,2,1);	
IPAddress subnet(255, 255, 255, 0);


// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

//DHT setup

#define DHTPIN 7     // what pin we're connected to


#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);

int lastReadingTime=millis();
 float hum = dht.readHumidity();
  float tem = dht.readTemperature();



void setup() {
  // start the SPI library:
  Serial.begin(9600);
  Serial.println("Serial Initialized!");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("Server Initialized!");

 
  // give the sensor and Ethernet shield time to set up:
  delay(1000);

  //Initialize the DHT values
 
  
}



void loop() { 
  // check for a reading no more than once a second.
  if (millis() - lastReadingTime > 1000){
    // if there's a reading ready, read it:
      getData();
      
    
      // timestamp the last time you got a reading:
      lastReadingTime = millis();
    
  }

  // listen for incoming Ethernet connections:
  listenForEthernetClients();
}


void getData() {
  Serial.println("Getting reading");
  float hum= dht.readHumidity();
      float tem = dht.readTemperature();

 

 

  Serial.print("Temperature: ");
  Serial.print(tem);
  Serial.println(" degrees C");
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");
}

void listenForEthernetClients() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Got a client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          // print the current readings, in HTML format:
          client.print("Temperature: ");
          client.print(tem);
          client.print(" degrees C");
          client.println("<br />");
          client.print("humidity: ");
          client.print(hum);
          client.print(" %");
          client.println("<br />");  
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
} 



