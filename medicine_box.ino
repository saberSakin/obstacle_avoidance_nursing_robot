#include <Servo.h>

const int trigPin = 9;    // Trigger pin of ultrasonic sensor
const int echoPin = 10;   // Echo pin of ultrasonic sensor
const int servoPin = 11;  // Servo motor pin

Servo servo;              // Create a servo object

long duration;            // Variable to store the duration of sound wave travel
int distance;             // Variable to store the distance measurement

unsigned long previousMillis = 0;  // Variable to store the last time the servo was moved
const long interval = 5000;        // Interval after which the servo will reset (in milliseconds)

void setup() {
  pinMode(trigPin, OUTPUT);  // Set trigPin as OUTPUT
  pinMode(echoPin, INPUT);   // Set echoPin as INPUT
  servo.attach(servoPin);    // Attach the servo to its pin
  servo.write(90);           // Initial position of the servo (90 degrees)
  Serial.begin(9600);        // Initialize serial communication
}

void loop() {
  // Ultrasonic sensor operation
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // If hand detected within a certain range, move the servo
  if (distance < 20 && distance > 0) {  // Adjust this range according to your setup
    moveServo();  // Call the function to move the servo
  }

  // Check if it's time to reset the servo position
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    servo.write(90);  // Reset servo position to 90 degrees
  }
}

void moveServo() {
  // Move the servo to a certain position
  servo.write(0);  // Change this value to adjust the position
  delay(1000);     // Delay to hold the position
}
