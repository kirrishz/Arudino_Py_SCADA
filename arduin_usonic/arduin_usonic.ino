#include <Servo.h>
Servo myservo; 
int val = 0;              // variable to store the sensor value
String pval = "*";        // string variable to send sensor value over COM port
int TRIG_PIN   = A1; // Arduino pin connected to Ultrasonic Sensor's TRIG pin
int ECHO_PIN   = A2; // Arduino pin connected to Ultrasonic Sensor's ECHO pin
int BUZZER_PIN = 5; // Arduino pin connected to Piezo Buzzer's pin
int DISTANCE_THRESHOLD = 30; // centimeters

// variables will change:
float duration_us, distance_cm;

void setup() {
  Serial.begin(9600);     // setup serial communication
  myservo.attach(3);      // attach motor to PWM pin 3
  myservo.write(90);      // rotating motor to initial position
  pinMode(TRIG_PIN, OUTPUT);   // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);    // set arduino pin to input mode
  pinMode(BUZZER_PIN, OUTPUT); // set arduino pin to output mode
  
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

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

    
  for(int i=0;i<=180;i=i+2){
    myservo.write(i);                                 // rotating motor CW
    val = 100095*(pow(analogRead(TRIG_PIN),-0.966)); // sensor calibration equation
    if ((val>1500) || (val<0)){                       // disregarding erroneous readings
      val = NULL;
    }
    Serial.println(i + pval + val);                   // sending motor position and sensor reading over COM port
    delay(50);
  }
  for(int i=180;i>=0;i=i-2){
    myservo.write(i);                                 // rotating motor CCW
    val = 100095*(pow(analogRead(TRIG_PIN),-0.966)); // sensor calibration equation
    if ((val>1500) || (val<0)){                       // disregarding erroneous readings
      val = NULL;
    }
    Serial.println(i + pval + val);                   // sending motor position and sensor reading over COM port
    delay(50);
  }
  
}
