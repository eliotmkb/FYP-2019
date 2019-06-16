
byte directionPin = 9;
byte stepPin = 8;
byte ledPin = 13;
int mspeed1 = 100;
int mspeed2 = 105;

void setup() 
{ 

  Serial.begin(9600);
  Serial.println("Starting StepperTest");
  digitalWrite(ledPin, LOW);

  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
}

void loop() 
{ 
  for(int i = 0; i < 10000; i++){
    digitalWrite(directionPin, HIGH);
    
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(mspeed1);
    digitalWrite(stepPin, LOW);  
    delayMicroseconds(mspeed1);
  }
  for(int i = 0; i < 10000; i++){
    digitalWrite(directionPin, HIGH);
    
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(mspeed2);
    digitalWrite(stepPin, LOW);  
    delayMicroseconds(mspeed2);
  }
}
