byte directionPin = 9;
byte stepPin = 8;
int numberOfSteps = 10000; //ONLY WORKS WITH NBOFSTEPS > 1800
byte ledPin = 13;
int minspeed = 1000;
int maxspeed = 100;
int zoom = 0;

int t1 = 900;
int t2 = numberOfSteps-900;

void setup() 
{ 

  Serial.begin(9600);
  Serial.println("Starting StepperTest");
  digitalWrite(ledPin, LOW);

  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  Serial.print("t1 is ");
  Serial.println(t1);
  Serial.print("t2 is ");
  Serial.println(t2);

//  int i = 1000;

  digitalWrite(directionPin, HIGH);
  zoom = minspeed;
  for (int i = 0; i < numberOfSteps; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(zoom);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(zoom);
//    int time1 = micros();
    zoom = vroomvroom(i);
//    int time2 = micros();
//    int interval = time2 - time1;
//    Serial.println(interval);
    }

  delay(200);

  digitalWrite(directionPin, LOW);
  zoom = minspeed;
  for (int i = 0; i < numberOfSteps; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(zoom);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(zoom);
    zoom = vroomvroom(i);
  }

  delay(2000);
  
}

void loop() 
{ 
//  digitalWrite(directionPin, HIGH);
//  zoom = minspeed;
//  for (int i = 0; i < numberOfSteps; i++){
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(zoom);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(zoom);
//    if (i < t1){
//      zoom = round(minspeed - (i*delta));
//      }
//    else if(i > t2){
//      zoom = round(maxspeed + (i*delta));
//      }
//    else{
//      zoom = maxspeed;  
//      }
//    }
//
//  delay(200);
//
//  digitalWrite(directionPin, LOW);
//  zoom = minspeed;
//  for (int i = 0; i < numberOfSteps; i++){
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(zoom);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(zoom);
//    if (i < t1){
//      zoom = round(minspeed - (i*delta));
//      }
//    else if(i > t2){
//      zoom = round(maxspeed + (i*delta));
//      }
//    else{
//      zoom = maxspeed;  
//      }
//  }
//
//  delay(2000);
}

int vroomvroom(int i){
  if (i < t1){
      zoom = minspeed - i;
      }
    else if(i > t2){
      zoom = maxspeed + (i-t2);
      }
    else{
      zoom = maxspeed;  
      }
      return zoom;
  }
