//dealy =  1000/FPS 
int program = 0;
void setup() {
  Serial.begin(115200);
}

void loop() {
  if(program==0){
      for(float i = 0;i<255;i++){
        Serial.print(i);      
        Serial.print(';');
        delay(16.6);
      }
      for(float i = 255;i>0;i--){
        Serial.print(i);      
        Serial.print(';');
        delay(16.6);
      }
  }
  if(program==1){
        for(float i = 0;i<255;i=i+0.1){
        Serial.print(sin(i)*100);      
        Serial.print(';');
        delay(16.6);
      }        
    }
    if(program==2){
        pinMode(12,OUTPUT);
        pinMode(15,INPUT);
        digitalWrite(12,1);
        Serial.print(analogRead(15));
        Serial.print(';');
        delay(16.33);
        //digitalWrite(12,0);
        //Serial.print((analogRead(15)/4095)*100);
        //Serial.print(';');
        //delay(16.33/2);
      }
   if(program==3){
      for(float i = 0;i<3;i=i+0.1){
        Serial.print(i);      
        Serial.print(';');
        delay(16.6);
      }
      for(float i = 3;i>0;i=i-0.1){
        Serial.print(i);      
        Serial.print(';');
        delay(16.6);
      }
  }          

}
