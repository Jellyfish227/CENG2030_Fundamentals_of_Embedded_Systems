# 1 "/Users/jellyfish/Documents/CUHK/Year_2/Spring/CENG2030_Fundamentals_of_Embedded_Systems/code/code.ino"
# 2 "/Users/jellyfish/Documents/CUHK/Year_2/Spring/CENG2030_Fundamentals_of_Embedded_Systems/code/code.ino" 2

//instanciate servo
Servo xyPlaneServo;
Servo yzPlaneServo;

//declaration of pins
const int ECHO = 12; // select the input pin for the ultrasonic echo pin
const int TRIG = 13; // select the input pin for the ultrasonic trig pin
const int LIR = A0;
const int RIR = A1;
const int TIR = A2;
const int BIR = A3;
const int YZSERVO = 11;
const int XYSERVO = 10;
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
  pinMode(ECHO, 0x0);
  pinMode(TRIG, 0x1);
  xyPlaneServo.write(0);
  yzPlaneServo.write(0);
}

void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG, 0x0);
  delayMicroseconds(5);
  digitalWrite(TRIG, 0x1);
  delayMicroseconds(10);
  digitalWrite(TRIG, 0x0);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ECHO, 0x0);
  duration = pulseIn(ECHO, 0x1);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1; // Divide by 29.1 or multiply by 0.0343

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

  if (cm > 340)
  {
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
    else if (topLevel > bottomLevel + DEADBAND)
    {
      posYZ++;
      if (posYZ > 180)
        posYZ = 180;
    }
    yzPlaneServo.write(posYZ);
  }

  delay(250);
}
