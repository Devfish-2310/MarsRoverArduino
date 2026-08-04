#include <Servo.h>

Servo servo6;
Servo servo7;

// Right Motor Control Pins
const int rightMotorForward = 11;
const int rightMotorBackward = 10;

// Left Motor Control Pins
const int leftMotorForward = 9;
const int leftMotorBackward = 8;

void setup() {
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);

  servo6.attach(6);
  servo7.attach(7);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char incomingData = Serial.read();
    Serial.print("Received: ");
    Serial.println(incomingData);

    controlMotors(incomingData);  // Handle motor movement
    controlServo(incomingData);   // Handle servo movement
  }
}

// Function for motor control
void controlMotors(char command) {
  if (command == 'F') { // Move Forward
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
  }
  else if (command == 'B') { // Move Backward
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, HIGH);
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, HIGH);
  }
  else if (command == 'L') { // Turn Left
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, HIGH);
  }
  else if (command == 'R') { // Turn Right
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, HIGH);
    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
  }
  else if (command == 'S') { // Stop
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
  }
}

// Function for servo movement
void controlServo(char command) {
  if (command == 'W') { // ALL SERVOS WIND
    // Lower the rover by unwinding the gear thing
    for (int pos = 90; pos <= 170; pos++) {
      servo6.write(pos);
      servo7.write(pos);
      delay(20);
    }
    delay(1500);
  }

  if (command == 'U') { // ALL SERVOS UNWIND
    // Raise the rover by winding the gear thing
    for (int pos = 170; pos >= 90; pos--) {
      servo6.write(pos);
      servo7.write(pos);
      delay(20);
    }
    delay(1500);
  }

  if (command == 'K') { // BACK TILT
    for (int pos = 90; pos <= 180; pos++) {
      servo7.write(pos);
      delay(20);
    }
    delay(1500);
  }

  if (command == 'P') { // FRONT SERVOS MOVE BACK
    // Raise the rover by winding the gear thing
    for (int pos = 180; pos >= 90; pos--) {
      servo7.write(pos);
      delay(20);
    }
    delay(1500);
  }
}
