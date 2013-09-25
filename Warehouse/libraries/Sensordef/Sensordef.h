 #ifndef SENSORDEF_H
   #define SENSORDEF_H
   #include <Arduino.h>
   
   
    
   class Sensor {
    public:
     int pinin, pinout, pin_value, low_user_value, low_r_value, high_r_value, other_r_value, high_user_value; // Low / high values denote the min/max that can come off the pin, and what they relate to on a linear scale in terms of the user (can be modded to min/max at 0/255
     int pinouts, sensor_value;
     char name[15];
     char units[15];
     float max_in, min_in, m, b;
	   //int test1, test2;
    void  update();
	   Sensor( int tpinin, int tpinout, const char[15] tname, const char[15] tunits, int tlow_user,  int thigh_user, int tlow_r_value, long int thigh_r_value, int tother_r_value);
	   ~Sensor();
 }
#endif
