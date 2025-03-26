/*
This code is just for Servo Motor
*/

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Define pins needed
#define SERVOMIN 140  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 520  // this is the 'maximum' pulse length count (out of 4096)

// Both Servo motors to move arm up & down
Servo Serv1;               // Servo 1 in facing front
Servo Serv2;               // Servo 2 is facing back
int posSer1, posSer2 = 0;           // Set both Servo motor position to 0
int armHeight = 0;

// Servo control variables
uint8_t servonum = 0;
int xval, yval;
int xSum = 512, ySum = 512;
int lexpulse, rexpulse;
int leypulse, reypulse;
int lUpLid, lLoLid, rUpLid, rLoLid;
int trimval;

int sensorValue = 0;
int outputValue = 0;
int switchval = 0;      // Switch for blinking eyes


// Runs once
void setup() {
  Serial.begin(9600);
  Serial.println("Eye control with Ultrasonic Sensor!");

  // All pins set as output
  // Serv1.attach(6);  // Servo 1 set to pin 6
  // Serv2.attach(7);  // Servo 2 set to pin 7
  pinMode(5, INPUT);   // For Arduino, not Servo Shield
  PinMode(6, INPUT);

  pinMode(4, OUTPUT);   // On Arduino


  // PWM initialization
  pwm.begin();
  pwm.setPWMFreq(60);  // Set frequency to 60 Hz for servos
  delay(10);
}





              // Start Here




void loop() {
  delay(10);

  // // Eye Control Code Start
  // // Eye movement control
  // if (digitalRead(8) == HIGH && xSum < 1024) xSum += 20;
  // if (digitalRead(9) == HIGH && xSum > 0) xSum -= 20;
  // if (digitalRead(10) == HIGH && ySum < 700) ySum += 20;
  // if (digitalRead(11) == HIGH && ySum > 0) ySum -= 20;

  // xval = xSum;
  // yval = ySum;

  // // Map servo pulses
  // lexpulse = map(xval, 0, 1023, 280, 380);
  // leypulse = map(yval, 0, 1023, 380, 500);
  // trimval = map(512, 320, 580, -40, 40);

  // // Lid movement
  // lUpLid = map(512, 0, 1023, 400, 280) - (trimval - 40);
  // lUpLid = constrain(lUpLid, 280, 400);
  // rUpLid = 680 - lUpLid;
  // lLoLid = map(512, 0, 1023, 410, 280) + (trimval / 2);
  // lLoLid = constrain(lLoLid, 280, 400);
  // rLoLid = 680 - lLoLid;

  // Set servo positions for eyes
  pwm.setPWM(0, 0, lexpulse);
  pwm.setPWM(1, 0, leypulse);

  // // Check for motion detection from ultrasonic sensor
  // if (detectMotion()) {
  //   Serial.println("Motion detected! Blinking...");
  //   blinkEyes();  // Blink the eyes when motion is detected
  // } else {
  //   moveLids(lUpLid, lLoLid, rUpLid, rLoLid);  // Move eyelids normally if no motion
  // }
  // delay(5);
  // // Eye Control Code End

  // Loop to move both Servo motors to lift arm up and down
  armHeight = 75;  // Variable for how far up the arm will go to wave

  for (posSer1 = 0; posSer1 <= armHeight; posSer1 += 1) {  // Moves arm 50 degrees
    posSer2 = posSer2 - 1;                                 // While position 1 increases by 1, we want position 2 to decrease by 1
                                                           // This is to make sure that both servers work like a mirror turning in the same direction
    Serv1.write(posSer1);                                  // Servo 1 goes to position in value posSer1
    Serv2.write(posSer2);                                  // Servo 2 works opposite of Servo 1 like a mirror
    delay(15);                                             // 15ms delay
  }

  for (int i = 0; i < 2; i++) {  // Quick loop to move arm back and forth
    for (posSer1 = armHeight; posSer1 >= 10; posSer1 -= 1) {
      posSer2 = posSer2 + 1;
      Serv1.write(posSer1);
      Serv2.write(posSer2);
      delay(15);
    }
    for (posSer1 = 10; posSer1 >= armHeight; posSer1 += 1) {
      posSer2 = posSer2 - 1;
      Serv1.write(posSer1);
      Serv2.write(posSer2);
      delay(15);
    }
  }

  for (posSer1 = armHeight; posSer1 >= 0; posSer1 -= 1) {  // Moves arm back down
    posSer2 = posSer2 + 1;
    Serv1.write(posSer1);
    Serv2.write(posSer2);
    delay(15);
  }
}

// // Function to blink eyes
// void blinkEyes() {
//   pwm.setPWM(2, 0, 605);  // Left upper eyelid
//   pwm.setPWM(3, 0, 135);  // Left lower eyelid
//   pwm.setPWM(4, 0, 135);  // Right upper eyelid
//   pwm.setPWM(5, 0, 605);  // Right lower eyelid
//   delay(500);             // Hold blink for half a second
// }

// // Function to move eyelids based on sensor inputs
// void moveLids(int lUpLid, int lLoLid, int rUpLid, int rLoLid) {
//   pwm.setPWM(2, 0, lUpLid);
//   pwm.setPWM(3, 0, lLoLid);
//   pwm.setPWM(4, 0, rUpLid);
//   pwm.setPWM(5, 0, rLoLid);
// }

// // Function to detect motion using ultrasonic sensor
// bool detectMotion() {
//   // Clear the trigger pin
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);

//   // Send a 10-microsecond pulse to trigger the sensor
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);

//   // Measure the time taken for the echo to return
//   long duration = pulseIn(echoPin, HIGH);

//   // Calculate the distance (in cm)
//   int distance = duration * 0.034 / 2;  // Speed of sound is 34,000 cm/s

//   Serial.print("Distance: ");
//   Serial.println(distance);

//   // If someone is within 50 cm and 1 meter, return true
//   if (distance > 25 && distance < 1000) {
//     return true;
//   } else {
//     return false;
//   }
// }
