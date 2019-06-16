#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 51; i++){
      int x = i*5;
      Wire.beginTransmission(9);
      Wire.write(x);
      Wire.endTransmission();
      delay(100);
    }
    
    for(int i = 51; i > 0; i--){
      int x = i*5;
      Wire.beginTransmission(9);
      Wire.write(x);
      Wire.endTransmission();
      delay(100);
    }

}
