#include <Servo.h>
Servo myservo; 
int val = 0;              // variable to store the sensor value
const int TRIG_PIN = 6;       // sensor pin
String pval = "*";        // string variable to send sensor value over COM port
const int BUZZER_PIN = 5;
const int ECHO_PIN=7;
const int DISTANCE_THRESHOLD = 50; // centimeters

// variables will change:
float duration_us, distance_cm;

void setup() {
  
  Serial.begin(9600);     // setup serial communication
  myservo.attach(3);      // attach motor to PWM pin 3
  myservo.write(90);      // rotating motor to initial position
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
}

void loop() {

  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

  if(distance_cm < DISTANCE_THRESHOLD)
    digitalWrite(BUZZER_PIN, HIGH); // turn on Piezo Buzzer
  else
    digitalWrite(BUZZER_PIN, LOW);  // turn off Piezo Buzzer
  
  for(int i=0;i<=180;i=i+2){
    myservo.write(i);                                 // rotating motor CW
    val = distance_cm; // sensor calibration equation
    
    
    Serial.println(i + pval + val);                   // sending motor position and sensor reading over COM port
    delay(50);
  }
  for(int i=180;i>=0;i=i-2){
    myservo.write(i);                                 // rotating motor CCW
    val = distance_cm; // sensor calibration equation
    
    Serial.println(i + pval + val);                   // sending motor position and sensor reading over COM port
    delay(50);
  }
  
}
