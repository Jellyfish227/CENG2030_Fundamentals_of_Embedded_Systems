#include <Servo.h>
Servo myservo;

const int IRLEFT = A4;
const int IRRIGHT = A5;
const int SERVOPIN = 11;
const int DEADBAND = 20;

int pos = 0;
int leftLevel = 0;
int rightLevel = 0;
bool isTurnRight = false;
bool isTurnLeft = false;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(SERVOPIN);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  leftLevel = analogRead(IRLEFT);
  Serial.print("Left:");
  Serial.println(leftLevel);
  rightLevel = analogRead(IRRIGHT);
  Serial.print("Right:");
  Serial.println(rightLevel);

  if (leftLevel > rightLevel) {
    if (leftLevel - rightLevel > DEADBAND){
      pos--;
      if (pos < 0) 
        pos = 0;
      myservo.write(pos);
    }
  } else if (rightLevel > leftLevel) {
    if (rightLevel - leftLevel > DEADBAND){
      pos++;
      if (pos > 180)
        pos = 180;
      myservo.write(pos);
    }
  }
  delay(10);
}
