// MENU TEST
// 4/9/13



#include <MenuBackend.h>
#include <Wire.h>
#include <LiquidCrystal.h>

//Liquid crystal and keys backend

int IRledPin = 3;  // LED connected to digital pin 3
 LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);
 
int adc_key_val[5] ={50, 200, 400, 600, 800 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

/*  0 - led on
    1- led off
    2 - led brightness down
    3 - led brightness up
    4 - White color
    


*/
int IRLED[][80]=

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




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////




//Serial.begin(9600);

/////////////////////////////////////////////////////////////////////////////////////






//this controls the menu backend and the event generation
MenuBackend menu = MenuBackend(menuUseEvent,menuChangeEvent);
//Serial.print("Setting up MenuBackend");

	//beneath is list of menu items needed to build the menu

    MenuItem IRLEDFunc = MenuItem("IRFunctions");
          MenuItem LEDOn = MenuItem("LEDOn");
          MenuItem LEDOff = MenuItem("LEDOff");
          MenuItem LEDBright_Down = MenuItem("BrightDown");
          MenuItem LEDBright_Up = MenuItem("BrightUp");
          MenuItem LEDFlash = MenuItem("LEDFlash");
         
     MenuItem IRLEDColor = MenuItem("LEDColor");
            MenuItem LEDC_Red = MenuItem("Red");
            MenuItem LEDC_White = MenuItem("White");
            MenuItem LEDC_Blue = MenuItem("Blue");
         
         
         //this function builds the menu and connects the correct items together
         
         
    /////////////////////////////////////////////////////////////////////////////////////     
       
  /////////////////////////////////////////////////////////////////////////////////////
    
void menuSetup()
{
	Serial.println("Setting up menu...");
      menu.getRoot().add(IRLEDFunc);
      //Make IRLEDFunc the root option
      IRLEDFunc.add(LEDOn).add(LEDOff).add(LEDBright_Down).add(LEDBright_Up).add(LEDFlash);
      
      IRLEDFunc.addRight(IRLEDColor).add(LEDC_Red).add(LEDC_White).add(LEDC_Blue);
      
}


/////////////////////////////////////////////////////////////////////////////////////

void menuUseEvent(MenuUseEvent used)
{
	Serial.print("Menu use ");
	Serial.println(used.item.getName());

      
         
        if (used.item == LEDOn)    {         SendIR(0);    }
         else if (used.item == LEDOff)  {        SendIR(1);      }
        else if (used.item == LEDBright_Down){        SendIR(2);    }
       else  if (used.item == LEDBright_Up)  {         SendIR(3);      }
       else if (used.item == LEDFlash)  {          SendIR(6);      }    //not implemented  
       else if (used.item == LEDC_White)      {        SendIR(4);        }
        
        else { Serial.println("Function not implemented");            }
        
     




	
}
/////////////////////////////////////////////////////////////////////////////////////


void menuChangeEvent(MenuChangeEvent changed)
{
        lcd.clear();
	//lcd.print("Menu change ");
	//lcd.print(changed.from.getName());
	lcd.print(" ");
	lcd.println(changed.to.getName());

        Serial.print("Menu change ");
	Serial.print(changed.from.getName());
	Serial.print(" ");
	Serial.println(changed.to.getName());
      delay(10);
}

/////////////////////////////////////////////////////////////////////////////////////


void SendIR(int num){
   Serial.print("Sending Signal ");
   Serial.println(num);
  
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
/////////////////////////////////////////////////////////////////////////////////////

int get_key(unsigned int input)
{
    int k;
   
    for (k = 0; k < NUM_KEYS; k++)
    {
      if (input < adc_key_val[k])
 {
            return k;
        }
   }
   
    if (k >= NUM_KEYS)k = -1;  // No valid key pressed
    return k;
}

/////////////////////////////////////////////////////////////////////////////////////



void keypress( int i){      // takes the keypress and cases it for what it is 
   switch (i) {
     case 5:  Serial.println(i);
     case 4: menu.use();
             break;
     case 3: menu.moveLeft();
             break;
     case 1: menu.moveUp();
             break;
     case 2: menu.moveDown();
             break;
     case 0: menu.moveRight();
             break;
     default: delay(10); Serial.println(i);
              break;
   }
}



/////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////



void setup()  {        
 // initialize the IR digital pin as an output:
 pinMode(IRledPin, OUTPUT);   
 Serial.begin(9600);
	lcd.clear(); 
  lcd.begin(16, 2);
  lcd.setCursor(0,0); 
  lcd.print("Tolly IR Blaster");
      Serial.println("Starting Menu setup");
	menuSetup();
	Serial.println("Starting navigation (see source for description):");
  //delay(5000);
  
}      
         

void loop()           
{
 //Serial.println("Sending IR signal");
   
  adc_key_in = analogRead(0);    // read the value from the sensor 
  key = get_key(adc_key_in);  // convert into key press
 
  if (key != oldkey)   // if keypress is detected
   {
    delay(50);  // wait for debounce time
    adc_key_in = analogRead(0);    // read the value from the sensor 
    key = get_key(adc_key_in);    // convert into key press
    if (key != oldkey)    
    {   
      lcd.setCursor(0, 1);
      oldkey = key;
      if (key >=0){
           
           keypress(key);
           delay(100);
           
      }
    }
  }
 
} 
