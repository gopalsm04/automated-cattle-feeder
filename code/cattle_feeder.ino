// Include necessary libraries
#include <Servo.h>

// Define IR sensor pins
#define LEFT_IR A0
#define RIGHT_IR A1

// Define ultrasonic sensor pins
#define TRIG_PIN 9
#define ECHO_PIN 8

// Define motor control pins
#define LEFT_MOTOR_FORWARD 2
#define LEFT_MOTOR_BACKWARD 3
#define RIGHT_MOTOR_FORWARD 4
#define RIGHT_MOTOR_BACKWARD 5

// Create servo object
Servo servo;

// Define variables
int obstacleCount = 0;
long duration;
int distance;

void setup() {
  // Initialize pins
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);

  // Attach servo motor
  servo.attach(6);
  servo.write(0); // Set initial position to 0°

  Serial.begin(9600);
}

void loop() {
  followLine();
  checkObstacle();
}

void followLine() {
  int leftIR = digitalRead(LEFT_IR);
  int rightIR = digitalRead(RIGHT_IR);

  if (leftIR == LOW && rightIR == LOW) {
    // Move forward
    moveForward();
  } else if (leftIR == HIGH && rightIR == LOW) {
    // Turn right
    turnRight();
  } else if (leftIR == LOW && rightIR == HIGH) {
    // Turn left
    turnLeft();
  } else {
    // Stop
    stopMotors();
  }
}

void checkObstacle() {
  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo time
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance
  distance = duration * 0.034 / 2;

  if (distance > 0 && distance < 20) { // Obstacle detected within 20 cm
    obstacleCount++;
    handleObstacle(obstacleCount);

    if (obstacleCount >= 4) {
      obstacleCount = 0; // Reset obstacle count after 4 obstacles
    }
  }
}

void handleObstacle(int count) {
  stopMotors();

  switch (count) {
    case 1:
      servo.write(30);
      delay(15000); // Wait for 15 seconds
      break;
    case 2:
      servo.write(60);
      delay(15000); // Wait for 15 seconds
      break;
    case 3:
      servo.write(90);
      delay(15000); // Wait for 15 seconds
      break;
    case 4:
      servo.write(0);
      delay(45000); // Wait for 45 seconds
      break;
  }
}

void moveForward() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void turnLeft() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void turnRight() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void stopMotors() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}
