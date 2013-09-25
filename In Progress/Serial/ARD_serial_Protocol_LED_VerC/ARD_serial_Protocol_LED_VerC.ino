


const int zero = 0;

                            //LEDs
int LED_Pins[3] = {9,10,11};                                 //RGB Output pins
int LED_Val[3] = {0,0,0};


                              //RX
boolean RX_Started = 0;
boolean RX_First_Run=0;
byte RX_Buffer[256] = {0};
int RX_Start_Byte = 0;
int RX_End_Byte = 0;
int RX_Length = 30;
int RX_Data_Count = 0;

                              //SYS
int SYS_Start_Byte = 0x80;
int SYS_End_Byte = 0XFE;

                            //Parse
int RX_Parse_Pos = 2;


void setup(){
  Serial.begin(9600);
  for(int i=0;i<3;i++){
   pinMode(LED_Pins[i], OUTPUT);  }
}

void loop() {
  LED_Update();
  while (Serial.available() > RX_Data_Count){
      if(RX_First_Run==1){RX_First_Run=0;}
     if(RX_Started==0)
     {
         RX_Buffer[0] = Serial.read();
         //RX_Data_Count++;
         if (RX_Buffer[0] == SYS_Start_Byte)
         {
             RX_Started = 1;
             RX_First_Run = 1;
             
             Serial.print("S: ");
            /* Serial.print(RX_Start_Byte);
             Serial.println("  ");*/                                                   //debug
           }
         RX_Data_Count++;
     }
     if(RX_Started==1 && RX_First_Run==0)
     {
       
       RX_Buffer[RX_Data_Count] = Serial.read();
       //RX_Data_Count++;
       
       Serial.print(RX_Data_Count);
       Serial.print(",");
       Serial.print(RX_Buffer[RX_Data_Count]); 
      Serial.println(" ");      //DEBUG
       
       if(RX_Data_Count == 1){
              RX_Length = RX_Buffer[1];
              Serial.print("L:"); Serial.print(RX_Length);Serial.println("   ");                                     //DEBUG
       }
       if(RX_Data_Count>=RX_Length){   
        Serial.flush();         //sub back in RX_Length - DONE
         RX_Check_End();
       }
      RX_Data_Count++;
     
     }
  }
  
}
         //6/29 - Does not reset the counter after a good or bad packet - Serial.Flush is called and the counter is reset to 0
         // try to define a minimum backoff time to allow the serial buffer to reset itself
   
void RX_Check_End(){
  RX_End_Byte = RX_Buffer[RX_Length-1];
  Serial.println("CCC");  //DEBUG
  Serial.flush();
  if(RX_End_Byte==SYS_End_Byte){
                                     //END PACKET 
     RX_Parse_Data();
     RX_Started=0;
     RX_Data_Count = zero;
     RX_Length=64;
     
  }
  else{ //Bad_Packet
  Serial.println("BBB");
                  //RX_Parse_Data();
  RX_Started=0;
  RX_Data_Count = zero;
  RX_Length = 64;
  
  }
 
}
  void RX_Parse_Data(){
    RX_Parse_Pos = 2;
    Serial.println("PPP");                       //DEBUG
    while(RX_Parse_Pos <= RX_Data_Count){
      switch(RX_Buffer[RX_Parse_Pos]){
        case 0x90: LED_SerialIn(RX_Parse_Pos+1); Serial.println("LDS");break;
        //case 146: DISP_SerialIn(RX_Parse_Pos+1); break;                                      //future
        default : RX_Parse_Pos++; break;
      }
    }
      if(RX_Parse_Pos >= RX_Data_Count){
        RX_Data_Count = 0; RX_Parse_Pos=2; 
    
    }
  }
    
    void LED_SerialIn(int x){
      for( int i=0;i<3; i++){
        LED_Val[i] = RX_Buffer[i+x];
      }
      RX_Parse_Pos+=4;
      LED_Update();
    }
    
    void LED_Update(){
      for(int i=0; i <3; i++){
        analogWrite(LED_Pins[i], LED_Val[i]%255);
      }
    }
