#include <Servo.h>

//instanciate servo
Servo xyPlaneServo;
Servo yzPlaneServo;

/*
 * For demo, use IR sensor for better effect, use photoresistor in actual case
 */
// declaration of pins
const int ECHO = 12;   // select the input pin for the ultrasonic echo pin
const int TRIG = 13;   // select the input pin for the ultrasonic trig pin
const int LIR = A0;    // Left IR
const int RIR = A1;    // Right IR
const int TIR = A2;    // Top IR
const int BIR = A3;    // Bottom IR
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
  leftLevel = analogRead(LIR);
  rightLevel = analogRead(RIR);
  topLevel = analogRead(TIR);
  bottomLevel = analogRead(BIR);
  Serial.print("Left:");
  Serial.println(leftLevel);
  Serial.print("Right:");
  Serial.println(rightLevel);
  Serial.print("Top:");
  Serial.println(topLevel);
  Serial.print("Bottom:");
  Serial.println(bottomLevel);

  // 30cm is for demo use, it should be actual length in deployment
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
