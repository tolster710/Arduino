






//#include <Sensordef.h>

#include <TimerOne.h>
#include <DHT.h>

#define DHTPIN 20
#define DHTTYPE DHT11



//SENSOR CLASS CODE
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
         
         for(int i=0; i<16; i++){
         name[i] = tname[i];
         units[i] = tunits[i];
         }
         
         max_in = ((low_r_value)/(low_r_value+other_r_value))*1024;
         min_in = ((high_r_value)/(high_r_value+other_r_value))*1024;
         m = (((high_user_value)-(low_user_value))/((max_in)-(min_in)));
         b = high_user_value-(m*max_in);
         
          Serial.print("m,b ==     ");
         Serial.print(m);
         Serial.print(" , ");
         Serial.println(b);
     }
     
         void update(){
           pin_value = analogRead(pinin);
           Serial.println(pin_value);
           sensor_value = (pin_value*m)+b;
           //Serial.print(name ": "sensor_value" " units);
           Serial.print(name);
           Serial.print(" :");
           Serial.print(sensor_value);
           Serial.print("  ");
           Serial.print(units);
           Serial.println("   ");
           
           if(pinouts<=50){
             analogWrite(pinouts,sensor_value);
           }
         }
     
   };






//DHT Sensor
DHT dht(DHTPIN, DHTTYPE);




int col = 0;
byte leds[32][8] = {\
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
      
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \

 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \

 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0}, \
 { 0,0,0,0,0,0,0,0} \ 

};


const boolean zero[5][3] = { 
        {1,1,1}, 
        {1,0,1}, 
        {1,0,1},
        {1,0,1},
        {1,1,1}
};
const boolean one[5][3] = { 
        {1,1,1}, 
        {0,1,0}, 
        {0,1,0},
        {1,1,0},
        {0,1,0}
};
const boolean two[5][3] = { 
        {1,1,1}, 
        {1,0,0}, 
        {1,1,1},
        {0,0,1},
        {1,1,1}
};
const boolean three[5][3] = { 
        {1,1,1}, 
        {0,0,1}, 
        {1,1,1},
        {0,0,1},
        {1,1,1}
};
const boolean four[5][3] = { 
        {0,0,1}, 
        {0,0,1}, 
        {1,1,1},
        {1,0,1},
        {1,0,1}
};
const boolean five[5][3] = { 
        {1,1,1}, 
        {0,0,1}, 
        {1,1,1},
        {1,0,0},
        {1,1,1}
};
const boolean six[5][3] = { 
        {1,1,1}, 
        {1,0,1}, 
        {1,1,1},
        {1,0,0},
        {1,0,0}
};
const boolean seven[5][3] = { 
        {0,0,1}, 
        {0,0,1}, 
        {0,0,1},
        {0,0,1},
        {1,1,1}
};
const boolean eight[5][3] = { 
        {1,1,1}, 
        {1,0,1}, 
        {1,1,1},
        {1,0,1},
        {1,1,1}
};
const boolean nine[5][3] = { 
        {0,0,1}, 
        {0,0,1}, 
        {1,1,1},
        {1,0,1},
        {1,1,1}
};
const boolean null[5][3] = { 
        {0,0,0}, 
        {0,0,0}, 
        {0,0,0},
        {0,0,0},
        {0,0,0}
};

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[16]= {24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,39};
//int pins[16]={0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15 

// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[0], pins[1], pins[2], pins[3], pins[4], pins[5], pins[6], pins[7]};

// row[xx] of leds = pin yy on led matrix
int rows[6] = { pins[12], pins[13], pins[11], pins[10], pins[9], pins[8]};
int given[6] = {0,1,0,0,0,0}; // column to increment

int RowWrite = 0;
const int numPatterns = 6;

int VirtArray1[5][3];
int VirtArray2[5][3];
int VirtArray3[5][3];
int VirtArray4[5][3];
int VirtArray5[5][3];
int VirtArray6[5][3];


int h0 = 0;
int h1 = 9;
int m0 = 2;
int m1 = 9;
int s0 = 3;
int s1 = 0;
int hours = 9;

int timerPeriod = 499;
int secThreshold = 2000;
int secCount = 0;





Sensor Photo(6,13, "Photo", "_Intensity",255, 0, 100, 50000, 2700);
 //sensor setup
Sensor Thermo(7, 54, "Thermo", " deg F", 300, 100, 100, 300, 390);


void setup() {
 // sets the led pins as output
 for (int i = 0; i <= 13; i++) {
   pinMode(pins[i], OUTPUT);
 }
 pinMode(22, INPUT);

//set the switch pins to input
  pinMode(pins[14], INPUT);
  pinMode(pins[15], INPUT);
 // set up cols and rows
 for (int i = 1; i <= 8; i++) {
   digitalWrite(cols[i - 1], LOW);
 }

 for (int i = 0; i < 6; i++) {
   digitalWrite(rows[i], LOW);
 }

 Serial.begin(38400);
 Serial.println("Entering the loop...");
 Serial.println("DHT11 Test!");
 dht.begin();
 
 
 Timer1.initialize(timerPeriod);
 Timer1.attachInterrupt(increment);
 
 
}













void loop(){

 /*RowWrite++;
 if (RowWrite > 31)
     {RowWrite = 0;}
    // Serial.println(RowWrite);
*/
   

}
void rewrite(){
  
switch(h0){
   
  case 1: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray1[a][b] = one[a][b];}
        }break;
    case 2: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray1[a][b] = two[a][b];}
        }break;
       default: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray1[a][b] = null[a][b];}
        }break; 
}
switch(h1){
   
 case 0: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray2[a][b] = zero[a][b];}
        }break;
  case 1: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray2[a][b] = one[a][b];}
        }break;
    case 2: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray2[a][b] = two[a][b];}
        }break;
    case 3: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray2[a][b] = three[a][b];}
        }break;    
    case 4: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray2[a][b] = four[a][b];}
        }break;    
    case 5: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray2[a][b] = five[a][b];}
        }break; 
    case 6: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray2[a][b] = six[a][b];}
        }break;    
    case 7: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray2[a][b] = seven[a][b];}
        }break;    
     case 8: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray2[a][b] = eight[a][b];}
        }break;   
     case 9: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray2[a][b] = nine[a][b];}
        }break;   
       default: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray2[a][b] = null[a][b];}
        }break; 
}
  switch(m0){
   
 case 0: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray3[a][b] = zero[a][b];}
        }break;
  case 1: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray3[a][b] = one[a][b];}
        }break;
    case 2: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray3[a][b] = two[a][b];}
        }break;
    case 3: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray3[a][b] = three[a][b];}
        }break;    
    case 4: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray3[a][b] = four[a][b];}
        }break;    
    case 5: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray3[a][b] = five[a][b];}
        }break; 
    case 6: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray3[a][b] = six[a][b];}
        }break;    
    case 7: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray3[a][b] = seven[a][b];}
        }break;    
     case 8: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray3[a][b] = eight[a][b];}
        }break;   
     case 9: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray3[a][b] = nine[a][b];}
        }break;   
       default: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray3[a][b] = null[a][b];}
        }break; 
}
switch(m1){
   
 case 0: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray4[a][b] = zero[a][b];}
        }break;
  case 1: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray4[a][b] = one[a][b];}
        }break;
    case 2: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray4[a][b] = two[a][b];}
        }break;
    case 3: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray4[a][b] = three[a][b];}
        }break;    
    case 4: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray4[a][b] = four[a][b];}
        }break;    
    case 5: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray4[a][b] = five[a][b];}
        }break; 
    case 6: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray4[a][b] = six[a][b];}
        }break;    
    case 7: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray4[a][b] = seven[a][b];}
        }break;    
     case 8: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray4[a][b] = eight[a][b];}
        }break;   
     case 9: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray4[a][b] = nine[a][b];}
        }break;   
       default: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray4[a][b] = null[a][b];}
        }break; 
}
switch(s0){
   
 case 0: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray5[a][b] = zero[a][b];}
        }break;
  case 1: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray5[a][b] = one[a][b];}
        }break;
    case 2: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray5[a][b] = two[a][b];}
        }break;
    case 3: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray5[a][b] = three[a][b];}
        }break;    
    case 4: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray5[a][b] = four[a][b];}
        }break;    
    case 5: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray5[a][b] = five[a][b];}
        }break; 
    case 6: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray5[a][b] = six[a][b];}
        }break;    
    case 7: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray5[a][b] = seven[a][b];}
        }break;    
     case 8: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray5[a][b] = eight[a][b];}
        }break;   
     case 9: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray5[a][b] = nine[a][b];}
        }break;   
       default: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray5[a][b] = null[a][b];}
        }break; 
}
   switch(s1){
   
 case 0: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray6[a][b] = zero[a][b];}
        }break;
  case 1: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray6[a][b] = one[a][b];}
        }break;
    case 2: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray6[a][b] = two[a][b];}
        }break;
    case 3: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray6[a][b] = three[a][b];}
        }break;    
    case 4: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray6[a][b] = four[a][b];}
        }break;    
    case 5: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray6[a][b] = five[a][b];}
        }break; 
    case 6: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray6[a][b] = six[a][b];}
        }break;    
    case 7: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray6[a][b] = seven[a][b];}
        }break;    
     case 8: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray6[a][b] = eight[a][b];}
        }break;   
     case 9: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray6[a][b] = nine[a][b];}
        }break;   
       default: for(int a =0; a<5; a++)
    {for(int b = 0; b<3; b++)
      {VirtArray6[a][b] = null[a][b];}
        }break; 
}

for(int x = 0; x<5; x++){
  for(int y = 0; y<3; y++){
    
    leds[x+8][y] = VirtArray1[x][y];
    leds[x+8][y+4] = VirtArray2[x][y];
    leds[x+16][y] = VirtArray3[x][y];
    leds[x+16][y+4] = VirtArray4[x][y];
    leds[x+24][y] = VirtArray5[x][y];
    leds[x+24][y+4] = VirtArray6[x][y];
    
  }
}





   }


void Clockup(){
  Photo.update();
  Thermo.update();
  if (s1 > 9)
    {s1 = 0;
    s0++;
    //DHTUpdate();
    if (s0 > 5){
      s0 = 0;
      m1++;
      if(m1 > 9){
        m1 = 0;
        m0++;
        if(m0 > 5){
          m0 = 0;
          h1++;
          hours++;
          if(h1 > 9){
            h1 = 0;
            
            h0=1;
          
          
        
          }
        }
        if(hours > 12){
            hours = 1;
            h1 = 1;
            h0 = 0;
          }
      }
    }
    }
    rewrite();
    
}



 /*void test(){
     
     
     for(int a = 0; a < 5; a++)
    {
      
      for(int b = 0; b < 3; b++)
      {
        if( h0 == 0){
         // memcpy (VirtArray1, zero, sizeof VirtArray1);
          VirtArray1[a][b] = zero[a][b];
        }
       
        
      }
    }
   }
*/


void increment(){
  
  RowWrite++;
 if (RowWrite > 31)
     {RowWrite = 0;}
    // Serial.println(RowWrite);
  
  //count the seconds
  secCount++;
  if(secCount >= secThreshold)
    { secCount = 0;
      s1++;
      Clockup();
    }
  
   for(int col = 0; col < 8; col++)
   {
          digitalWrite(cols[col], LOW);
        }
  
 //incrementing the rows array
  if (given[5] == 0){
         given[5]=1;      
         }
   else{
           given[5] = 0;
           if (given[4] == 0){
             given[4] = 1;
             }
           else{
               given[4] = 0;
               if (given[3] == 0){
                 given[3] = 1;
                 }
               else{
                   given[3] = 0;
                  if (given[2] == 0){
                   given[2] = 1;
                    }
                 else{
                     given[2] = 0;
                      if (given[1] == 0){
                       given[1] = 1;
                       given[0] = 0;
                       }
                      else{
                         given[1] = 0;
                         given[0] = 1;
                       }
                      }
                   }
                 }
             }

  /* Serial.println("this iteration of given");
   for(int j = 0; j<6; j++){
     Serial.print(given[j]);
 
 
 
   }*/
   
   for (int i = 0; i<6; i++){
     if ( given[i] == 1)
       { digitalWrite(rows[i], HIGH);}
      else{
         digitalWrite(rows[i], LOW);}
   }
  

   for(int col = 0; col < 8; col++)
   {
       if (leds[RowWrite][col] == 1)
        {
          digitalWrite(cols[col], HIGH);
        }
        else{
           digitalWrite(cols[col], LOW);
        }
   }
   
   
 
   
}
  

void DHTUpdate(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
    if (isnan(t) || isnan(h)){
      Serial.println("Failed to read DHT11");
      Serial.println(h);
      Serial.println(t);
    }
    else{
      Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }
}
