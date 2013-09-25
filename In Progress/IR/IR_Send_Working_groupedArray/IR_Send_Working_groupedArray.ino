// This sketch will send out a Nikon D50 trigger signal (probably works with most Nikons)
// See the full tutorial at http://www.ladyada.net/learn/sensors/ir.html
// this code is public domain, please enjoy!
 
int IRledPin = 3;  // LED connected to digital pin 13
 
// The setup() method runs once, when the sketch starts



int IRLED[][150]=

{{
// ON, OFF (in 10's of microseconds)
//LED ON
	886, 436,
	58, 50,
	60, 50,
	60, 50,
	58, 50,
	60, 50,
	60, 50,
	58, 50,
	62, 48,
	62, 158,
	60, 160,
	58, 160,
	62, 158,
	60, 160,
	60, 160,
	60, 158,
	62, 160,
	58, 160,
	62, 156,
	62, 160,
	60, 48,
	62, 48,
	60, 50,
	60, 48,
	62, 48,
	62, 50,
	58, 50,
	60, 50,
	60, 158,
	62, 158,
	60, 160,
	60, 158,
	62, 160,
	58, 3916,
	886, 214,
	60, 0},
 {

// ON, OFF (in 10's of microseconds)
//LED OFF

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

	58, 0},

{

// ON, OFF (in 10's of microseconds)
//int LED_BrightDown[] = 

	884, 438,

	58, 50,

	62, 48,

	58, 52,

	60, 48,

	62, 48,

	60, 50,

	58, 50,

	64, 46,

	60, 160,

	62, 158,

	60, 160,

	60, 158,

	62, 158,

	62, 158,

	60, 158,

	64, 158,

	60, 48,

	62, 48,

	60, 158,

	62, 48,

	60, 52,

	60, 48,

	62, 46,

	58, 54,

	58, 160,

	60, 158,

	64, 48,

	60, 158,

	62, 160,

	60, 158,

	60, 158,

	64, 158,

	60, 0},

 {

// ON, OFF (in 10's of microseconds)
//int LED_BrightUp[] =

	886, 436,

	60, 50,

	58, 52,

	58, 50,

	58, 56,

	54, 52,

	58, 54,

	58, 52,

	54, 54,

	58, 162,

	56, 164,

	56, 162,

	60, 162,

	58, 160,

	58, 160,

	58, 162,

	58, 160,

	58, 164,

	58, 48,

	62, 160,

	60, 50,

	58, 50,

	60, 50,

	62, 46,

	60, 52,

	60, 50,

	58, 162,

	58, 50,

	62, 156,

	60, 160,

	60, 162,

	60, 158,

	58, 160,

	64, 3910,

	890, 212,

	60, 0},

 {

// ON, OFF (in 10's of microseconds)
//int LED_White[] =

	888, 434,

	60, 48,

	62, 48,

	60, 50,

	60, 48,

	62, 48,

	60, 50,

	62, 46,

	64, 46,

	60, 160,

	60, 160,

	62, 156,

	62, 158,

	64, 156,

	60, 160,

	60, 158,

	64, 158,

	60, 158,

	62, 158,

	62, 48,

	64, 154,

	64, 46,

	60, 50,

	62, 48,

	62, 46,

	62, 48,

	62, 48,

	62, 158,

	62, 46,

	64, 158,

	60, 158,

	60, 158,

	64, 158,

	62, 3912,

	886, 216,

	60, 0}};



 
void setup()  {        
 // initialize the IR digital pin as an output:
 pinMode(IRledPin, OUTPUT);   
 
 Serial.begin(9600);
}
 
void loop()           
{
 Serial.println("Sending IR signal");
 
 SendIR(0); // lights on
 
 SendIR(0); // lights on
  SendIR(2);
 SendIR(2);
 
 delay(1*1000); // wait one minute (60 seconds * 1000 milliseconds)
 
 SendIR(4); // turn to white
 SendIR(3);
 SendIR(3);

  delay(1*1000); // wait one minute (60 seconds * 1000 milliseconds)
  
  SendIR(1);
   delay(1*1000); // wait one minute (60 seconds * 1000 milliseconds)
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
 
 void SendIR(int num){
   int Signalsize = sizeof(IRLED[num]) / sizeof(IRLED[num][0]);
   for (int i=0; i<Signalsize; i++){
   if (i%2==0){
    pulseIR(IRLED[num][i]*10);
   }
   else{
    delayMicroseconds(IRLED[num][i]*10);
   }
   }
 }
   
 
