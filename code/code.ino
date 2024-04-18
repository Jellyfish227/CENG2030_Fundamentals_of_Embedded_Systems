const int sensorPin = A0;   // select the input pin for the potentiometer
const int ledPin = 13;      // select the pin for the LED
const int THRESHOLD = 800;

bool pulseCounted = false;
int pulseCount = 0;
int rawPulseVal = 0;
int pulseRate = 0;
int sensorValue = 0;
long int time;  // variable to store the value coming from the sensor

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  time = millis();
  sensorValue = analogRead(sensorPin);
  
  if (sensorValue >= 700){
    digitalWrite(ledPin, HIGH);
    if(!pulseCounted){
      pulseCount++;
      pulseCounted = true;
    }
    
  } else {
    digitalWrite(ledPin, LOW);
    pulseCounted = false;
  }

  pulseRate = pulseCount * 60000/time;

  Serial.print("SignalLevel:");
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.print("PulseRate:");
  Serial.println(pulseRate);
  delay(20);
  
}
