// This sketch will send out a Nikon D50 trigger signal (probably works with most Nikons)
// See the full tutorial at http://www.ladyada.net/learn/sensors/ir.html
// this code is public domain, please enjoy!
 
int IRledPin = 3;  // LED connected to digital pin 13
 
// The setup() method runs once, when the sketch starts



int LED_Power_ON[] = {

// ON, OFF (in 10's of microseconds)

	880, 440,

	60, 50,

	60, 50,

	60, 50,

	60, 50,

	60, 50,

	60, 50,

	60, 50,

	60, 50,

	60, 160,

	60, 160,

	60, 160,

	60, 160,

	60, 160,

	60, 160,

	60, 160,

	60, 160,

	60, 160,

	60, 160,

	60, 160,

	60, 50,

	60, 50,

	60, 50,

	60, 50,

	60, 50,

	60, 50,

	60, 50,

	60, 50,

	60, 160,

	60, 160,

	60, 160,

	60, 160,

	60, 160,

	60, 3900,

	888, 214,

    60, 2860,

	888, 214,

	60, 0};

int LED_Power_ON_size = sizeof(LED_Power_ON) / sizeof(LED_Power_ON[0]);


int LED_Power_Off[] = {

// ON, OFF (in 10's of microseconds)

	884, 440,

	54, 54,

	56, 52,

	56, 56,

	54, 54,

	58, 52,

	58, 52,

	56, 52,

	58, 52,

	56, 164,

	56, 164,

	56, 162,

	58, 164,

	56, 162,

	56, 164,

	54, 164,

	60, 162,

	54, 54,

	56, 164,

	56, 164,

	56, 54,

	54, 54,

	58, 52,

	58, 52,

	56, 52,

	58, 164,

	54, 52,

	58, 54,

	56, 162,

	58, 164,

	54, 164,

	58, 160,

	60, 162,

	58, 0};
int LED_Power_Off_size = sizeof(LED_Power_Off) / sizeof(LED_Power_Off[0]);

 
void setup()  {        
 // initialize the IR digital pin as an output:
 pinMode(IRledPin, OUTPUT);   
 
 Serial.begin(9600);
}
 
void loop()           
{
 Serial.println("Sending IR signal");
 
 SendPowerOn();
 
 delay(6*1000); // wait one minute (60 seconds * 1000 milliseconds)
 
 SendPowerOff();
  delay(6*1000); // wait one minute (60 seconds * 1000 milliseconds)
 //pulseIR(450); //60ms
 //delayMicroseconds(580); //50
 //pulseIR(700);
 //delayMicroseconds(1700); // 160
 //pulseIR(1350); // 160 long
 //delayMicroseconds(3000);
}
 
// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
 // we'll count down from the number of microseconds we are told to wait
 
 cli(); // this turns off any background interrupts
 
 while (microsecs > 0) {
  // 38 kHz is about 13 microseconds high and 13 microseconds low
  digitalWrite(IRledPin, HIGH); // this takes about 3 microseconds to happen
  delayMicroseconds(10);     // hang out for 10 microseconds, you can also change this to 9 if its not working
  digitalWrite(IRledPin, LOW);  // this also takes about 3 microseconds
  delayMicroseconds(10);     // hang out for 10 microseconds, you can also change this to 9 if its not working
 
  // so 26 microseconds altogether
  microsecs -= 26;
 }
 
 sei(); // this turns them back on
}
 
 
 void SendPowerOn(){
  for (int i=0; i<LED_Power_ON_size; i++){
   if (i%2==0){
    pulseIR(LED_Power_ON[i]*10);
   }
   else{
    delayMicroseconds(LED_Power_ON[i]*10);
   }
  }
 }
  
  void SendPowerOff(){
  for (int i=0 ;i<LED_Power_Off_size; i++){
   if (i%2==0){
    pulseIR(LED_Power_Off[i]*10);
   }
   else{
    delayMicroseconds(LED_Power_Off[i]*10);
   }
  }
 }

