#include <Servo.h>

//instanciate servo
Servo xyPlaneServo;
Servo yzPlaneServo;

//declaration of pins
const int ECHO = 12;   // select the input pin for the ultrasonic echo pin
const int TRIG = 13;   // select the input pin for the ultrasonic trig pin
const int LPR = A0;
const int RPR = A1;
const int TPR = A2;
const int BPR = A3;
const int YZSERVO = 11;
const int XYSERVO = 10;
const int LED = 9;
const int DEADBAND = 20;

//declaration of 
long duration, cm;
int posXY = 0;
int posYZ = 0;
int leftLevel, rightLevel, topLevel, bottomLevel;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xyPlaneServo.attach(XYSERVO);
  yzPlaneServo.attach(YZSERVO);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(LED, OUTPUT);
  xyPlaneServo.write(0);
  yzPlaneServo.write(0);
}

void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ECHO, INPUT);
  duration = pulseIn(ECHO, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343

  Serial.print(cm);
  Serial.println("cm");

  //light signal input
  leftLevel = analogRead(LPR);
  rightLevel = analogRead(RPR);
  topLevel = analogRead(TPR);
  bottomLevel = analogRead(BPR);
  Serial.print("Left:");
  Serial.println(leftLevel);
  Serial.print("Right:");
  Serial.println(rightLevel);
  Serial.print("Top:");
  Serial.println(topLevel);
  Serial.print("Bottom:");
  Serial.println(bottomLevel);

  if (cm > 30)
  {
    digitalWrite(LED, LOW);
    if (leftLevel > rightLevel + DEADBAND)
    {
      posXY--;
      if (posXY < 0)
        posXY = 0;
    }
    else if (rightLevel > leftLevel + DEADBAND)
    {
      posXY++;
      if (posXY > 180)
        posXY = 180;
    }
    xyPlaneServo.write(posXY);
    

    if (topLevel > bottomLevel + DEADBAND)
    {
      posYZ--;
      if (posYZ < 0)
        posYZ = 0;
    }
    else if (bottomLevel > topLevel + DEADBAND)
    {
      posYZ++;
      if (posYZ > 180)
        posYZ = 180;
    }
    yzPlaneServo.write(posYZ);
  } else {
    digitalWrite(LED, HIGH);
  }

  delay(50);
}
