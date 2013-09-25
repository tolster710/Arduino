
//purpose of this is to read voltage from pin input - determing source files of IRda remote
int INPUT_Pins[2] = {14,15};
int OUTPUT_Pins[2] = {9,10};
int value[2];


void setup(){
  Serial.begin(19200);
  for(int i=0;i<2;i++){
    pinMode(INPUT_Pins[i], INPUT);
    pinMode(OUTPUT_Pins[i], OUTPUT);
  }
}
void loop()
{
  for(int j = 0; j<20; j++){
for (int i=0; i<2; i++){
  value[i] = analogRead(INPUT_Pins[i]);
}

Serial.print(INPUT_Pins[0]);
Serial.print(",");
  }
  Serial.println(" ");
}
  


