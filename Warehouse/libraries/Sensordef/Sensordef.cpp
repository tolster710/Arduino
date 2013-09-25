 #include "Sensordef.h"
   
Sensor::Sensor( int tpinin, int tpinout, const char[15] tname, const char[15] tunits, int tlow_user,  int thigh_user, int tlow_r_value, long int thigh_r_value, int tother_r_value){       //constructor
         pinin=tpinin;  
         pinouts=tpinout;   //sets pin
         pinMode(pinin, INPUT);       //sets pin to output
         pin_value = analogRead(pinin);       // reads initial value
         low_r_value = tlow_r_value;
         high_r_value = thigh_r_value;
         other_r_value = tother_r_value;
         low_user_value = tlow_user;
         high_user_value = thigh_user;
		 name
         
         max_in = ((low_r_value)/(low_r_value+other_r_value))*255;
         min_in = ((high_r_value)/(high_r_value+other_r_value))*255;
         m = (((high_user_value)-(low_user_value))/((max_in)-(min_in)));
         b = high_user_value-(m*max_in);
     }
     Sensor::-Sensor(){}
     
         void Sensor::update(){
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
