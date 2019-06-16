#include <Wire.h>
int send_data[3];
int stage;
float interval;
int rspeed;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  //Start random operation stage
  stage = 1;
  interval = 0;
  rspeed = 0;
  Serial.print(stage);
  Wire.beginTransmission(9);
  Wire.write((uint8_t*)&send_data, sizeof(send_data));
  Wire.endTransmission();

  //wait
  delay(30000);

  //Start transition stage
  stage = 2;
  Serial.print(stage);
  Wire.beginTransmission(9);
  Wire.write((uint8_t*)&send_data, sizeof(send_data));
  Wire.endTransmission();

  delay(30000);

  //Start sync stage
  stage = 3;
  interval = 15;
  Serial.print(stage);
  Wire.beginTransmission(9);
  Wire.write((uint8_t*)&send_data, sizeof(send_data));
  Wire.endTransmission();
  

}
