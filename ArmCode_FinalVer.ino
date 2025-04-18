/*
Greeting Rams - Arm Code - Condensed Version
          This code is for controlling Servo Motors using Arduino
          Code has been condensed to look a little neater than before
Author: Jose Mojica-Ramos
Edited: April 18, 2025
*/

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Initialize PWM driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Define servo parameters
#define SERVOMIN 140  // Minimum pulse length count (out of 4096)
#define SERVOMAX 520  // Maximum pulse length count (out of 4096)

// Servo definitions
Servo Serv1;  // Front-facing Servo
Servo Serv2;  // Back-facing Servo

// Global variables for servo movement
int armHeight = 75;            // Maximum arm height for waving
int posSer1, posSer2 = 0;      // Initial positions for Servos

void setup() {
  Serial.begin(9600);

  // Attach servos to PWM pins or standard pins
  Serv1.attach(6);  // Pin for Servo 1
  Serv2.attach(7);  // Pin for Servo 2

  // Initialize PWM driver
  pwm.begin();
  pwm.setPWMFreq(60);  // Set frequency to 60 Hz for servos
  delay(10);
}

void loop() {
  delay(10);  // Short delay before starting movement

  liftArm();   // Lift arm to waving position
  waveArm(2);  // Perform waving motion twice
  lowerArm();  // Lower arm back to resting position
}

// Function to lift the arm
void liftArm() {                                          // Moves arms 50 degrees
  for (posSer1 = 0; posSer1 <= armHeight; posSer1++) {
    posSer2--;                                            // Mirror movement for Servo 2 in opposite direction
    moveServos(posSer1, posSer2);
  }
}

// Function to wave the arm
void waveArm(int reps) {
  for (int i = 0; i < reps; i++) {
    // Move arm down
    for (posSer1 = armHeight; posSer1 >= 10; posSer1--) {
      posSer2++;
      moveServos(posSer1, posSer2);
    }
    // Move arm up
    for (posSer1 = 10; posSer1 <= armHeight; posSer1++) {     // Might be posSer1 >= armHeight
      posSer2--;
      moveServos(posSer1, posSer2);
    }
  }
}

// Function to lower the arm
void lowerArm() {
  for (posSer1 = armHeight; posSer1 >= 0; posSer1--) {
    posSer2++;
    moveServos(posSer1, posSer2);
  }
}

// Function to move both servos
void moveServos(int pos1, int pos2) {
  Serv1.write(pos1);  // Set Servo 1 to position
  Serv2.write(pos2);  // Set Servo 2 to position
  delay(15);          // Delay for smooth movement
}
