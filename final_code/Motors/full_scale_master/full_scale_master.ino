//This code is very similar to the flex_motor_master code which is commented
//The only difference is that here, the number of motors used is not specified by the matlab code but in here (line 12) which doesn't limit us to max. 10 motors

#include <Wire.h>
int x = 0;
int y = 0;
//Array with percentage delay values dels[3] = 16000 = 100%
const unsigned int dels[9] = {6400, 9600, 12800, 16000, 19200, 22400, 25600, 28800, 32000};
byte stop_data[6] = {0, 0, 0, 0, 0, 0};
unsigned int bigval;
int Serial_data;
const int ledPin = 13;
const int nbMotor = 2;
int slave_id[nbMotor];
byte Mot_data[nbMotor][6];
int Mot_cycle[nbMotor];
// Structure of Mot_data[i][j]:
//i is the motor number, 0 being reference
//j is each data type: 0 to 3 are the nbOfSteps, 4 is maxspeed, 5 is iterations


void setup() {
  // Start the I2C Bus as Master
  Wire.begin();

  Serial.begin(9600);

  Mot_cycle[0] = 0;
  slaveSetup();
  randop();
  
//  for(int i = 0; i < nbMotor; i++){
//    Serial.print("Motor ");
//    Serial.print(i);
//    Serial.print(": ");
//    for(int j = 0; j < 6; j++){
//      Serial.print(Mot_data[i][j], DEC);
//      Serial.print(", ");
//      }
//    Serial.println("");  
//    }
    
  digitalWrite(ledPin, HIGH);

}
void loop() {

}

void serialEvent() {
  Serial_data = Serial.read();
  if(Serial_data == 1){
    for(int i = 0; i < nbMotor; i++){
      send_data(Mot_data[i], slave_id[i]);
      }
    }
  else if (Serial_data == 0 || Serial_data == 2){
    for(int i = 0; i < nbMotor; i++){
      send_data(stop_data, slave_id[i]);
      }
    }

    delay(5000);
    syncop();
    for(int i = 1; i < nbMotor; i++){
      send_data(Mot_data[i], slave_id[i]);
      }
    randop();
  }

void randop(){
    randomSeed(analogRead(0));
    
    bigval = round((dels[3] - 747)/2.4445);
    Mot_data[0][3] = (bigval & 0xF000) >> 12;
    Mot_data[0][2] = (bigval & 0x0F00) >> 8;
    Mot_data[0][1] = (bigval & 0x00F0) >> 4;
    Mot_data[0][0] = (bigval & 0x000F);
    Mot_data[0][4] = 60;
    Mot_data[0][5] = 10;
    
    for(int i = 1; i < nbMotor; i++){
      y = random(3, 10);
          switch(y){
          case 3:
          Mot_data[i][4] = y*10;
          x = random(0, 3);
          switch(x){
            case 0: Mot_cycle[i] = 2; break;
            case 1: Mot_cycle[i] = 3; break;
            case 2: Mot_cycle[i] = 4; break;
            }
          bigval = round((dels[x] - 2151.5)/1.2373);
          Mot_data[i][3] = (bigval & 0xF000) >> 12;
          Mot_data[i][2] = (bigval & 0x0F00) >> 8;
          Mot_data[i][1] = (bigval & 0x00F0) >> 4;
          Mot_data[i][0] = (bigval & 0x000F);
          Mot_data[i][5] = 5;
          break;
          
          case 4:
          Mot_data[i][4] = y*10;
          x = random(0, 4);
          bigval = round((dels[x] - 1602.5)/1.6398);
          Mot_data[i][3] = (bigval & 0xF000) >> 12;
          Mot_data[i][2] = (bigval & 0x0F00) >> 8;
          Mot_data[i][1] = (bigval & 0x00F0) >> 4;
          Mot_data[i][0] = (bigval & 0x000F);
          Mot_data[i][5] = 5;
          switch(x){
            case 0: Mot_cycle[i] = 2; break;
            case 1: Mot_cycle[i] = 3; break;
            case 2: Mot_cycle[i] = 4; break;
            case 3: Mot_cycle[i] = 5; break;
            }
          break;
          
          case 5:
          Mot_data[i][4] = y*10;
          x = random(0, 5);
          bigval = round((dels[x] - 1133.5)/2.0423);
          Mot_data[i][3] = (bigval & 0xF000) >> 12;
          Mot_data[i][2] = (bigval & 0x0F00) >> 8;
          Mot_data[i][1] = (bigval & 0x00F0) >> 4;
          Mot_data[i][0] = (bigval & 0x000F);
          Mot_data[i][5] = 5;
          switch(x){
            case 0: Mot_cycle[i] = 2; break;
            case 1: Mot_cycle[i] = 3; break;
            case 2: Mot_cycle[i] = 4; break;
            case 3: Mot_cycle[i] = 5; break;
            case 4: Mot_cycle[i] = 6; break;
            }
          break;
          
          case 6:
          Mot_data[i][4] = y*10;
          x = random(0, 6);
          bigval = round((dels[x] - 747)/2.4445);
          Mot_data[i][3] = (bigval & 0xF000) >> 12;
          Mot_data[i][2] = (bigval & 0x0F00) >> 8;
          Mot_data[i][1] = (bigval & 0x00F0) >> 4;
          Mot_data[i][0] = (bigval & 0x000F);
          Mot_data[i][5] = 5;
          switch(x){
            case 0: Mot_cycle[i] = 2; break;
            case 1: Mot_cycle[i] = 3; break;
            case 2: Mot_cycle[i] = 4; break;
            case 3: Mot_cycle[i] = 5; break;
            case 4: Mot_cycle[i] = 6; break;
            case 5: Mot_cycle[i] = 7; break;
            }
          break;
          
          case 7:
          Mot_data[i][4] = y*10;
          x = random(0, 8);
          bigval = round((dels[x] - 440)/2.847);
          Mot_data[i][3] = (bigval & 0xF000) >> 12;
          Mot_data[i][2] = (bigval & 0x0F00) >> 8;
          Mot_data[i][1] = (bigval & 0x00F0) >> 4;
          Mot_data[i][0] = (bigval & 0x000F);
          Mot_data[i][5] = 5;
          switch(x){
            case 0: Mot_cycle[i] = 2; break;
            case 1: Mot_cycle[i] = 3; break;
            case 2: Mot_cycle[i] = 4; break;
            case 3: Mot_cycle[i] = 5; break;
            case 4: Mot_cycle[i] = 6; break;
            case 5: Mot_cycle[i] = 7; break;
            case 6: Mot_cycle[i] = 8; break;
            case 7: Mot_cycle[i] = 9; break;
            }
          break;
          
          case 8:
          Mot_data[i][4] = y*10;
          x = random(1, 9);
          bigval = round((dels[x] - 213.5)/3.2493);
          Mot_data[i][3] = (bigval & 0xF000) >> 12;
          Mot_data[i][2] = (bigval & 0x0F00) >> 8;
          Mot_data[i][1] = (bigval & 0x00F0) >> 4;
          Mot_data[i][0] = (bigval & 0x000F);
          Mot_data[i][5] = 5;
          switch(x){
            case 1: Mot_cycle[i] = 3; break;
            case 2: Mot_cycle[i] = 4; break;
            case 3: Mot_cycle[i] = 5; break;
            case 4: Mot_cycle[i] = 6; break;
            case 5: Mot_cycle[i] = 7; break;
            case 6: Mot_cycle[i] = 8; break;
            case 7: Mot_cycle[i] = 9; break;
            case 8: Mot_cycle[i] = 4; break;
            }
          break;
          
          case 9:
          Mot_data[i][4] = y*10;
          x = random(1, 9);
          bigval = round((dels[x] - 66.5)/3.6518);
          Mot_data[i][3] = (bigval & 0xF000) >> 12;
          Mot_data[i][2] = (bigval & 0x0F00) >> 8;
          Mot_data[i][1] = (bigval & 0x00F0) >> 4;
          Mot_data[i][0] = (bigval & 0x000F);
          Mot_data[i][5] = 5;
          switch(x){
            case 1: Mot_cycle[i] = 3; break;
            case 2: Mot_cycle[i] = 4; break;
            case 3: Mot_cycle[i] = 5; break;
            case 4: Mot_cycle[i] = 6; break;
            case 5: Mot_cycle[i] = 7; break;
            case 6: Mot_cycle[i] = 8; break;
            case 7: Mot_cycle[i] = 9; break;
            case 8: Mot_cycle[i] = 4; break;
            }
          break;
          }
    }
    }

void syncop(){
   for(int i = 1; i < nbMotor; i++){
    Mot_data[i][5] = 10 - Mot_cycle[i];
     for(int j = 0; j < 5; j++){
       Mot_data[i][j] = Mot_data[0][j];
       }
     }
   }

void send_data(byte data[], int slave){
  Wire.beginTransmission(slave); // transmit to device #slave
  Wire.write(data, 6);              // sends data 
  Wire.endTransmission();
  
  }

void slaveSetup(){
  for(int i = 0; i < nbMotor; i++){
    slave_id[i] = 9 + i;
    }
  }
