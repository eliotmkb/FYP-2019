#include <Wire.h>
int x = 0;
int y = 0;
//Array with percentage delay values dels[3] = 16000 = 100%
const unsigned int dels[9] = {6400, 9600, 12800, 16000, 19200, 22400, 25600, 28800, 32000};
byte mot1[6];
byte mot2[6];
byte stop_data[6] = {0, 0, 0, 0, 0, 0};
unsigned int bigval;
int Serial_data;
const int ledPin = 13;

void setup() {
  // Start the I2C Bus as Master
  Wire.begin();

  Serial.begin(9600);
  randop();
  digitalWrite(ledPin, HIGH);

//    switch(y){
//      case 3:
//      mot2[4] = y*10;
//      bigval = round((dels[x] - 2151.5)/1.2373);
//      mot2[3] = (bigval & 0xF000) >> 12;
//      mot2[2] = (bigval & 0x0F00) >> 8;
//      mot2[1] = (bigval & 0x00F0) >> 4;
//      mot2[0] = (bigval & 0x000F);
//      break;
//      
//      case 4:
//      mot2[4] = y*10;
//      bigval = round((dels[x] - 1602.5)/1.6398);
//      mot2[3] = (bigval & 0xF000) >> 12;
//      mot2[2] = (bigval & 0x0F00) >> 8;
//      mot2[1] = (bigval & 0x00F0) >> 4;
//      mot2[0] = (bigval & 0x000F);
//      break;
//      
//      case 5:
//      mot2[4] = y*10;
//      bigval = round((dels[x] - 1133.5)/2.0423);
//      mot2[3] = (bigval & 0xF000) >> 12;
//      mot2[2] = (bigval & 0x0F00) >> 8;
//      mot2[1] = (bigval & 0x00F0) >> 4;
//      mot2[0] = (bigval & 0x000F);
//      break;
//      
//      case 6:
//      mot2[4] = y*10;
//      bigval = round((dels[x] - 747)/2.4445);
//      mot2[3] = (bigval & 0xF000) >> 12;
//      mot2[2] = (bigval & 0x0F00) >> 8;
//      mot2[1] = (bigval & 0x00F0) >> 4;
//      mot2[0] = (bigval & 0x000F);
//      break;
//      
//      case 7:
//      mot2[4] = y*10;
//      bigval = round((dels[x] - 440)/2.847);
//      mot2[3] = (bigval & 0xF000) >> 12;
//      mot2[2] = (bigval & 0x0F00) >> 8;
//      mot2[1] = (bigval & 0x00F0) >> 4;
//      mot2[0] = (bigval & 0x000F);
//      break;
//      
//      case 8:
//      mot2[4] = y*10;
//      bigval = round((dels[x] - 213.5)/3.2493);
//      mot2[3] = (bigval & 0xF000) >> 12;
//      mot2[2] = (bigval & 0x0F00) >> 8;
//      mot2[1] = (bigval & 0x00F0) >> 4;
//      mot2[0] = (bigval & 0x000F);
//      break;
//      
//      case 9:
//      mot2[4] = y*10;
//      bigval = round((dels[x] - 66.5)/3.6518);
//      mot2[3] = (bigval & 0xF000) >> 12;
//      mot2[2] = (bigval & 0x0F00) >> 8;
//      mot2[1] = (bigval & 0x00F0) >> 4;
//      mot2[0] = (bigval & 0x000F);
//      break;
//      }

}
void loop() {

}

void serialEvent() {
  Serial_data = Serial.read();
  if(Serial_data == 1){
    send_data(mot1, 9);
    send_data(mot2, 10);
    }
  else if (Serial_data == 0 || Serial_data == 2){
    send_data(stop_data, 9);
    send_data(stop_data, 10);
    }

    delay(5000);
    syncop();
    send_data(mot1, 9);
    send_data(mot2, 10);
    randop();
  }

  void randop(){
    //ref motor at 600 speed
  bigval = round((dels[3] - 747)/2.4445);
  mot1[3] = (bigval & 0xF000) >> 12;
  mot1[2] = (bigval & 0x0F00) >> 8;
  mot1[1] = (bigval & 0x00F0) >> 4;
  mot1[0] = (bigval & 0x000F);
  mot1[4] = 60;
  mot1[5] = 2;

  //x = random(0, 9);
  x = 0;
  //Serial.println(x);
  //y = random(3, 10);
  //Serial.println(y);
  mot2[5] = 5;
  mot2[4] = 30;
  bigval = round((dels[x] - 2151.5)/1.2373);
  mot2[3] = (bigval & 0xF000) >> 12;
  mot2[2] = (bigval & 0x0F00) >> 8;
  mot2[1] = (bigval & 0x00F0) >> 4;
  mot2[0] = (bigval & 0x000F);
    }

void syncop(){
      bigval = round((dels[3] - 747)/2.4445);
      mot1[3] = (bigval & 0xF000) >> 12;
      mot1[2] = (bigval & 0x0F00) >> 8;
      mot1[1] = (bigval & 0x00F0) >> 4;
      mot1[0] = (bigval & 0x000F);
      mot1[4] = 60;
      mot1[5] = 1;
    

      mot2[5] = mot1[5];
      mot2[4] = mot1[4];
      mot2[3] = mot1[3];
      mot2[2] = mot1[2];
      mot2[1] = mot1[1];
      mot2[0] = mot1[0];
      }

void send_data(byte data[], int slave){
  Wire.beginTransmission(slave); // transmit to device #slave
  Wire.write(data, 6);              // sends data 
  Wire.endTransmission();
  
  }
