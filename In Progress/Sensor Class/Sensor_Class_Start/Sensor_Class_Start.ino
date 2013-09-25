
/*
int sensor_read[photo_read, therm_read = 0;
float therm_fahrenheit, photo_value;

int analogvalue[3];
 
 
 //setup

   pinMode(pins[14], INPUT); //Therm
   pinMode(pins[15], INPUT); //Photocell
   pinMode(pins[16], OUTPUT);  // output to led
   
   //on clockup
   
   void AnalogUpdate(){
     for(i=0;i<2;i++){
     analogvalue[i] = analogRead(pin[i+14]);
     
   
   */
   
    
   class Sensor {
    public:
     int pinin, pinout, pin_value, low_user_value, low_r_value, high_r_value, other_r_value, high_user_value; // Low / high values denote the min/max that can come off the pin, and what they relate to on a linear scale in terms of the user (can be modded to min/max at 0/255
     int pinouts, sensor_value;
     char name[15];
     char units[15];
     float max_in, min_in, m, b;
   
     Sensor( int tpinin, int tpinout, char tname[15], char tunits[15], int tlow_user,  int thigh_user, int tlow_r_value, int thigh_r_value, int tother_r_value){       //constructor
         pinin=tpinin;  
         pinouts=tpinout;   //sets pin
         pinMode(pinin, INPUT);       //sets pin to output
         pin_value = analogRead(pinin);       // reads initial value
         low_r_value = tlow_r_value;
         high_r_value = thigh_r_value;
         other_r_value = tother_r_value;
         low_user_value = tlow_user;
         high_user_value = thigh_user;
         
         max_in = ((low_r_value)/(low_r_value+other_r_value))*255;
         min_in = ((high_r_value)/(high_r_value+other_r_value))*255;
         m = (((high_user_value)-(low_user_value))/((max_in)-(min_in)));
         b = high_user_value-(m*max_in);
     }
     
         void update(){
           pin_value = analogRead(pinin);
           sensor_value = (pin_value*m)+b;
           //Serial.print(name ": "sensor_value" " units);
           Serial.print(name);
           Serial.print(" :");
           Serial.print(sensor_value);
           Serial.print("  ");
           Serial.print(units);
           Serial.println("");
           
           if(pinouts<=50){
             analogWrite(pinouts,sensor_value);
           }
         }
     
   };
   
   //Rest of the code correct - it doesnt like the declaration of Sensor anywhere.
   
   
   
   Sensor Photo();
   void setup(){
       Sensor Photo =   Sensor(11,13, "Photo", "Intensity", 0, 255, 100, 100000, 1000);
       Serial.begin(9600);
   }
   
  // as an object
  
          

     void loop(){
       Photo.update();
     }
