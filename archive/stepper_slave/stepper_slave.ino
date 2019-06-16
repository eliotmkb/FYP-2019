#include <Wire.h>
int LED = 13;
int x[3];
void setup() {
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Serial.begin(9600);
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes) {
  for(int i = 0; i < 3; i++)  x[i] = Wire.read()*100;    // read one character from the I2C
}
void loop() {
  //If value received is 0 blink LED for 200 ms
  Serial.println(x[0]);
  Serial.println(x[1]);
  Serial.println(x[2]);

  delay(2000);
}
