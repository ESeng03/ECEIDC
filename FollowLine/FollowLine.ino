#include <Servo.h>

#define Rx 17
#define Tx 16
#define lineSensor1 47 
#define lineSensor2 49
#define lineSensor4 53
#define lineSensor5 52
char outgoing = 'A'; //Char to be sent

Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(11);
  servoRight.attach(12);
  
  pinMode(6, INPUT); //Button
  pinMode(10, OUTPUT); //Green LED
  pinMode(8, OUTPUT); // Red LED

  digitalWrite(8,LOW); //Set inital LED states to off
  digitalWrite(10,LOW);
  
  Serial.begin(9600); //Open the arduino's serial montitor
  Serial2.begin(9600); //Open the XBee serial monitor
  
  delay(500);
}

void loop(){

  int qti1 = RCTime(lineSensor1);     //Calls funtion 'RCTime' Request reading from QTI sensor at pin 'linesensor1' saves value in variable 'qti'
  int qti2 = RCTime(lineSensor2);     //Calls funtion 'RCTime' Request reading from QTI sensor at pin 'linesensor1' saves value in variable 'qti'
  int qti4 = RCTime(lineSensor4);     //Calls funtion 'RCTime' Request reading from QTI sensor at pin 'linesensor1' saves value in variable 'qti'
  int qti5 = RCTime(lineSensor5);     //Calls funtion 'RCTime' Request reading from QTI sensor at pin 'linesensor1' saves value in variable 'qti'
  Serial.println(" ");
  Serial.println(qti1);  
  Serial.println(qti2); 
  Serial.println(qti4); 
  Serial.println(qti5); 

  if(qti2 > 100 || qti4 > 100){
    servoLeft.write(-10);
    servoRight.write(10);
    delay(1000);
  }else if(qti1 > 50){
    servoLeft.write(-10);
    servoRight.write(-10);
    delay(1000);

  }else if(qti5 > 50){
    servoLeft.write(10);
    servoRight.write(10);
    delay(1000);
  }

  /*
  //Send Message
  if(digitalRead(6) == HIGH){ //If button is pressed
    Serial2.print(outgoing); //Send char to the XBee
    digitalWrite(8, HIGH); //Turn Red LED on
    delay(100);
  } else {
    digitalWrite(8, LOW); //If not pressed turn the LED off
  }

  //Recieve Message
  if(Serial2.available()){ //If the XBee Receives a message
    char incoming = Serial2.read(); //Write the char to incoming
    Serial.println(incoming); //Print the char on the Arduino's serial
    digitalWrite(10, HIGH); //Turn the Green LED on
    delay(200); 
  } else {
    digitalWrite(10, LOW); //If not receiving a signal keep LED off
  }
  
  delay(50);*/
}

long RCTime(int sensorIn)
{
  
  long duration = 0;
  pinMode(sensorIn, OUTPUT); // Sets pin as OUTPUT
  digitalWrite(sensorIn, HIGH); // Pin HIGH
  delay(1); // Waits for 1 millisecond
  pinMode(sensorIn, INPUT); // Sets pin as INPUT
  digitalWrite(sensorIn, LOW); // Pin LOW

  while(digitalRead(sensorIn)) { // Waits for the pin to go LOW
    duration++;

  }
return duration; // Returns the duration of the pulse
}
