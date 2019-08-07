#include <Wire.h>
byte ledPin = 13;

//Important for communicating with the motor controller
byte directionPin = 9;
byte stepPin = 8;

int numberOfSteps = 0; //ONLY WORKS WITH NBOFSTEPS > 1124
int iterations;        //Number of iterations before motor changes motion profile

//The following 2 variables have to be recalculated if a different Logistic function is used
const int arrsz = 41;     //Number of steps in the exponential stages (at the end of those stages, the speed variation has a gradient of 1)
const int exp_inc = 10;   //After the 41 steps of exponential variation, the speed will have changed by this much 

//Minspeed is the same always but maxspeed gets overwritten with the data coming from master
const int minspeed = 1000;
int maxspeed = 300;

//mods changes when new data is received
bool mods = false;

//zoom is actually speed, sorry speed cant be used and I thought calling it zoom was funny
int zoom = 0;

int Sa[arrsz];  //Array starting at low speed
int Sb[arrsz];  //Array finishing at high speed

//time_array determines the steps at which we switch between linear/exponential growth
int time_array[6] = {0, 0, 0, 0, 0, 0};

  
void setup() 
{ 
  //Just some set ups
  Serial.begin(9600);
  Serial.println("Starting Stepper");
  digitalWrite(ledPin, LOW);

  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  //Wire.begin sets the slave address and .onReceive says what function to call when data is recieved form master
  Wire.begin(9);
  Wire.onReceive(receiveEvent);

  //Creating the intial exponential variation arrays (contains the exact speed (zoom) values for all the 41 steps)
  Serial.println("Creating arrays");
  //USING 500/1+exp(-0.1(x-80))
  for(int i = 0; i < arrsz; i++){
    Sa[i] = round(-500/(1+exp(-0.1*((i+1)-80))) + minspeed);
    Sb[i] = round(-500/(1+exp(-0.1*(160-(arrsz-i) - 80))) + (500+maxspeed));
    //Serial.println(Sb[i]);
    }

//  int i = 930;

  Serial.println("Start motor operation");
}

void loop() 
{ 
  //Only move the motors when new data is recieved from the master, check using mods
  if (mods){
    amp_change();
    mods =  false;

    //Loop for specefied number of iterations
    for(int i = 0; i < iterations; i++){
      digitalWrite(directionPin, HIGH);             //CW or CCW
      zoom = minspeed;                              //Always start at minspeed (for smoothness)
      
      //Typical motor controlling for loop
      for (int i = 0; i < numberOfSteps; i++){

        //Create pulse by alternating LOW and HIGH with a delay of zoom
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(zoom + 4);                //the +4 relates to the length of the vroomvroom function called after the LOW pulse
        digitalWrite(stepPin, LOW);
        delayMicroseconds(zoom);
        zoom = vroomvroom(i, time_array);           //Allocate new speed value
        //Serial.println(zoom);
        }
      delayMicroseconds(4);
    
      digitalWrite(directionPin, LOW);
      zoom = minspeed;
      for (int i = 0; i < numberOfSteps; i++){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(zoom + 4);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(zoom);
        zoom = vroomvroom(i, time_array);
      }
      }
    }
  //delayMicroseconds(4);
}

//Sets speed depending on step interval in which we are (sorry again for the name)
int vroomvroom(int i, int t[]){
  if (i < t[0]){    //1st exponential (slow) increase from minspeed
      zoom = Sa[i];
      }
    else if(i >= t[0] && i < t[1]){   //linear increase y=x
      zoom = (minspeed-10) - (i-t[0]);
      }
    else if(i >= t[1] && i < t[2]){   //2nd exp increase until maxspeed
      zoom = Sb[i-t[1]];  
      }
    else if(i >= t[2] && i < t[3]){   //continue at maxspeed until motor needs to slow down
      zoom = maxspeed;
      }
    else if(i > t[3] && i < t[4]){    //1st exponential decay from maxspeed
      zoom = Sb[(arrsz-1)-(i-t[3])];
      }
    else if(i >= t[4] && i < t[5]){   //linear decrease
      zoom = (maxspeed+10) + (i-t[4]);  
      }
    else if(i >= t[5]){   //2nd exponential decay until minspeed
      zoom = Sa[(arrsz-1)-(i-t[5])];
      }
      return zoom;
  }

//This function edits the time_array depending on the new incoming value of numberOfSteps
void time_array_mod(int t[], int exp_inc, int maxspeed, int arrsz, int minspeed, int numberOfSteps){
  t[0] = arrsz;
  t[1] = arrsz + (minspeed-maxspeed) - 2*exp_inc;
  t[2] = time_array[1] + arrsz;
  t[5] = numberOfSteps - arrsz;
  t[4] = t[5] - (minspeed-maxspeed - 2*exp_inc) - 1;
  t[3] = t[4] - arrsz;
  }

//This function edits the second exponential array depending on the new incoming value of maxspeed
//The first array never changes since it only depends on minspeed
 void exp_array_mod(int arrsz, int maxspeed, int Sb[]){
  for(int i = 0; i < arrsz; i++){
    Sb[i] = round(-500/(1+exp(-0.1*(160-(arrsz-i) - 80))) + (500+maxspeed));
    }
  }

//This function reads the new values of numberOfSteps, maxspeed, and iterations from the master
 void amp_change(){
    Serial.println("config changes");
    numberOfSteps = Wire.read();
    numberOfSteps += Wire.read() << 4;
    numberOfSteps += Wire.read() << 8;
    numberOfSteps += Wire.read() << 12;
    maxspeed = Wire.read()*10;
    iterations = Wire.read();
    time_array_mod(time_array, exp_inc, maxspeed, arrsz, minspeed, numberOfSteps);
    exp_array_mod(arrsz, maxspeed, Sb);
  }

 //Wire.onReceive interrupt
 void receiveEvent(int bytes){
    mods = true;
    }
