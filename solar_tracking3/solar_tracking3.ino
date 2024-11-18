#include <Servo.h>

// Create a Servo object
Servo myServo;

// Define the LDR pins
int ldrPin1 = A0;  // LDR1 connected to pin A0
int ldrPin2 = A1;  // LDR2 connected to pin A1
int ldrValue1 = 0; // Variable to store LDR1 value
int ldrValue2 = 0; // Variable to store LDR2 value

// Current position of the servo
int currentPosition = 90;

void setup() {
  // Attach the servo to pin 9
  myServo.attach(9);

  // Start serial communication for debugging
  Serial.begin(9600);

  // Initialize the servo to the middle position
 myServo.write(currentPosition);
}
void loop() {
  // Read the values from both LDRs
 ldrValue1 = analogRead(ldrPin1);
 ldrValue2 = analogRead(ldrPin2);

  // Print the LDR values to the Serial Monitor (for debugging)
 Serial.print("LDR1: ");
 Serial.print(ldrValue1);
 Serial.print("\tLDR2: ");
 Serial.println(ldrValue2);

 int targetPosition;

  // Compare the LDR values to determine the target position
 if (ldrValue1 > ldrValue2) {
 targetPosition = 0; // Move servo to the left
 } else if (ldrValue2 > ldrValue1) {
 targetPosition = 180; // Move servo to the right
 } else {
 targetPosition = 90; // Center position
 }
// Gradually move the servo to the target position
 moveServoSmoothly(targetPosition);

  // Wait a little before updating again
 delay(1000);
}

// Function to move the servo smoothly
void moveServoSmoothly(int targetPosition) {
 if (currentPosition < targetPosition) {
 for (int pos = currentPosition; pos <= targetPosition; pos++) {
 myServo.write(pos);
 delay(10); // Adjust delay for speed
 }
 } else if (currentPosition > targetPosition) {
 for (int pos = currentPosition; pos >= targetPosition; pos--) {
 myServo.write(pos);
 delay(10); // Adjust delay for speed
 }
 }
 currentPosition = targetPosition; // Update the current position
}