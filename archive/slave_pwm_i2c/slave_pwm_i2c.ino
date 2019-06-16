#include <Wire.h>
int pwm_pin = 6;
int x =0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pwm_pin, OUTPUT);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);

}

void receiveEvent(int bytes){
    x = Wire.read();
  }
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(x);
  analogWrite(pwm_pin, x);

}
