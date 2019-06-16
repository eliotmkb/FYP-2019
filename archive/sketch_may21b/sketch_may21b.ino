#include <Wire.h>

byte directionPin = 9;
byte stepPin = 8;
int numberOfSteps = 0; //ONLY WORKS WITH NBOFSTEPS > 1124
const int arrsz = 41;     //Number of steps it takes for ∂f/∂x to reach 1 
const int exp_inc = 10;   //what speed value is reached after arrsz steps 
byte ledPin = 13;
const int minspeed = 1000;
const int maxspeed = 300;
int zoom = 0;
int Sa[arrsz];  //Array starting at low speed
int Sb[arrsz];  //Array finishing at high speed

//tn determine the steps at which we switch between linear/exponential growth
int time_array[6];

//int t1 = arrsz;
//int t2 = arrsz + (minspeed-maxspeed) - 2*exp_inc;
//int t3 = t2 + arrsz;
//int t6 = numberOfSteps - arrsz;
//int t5 = t6 - (minspeed-maxspeed - 2*exp_inc) - 1;
//int t4 = t5 - arrsz;

void setup() 
{ 

  Serial.begin(9600);
  Serial.println("Starting Stepper");
  digitalWrite(ledPin, LOW);

  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  
//  Serial.println(t1);
//  Serial.println(t2);
//  Serial.println(t3);
//  Serial.println(t4);
//  Serial.println(t5);
//  Serial.println(t6);

  Serial.println("Creating arrays");
  //USING 500/1+exp(-0.1(x-80))
  for(int i = 0; i < arrsz; i++){
    Sa[i] = round(-500/(1+exp(-0.1*((i+1)-80))) + minspeed);
    Sb[i] = round(-500/(1+exp(-0.1*(160-(arrsz-i) - 80))) + (500+maxspeed));
    //Serial.println(Sb[i]);
    }

//  int i = 930;

  Serial.println("Start motor operation");
//  digitalWrite(directionPin, HIGH);
//  zoom = minspeed;
//  for (int i = 0; i < numberOfSteps; i++){
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(zoom + 4);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(zoom);
////    int time1 = micros(); //Use this to measure runtime of vroomvroom
//    zoom = vroomvroom(i);
////    int time2 = micros(); //and this
////    int interval = time2 - time1; //etc
////    Serial.println(interval);
//    //Serial.println(zoom);
//    }
//  delay(200);
//
//  digitalWrite(directionPin, LOW);
//  zoom = minspeed;
//  for (int i = 0; i < numberOfSteps; i++){
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(zoom + 4);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(zoom);
//    zoom = vroomvroom(i);
//  }
  
}

void loop() 
{ 
digitalWrite(directionPin, HIGH);
  zoom = minspeed;
  for (int i = 0; i < numberOfSteps; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(zoom + 4);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(zoom);
    zoom = vroomvroom(i, time_array);
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
  delayMicroseconds(4);
}

//Sets speed depending on step interval in which we are
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

void time_array_mod(int t[], int exp_inc, int maxspeed, int arrsz, int minspeed, int numberOfSteps){
  
  t[0] = arrsz;
  t[1] = arrsz + (minspeed-maxspeed) - 2*exp_inc;
  t[2] = t[1] + arrsz;
  t[5] = numberOfSteps - arrsz;
  t[4] = t[5] - (minspeed-maxspeed - 2*exp_inc) - 1;
  t[3] = t[4] - arrsz;
  }

 void receiveEvent(int bytes){
    int time1 = micros();
    numberOfSteps = Wire.read()*100;
    time_array_mod(time_array, exp_inc, maxspeed, arrsz, minspeed, numberOfSteps);
    int time2 = micros();
    int interval = time2 - time1;
    Serial.print("value change in ");
    Serial.println(interval);
  }
