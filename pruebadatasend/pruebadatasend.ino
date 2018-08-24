/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;
char a='a';
float buttonState=0.65;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(38400);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:

  // print out the state of the button:
  a='a';
  buttonState=0.65;
  Serial.print(a);
  Serial.print(buttonState);
 // delay(20);        // delay in between reads for stability
  a='b';
  buttonState=0.55;
  Serial.print(a);
  Serial.print(buttonState);
 // delay(20);  
  a='c';
  buttonState=0.45;
  Serial.print(a);
  Serial.print(buttonState);
  //delay(20);
  a='d';
  buttonState=0.35;
  Serial.print(a);
  Serial.print(buttonState);
  //delay(20);
  a='e';
  buttonState=0.25;
  Serial.print(a);
  Serial.print(buttonState);
 // delay(20);
  a='f';
  buttonState=0.55;
  Serial.print(a);
  Serial.print(buttonState);
  delay(50);
}



