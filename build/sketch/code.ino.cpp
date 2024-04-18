#include <Arduino.h>
#line 1 "/Users/jellyfish/Documents/CUHK/Year_2/Spring/CENG2030_Fundamentals_of_Embedded_Systems/code/code.ino"
#include <Servo.h>

//declaration of pins
const int ECHO = 12;   // select the input pin for the ultrasonic echo pin
const int TRIG = 13;   // select the input pin for the ultrasonic trig pin
const int LPR = A0;
const int RPR = A1;
const int TPR = A2;
const int BPR = A3;


long duration, cm;

int signal = 0;

#line 16 "/Users/jellyfish/Documents/CUHK/Year_2/Spring/CENG2030_Fundamentals_of_Embedded_Systems/code/code.ino"
void setup();
#line 23 "/Users/jellyfish/Documents/CUHK/Year_2/Spring/CENG2030_Fundamentals_of_Embedded_Systems/code/code.ino"
void loop();
#line 16 "/Users/jellyfish/Documents/CUHK/Year_2/Spring/CENG2030_Fundamentals_of_Embedded_Systems/code/code.ino"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
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

  delay(250);
}

