//dummy libray

//header

 #ifndef TESTH_H
   #define TESTH_H
   #include <Arduino.h>
  
   
   class test {
     public:
       int x, y;
       void calcu();
       test(int tx);
   }
   
   #endif
   
   
   
   
   #include "TestH.h"
   
     test::test(int tx){
       x=tx;
       y=x;
     }
     void test:calcu(){
       y=y*y;
     }
     
   
