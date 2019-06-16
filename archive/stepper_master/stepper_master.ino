#include <Wire.h>
int x = 0;
int y = 0;
int prex = 2000;
int prey = 2000;
byte data[2];
byte stop_data[2] = {0, 0};
int val = 0;
int PotoAmp = 1;
int PotoSpeed = 2;
bool operate = false;
int Serial_data;

void setup() {
  // Start the I2C Bus as Master
  Wire.begin();

  Serial.begin(9600);

  x = analogRead(PotoAmp);
  y = analogRead(PotoSpeed);
     
  val = map(x, 0, 1023, 20, 100);
  data[0] = (byte) val;
  val = map(y, 0, 1023, 30, 90);
  data[1] = (byte) val;
}
void loop() {
     x = analogRead(PotoAmp);
     y = analogRead(PotoSpeed);
     
     val = map(x, 0, 1023, 20, 100);
     data[0] = (byte) val;
     val = map(y, 0, 1023, 30, 90);
     data[1] = (byte) val;
     if((data[0] != prex || data[1] != prey) && operate){
//       for(int i = 0; i < 2; i++){
//        Serial.println(data[i]);
//       }
    
       Wire.beginTransmission(9); // transmit to device #9
       Wire.write(data, 2);              // sends data 
       Wire.endTransmission(); // stop transmitting
       
       prex = data[0];
       prey = data[1]; 
       
       delay(10000);
     }
}

void serialEvent() {
  Serial_data = Serial.read();
  if(Serial_data == 1){
    operate = true;
    }
  else if (Serial_data == 0 || Serial_data == 2){
    operate = false;
    Wire.beginTransmission(9); // transmit to device #9
    Wire.write(stop_data, 2);              // sends data 
    Wire.endTransmission();
    }
  }
