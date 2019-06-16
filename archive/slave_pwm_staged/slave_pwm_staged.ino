#include <Wire.h>
int pwm_pin = 6;
int x =0;
int period = 0;
int sync = 8;
int diff;
int real_diff;

void setup() {
  // put your setup code here, to run once:
  pinMode(pwm_pin, OUTPUT);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);

}

void receiveEvent(int bytes){
    x = Wire.read();
    if(x == 1){
      period = random(1,16);
      Serial.print(period);
      }
    switch(x){
      case 1:
      period = random(1,16);
      serial.print(period);
        break
      case 2:
        break
      case 3:
        break
      }
  }
void loop() {
  // put your main code here, to run repeatedly:

  if (x == 1){
    Serial.print("rand");
    for (int i = 127; i < 255; i++){
      analogWrite(pwm_pin, i);
      delay(period);
      }

     for (int i = 255; i > 0; i--){
      analogWrite(pwm_pin, i);
      delay(period);
      }

     for (int i = 0; i < 127; i++){
      analogWrite(pwm_pin, i);
      delay(period);
      }
    }

   if (x == 2){
    Serial.print("trans");
    if(period > sync){
      while (period != sync){
        for (int i = 127; i < 255; i++){
          analogWrite(pwm_pin, i);
          delay(period);
        }

        for (int i = 255; i > 0; i--){
          analogWrite(pwm_pin, i);
          delay(period);
        }

        for (int i = 0; i < 127; i++){
          analogWrite(pwm_pin, i);
          delay(period);
        }
        period = period--;
        }
      }

      else{
        while (period != sync){
        for (int i = 127; i < 255; i++){
          analogWrite(pwm_pin, i);
          delay(period);
        }

        for (int i = 255; i > 0; i--){
          analogWrite(pwm_pin, i);
          delay(period);
        }

        for (int i = 0; i < 127; i++){
          analogWrite(pwm_pin, i);
          delay(period);
        }
        period = period++;
        }
        }

      Serial.print("synced");
      for (int i = 127; i < 255; i++){
          analogWrite(pwm_pin, i);
          delay(period);
        }

      for (int i = 255; i > 0; i--){
          analogWrite(pwm_pin, i);
          delay(period);
        }

      for (int i = 0; i < 127; i++){
          analogWrite(pwm_pin, i);
          delay(period);
        }      
   }

}
