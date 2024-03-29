#include <Wire.h>
int x = 0;
int y = 0;

//Array with percentage delay values dels[3] = 16000 = 100%
const unsigned int dels[9] = {6400, 9600, 12800, 16000, 19200, 22400, 25600, 28800, 32000};

//send this to the motors to stop them
byte stop_data[6] = {0, 0, 0, 0, 0, 0};

//Large variable that contains data that will get seperated between Mot_data[i][0 to 3]
unsigned int bigval;

//Maximum number of motors that work with this code (if more are required use full_scale_master.ino and change nbMotor variable)
const int max_size = 10;

//Trivial variables
int Serial_data;
const int ledPin = 13;
int nbMotor = 0;

//Array containing all the slave id's
int slave_id[max_size]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//Array containing motion profile data of each motor
byte Mot_data[max_size][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};

//Number of iterations done by reference when motor n will have synced up with it, lets call it sync timing
int Mot_cycle[max_size] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// Structure of Mot_data[i][j]:
//i is the motor number, 0 being reference
//j is each data type: 0 to 3 are the nbOfSteps, 4 is maxspeed, 5 is iterations


void setup() {
  // Start the I2C Bus as Master
  //Nothing really important here
  Wire.begin();

  Serial.begin(9600);
  
  digitalWrite(ledPin, HIGH);

}
void loop() {
  //I didn't put anything in loop because the current code is only performing the choreography once
}

//This is an interrupt that gets called when data arrives from Matlab, it contains virtually all the code
void serialEvent() {
  //Read data coming from Matlab
  nbMotor = Serial.read();

  //see function descriptions
  slaveSetup();
  randop();

    //Send data over to the motors sequentially
    for(int i = 0; i < nbMotor; i++){
      send_data(Mot_data[i], slave_id[i]);
      }
  
    delay(5000);
    syncop();
    for(int i = 1; i < nbMotor; i++){
      send_data(Mot_data[i], slave_id[i]);
      }
  }

//This function assigns a different random motion profile to every motor except motor 0 that always gets the same refernce profile
void randop(){
    //If this isnt called the random sequence outputed by "rand()" is always the same, so the motion profiles are always the same
    randomSeed(analogRead(A0));

    //Assign the reference motion profile to motor 0 (iteration delay = 16000ms, maxspeed = 600 and iterations = 10) could be assigned to different motor
    bigval = round((dels[3] - 747.0)/2.4445);
    Mot_data[0][3] = (bigval & 0xF000) >> 12;
    Mot_data[0][2] = (bigval & 0x0F00) >> 8;
    Mot_data[0][1] = (bigval & 0x00F0) >> 4;
    Mot_data[0][0] = (bigval & 0x000F);
    Mot_data[0][4] = 60;
    Mot_data[0][5] = 10;
    
    //Assign a different random motion profile to every other motor
    for(int i = 1; i < nbMotor; i++){
      
      //First randomly allocate maxspeed between 300 and 900
      y = random(3, 10);
          switch(y){
          case 3:
          Mot_data[i][4] = y*10;
          
          //Then randomly allocate iteration delay value
          //Note that interval varies because for example, a maxspeed of 300 cant generate a delay greater than 12800 and a maxspeed of 900 cant generate a delay lower than 9600
          x = random(0, 3);
          
          //Use that delay to determine the sync timing and fill up Mot_data[i][j]
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
          
          //Just a repition of previous code with different maxspeed values
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
          bigval = round((dels[x] - 747.0)/2.4445);
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
          bigval = round((dels[x] - 440.0)/2.847);
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

//This function assigns the same motion profile to every motor once they've synced up (after 5 cycles)
void syncop(){
   for(int i = 1; i < nbMotor; i++){
    
    //The sync timing is used here to determine for how long each motor will have to move in sync with reference before motor 0 will complete 10 iterations
    Mot_data[i][5] = 10 - Mot_cycle[i];
     for(int j = 0; j < 5; j++){
       Mot_data[i][j] = Mot_data[0][j];
       }
     }
   }

//This function sends data over to the motors using their slave address 
void send_data(byte data[], int slave){
  Wire.beginTransmission(slave); // transmit to device #slave
  Wire.write(data, 6);              // sends data 
  Wire.endTransmission();
  
  }

//This function sets up the slave addresses depending on the number of connected motors
void slaveSetup(){
  for(int i = 0; i < nbMotor; i++){
    slave_id[i] = 9 + i;
    }
  }
