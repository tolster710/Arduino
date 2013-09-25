
#include <MenuBackend.h>


#include <Wire.h>
#include <LiquidCrystal.h>


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
	60, 0}};
 







 LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);
 
 int IRledPin = 3;  // LED connected to digital pin 3
 int adc_key_val[5] ={50, 200, 400, 600, 800 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;

/*
	This program demonstrates a menu modeled after the menubar in the Arduino IDE
	
   +root
	+file			+edit   +sketch			+tools			+help
	 +new			 +cut	 +verify (V)	 +autoformat	 +environment
	 +open
	 +examples
	  +ArduinoISP
*/

//this controls the menu backend and the event generation
MenuBackend menu = MenuBackend(menuUseEvent,menuChangeEvent);
	//beneath is list of menu items needed to build the menu
	MenuItem IRLEDFunc = MenuItem("IR Functions");
          MenuItem LEDOn = MenuItem("LED On    ");
          MenuItem LEDOff = MenuItem("LED Off  ");
          MenuItem LEDBright_Down = MenuItem("Bright Down");
          MenuItem LEDBright_Up = MenuItem("Bright Up");
          MenuItem LEDFlash = MenuItem("LED Flash");
         
     MenuItem IRLEDColor = MenuItem("LED Color");
            MenuItem LEDC_Red = MenuItem("Red");
            MenuItem LEDC_White = MenuItem("White");
            MenuItem LEDC_Blue = MenuItem("Blue");

//this function builds the menu and connects the correct items together
void menuSetup()
{
	Serial.println("Setting up menu...");
	//add the file menu to the menu root
	//when add is used, as opposed to addX as you see below, the item is added below the item it's added to
	menu.getRoot().add(IRLEDFunc);
      //Make IRLEDFunc the root option
      IRLEDFunc.add(LEDOn).add(LEDOff).add(LEDBright_Down).add(LEDBright_Up).add(LEDFlash);
      
      IRLEDFunc.addRight(IRLEDColor).add(LEDC_Red).add(LEDC_White).add(LEDC_Blue);
}

/*
	This is an important function
	Here all use events are handled
	
	This is where you define a behaviour for a menu item
*/
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

/*
	This is an important function
	Here we get a notification whenever the user changes the menu
	That is, when the menu is navigated
*/
void menuChangeEvent(MenuChangeEvent changed)
{
        lcd.clear();
	lcd.print("Change ");
	//lcd.print(changed.from.getName());
	lcd.print(" ");
	lcd.println(changed.to.getName());

        Serial.print("Menu change ");
	Serial.print(changed.from.getName());
	Serial.print(" to ");
	Serial.println(changed.to.getName());
      delay(100);
}
void setup()
{
	Serial.begin(9600);
	lcd.clear(); 
  lcd.begin(16, 2);
  lcd.setCursor(0,0); 
  lcd.print("Tolly IR Blaster");
  
	menuSetup();
	Serial.println("Starting navigation (see source for description):");

	menu.moveDown();  //move to root
	
}

void loop()
{
  //
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
void SendIR(int num){
   Serial.print("Sending Signal ");
   Serial.println(num);
   cli(); // this turns off any background interrupts
   int Signalsize = sizeof(IRLED[num]) / sizeof(IRLED[num][0]);
  
   for (int i=0; i<Signalsize; i++){
   if (i%2==0){
    pulseIR(IRLED[num][i]*10);
   }
   else{
    delayMicroseconds(IRLED[num][i]*10);
   }
   }
    sei(); // this turns them back on
 }
 /////////////////////////////////////////////////////////////////////////////////////
 
 void pulseIR(long microsecs) {
 // we'll count down from the number of microseconds we are told to wait
 

 
 while (microsecs > 0) {
  // 38 kHz is about 13 microseconds high and 13 microseconds low
  digitalWrite(IRledPin, HIGH); // this takes about 3 microseconds to happen
  delayMicroseconds(10);     // hang out for 10 microseconds, you can also change this to 9 if its not working
  digitalWrite(IRledPin, LOW);  // this also takes about 3 microseconds
  delayMicroseconds(10);     // hang out for 10 microseconds, you can also change this to 9 if its not working
 
  // so 26 microseconds altogether
  microsecs -= 26;
 }
 

}
 
 



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


