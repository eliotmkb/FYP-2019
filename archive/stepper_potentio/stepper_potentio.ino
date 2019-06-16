
byte directionPin = 9;
byte stepPin = 8;
byte ledPin = 13;
int sensorPin = A3;
int sensorValue = 0;
int count = 0;

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
  digitalWrite(directionPin, HIGH);

  if (count == 10000){
    Serial.println(sensorValue);
    count = 0;
    }

  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0, 1023, 1000,50);
  
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(sensorValue);
  digitalWrite(stepPin, LOW);
    
  delayMicroseconds(sensorValue);
  count = count + 1;
}
