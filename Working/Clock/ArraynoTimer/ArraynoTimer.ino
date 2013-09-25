








#include <TimerOne.h>


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
int pins[16]= {26,28,30,32,34,36,23,25,27,29,31,33,35,9,10,11};

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









void setup() {
 // sets the led pins as output
 for (int i = 0; i <= 13; i++) {
   pinMode(pins[i], OUTPUT);
 }

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
  if (s1 > 9)
    {s1 = 0;
    s0++;
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
  


