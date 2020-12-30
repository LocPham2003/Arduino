#include <Servo.h>
 
Servo leftRear;
Servo leftFront;

Servo rightFront;
Servo rightRear;

int rightFrontID = 4;
int rightRearID = 5;

int leftRearID = 6;
int leftFrontID = 7;

int LEDindicatorID = 12;

int rollPulse = 8;
int pitchPulse = 9;
int throttlePulse = 10;
int yawPulse = 11;

int batteryVoltage;

void setup() {
  Serial.begin(57600);
  
  leftRear.attach(leftRearID);
  leftFront.attach(leftFrontID);
  rightFront.attach(rightFrontID);
  rightRear.attach(rightRearID);

  
  pinMode(throttlePulse, INPUT);
  pinMode(yawPulse, INPUT);
  pinMode(pitchPulse, INPUT);
  pinMode(rollPulse, INPUT);
  
}

void maximumThrottle(){
  leftRear.writeMicroseconds(1800);
  leftFront.writeMicroseconds(1800);
  rightFront.writeMicroseconds(1800);
  rightRear.writeMicroseconds(1800);

  delay(2000);
}

void cancelThrottle(){
  leftRear.writeMicroseconds(0);
  leftFront.writeMicroseconds(0);
  rightFront.writeMicroseconds(0);
  rightRear.writeMicroseconds(0);

  delay(2000);

}

void assignRotation(int throttle, int yaw, int roll, int pitch){
  if (throttle < 1500){
    throttle = 0;
  }
  
  int rightFrontSpeed = throttle;
  int rightRearSpeed = throttle;
  int leftFrontSpeed = throttle;
  int leftRearSpeed = throttle;
  if (yaw >= 0){
      leftFrontSpeed += yaw;
      rightRearSpeed += yaw;    
  } else if (yaw < 0){
      leftRearSpeed += abs(yaw);
      rightFrontSpeed += abs(yaw);
  }

  if (pitch > 0) {
    rightFrontSpeed += pitch;
    leftFrontSpeed += pitch; 
  } else {
    leftRearSpeed += abs(pitch);
    rightRearSpeed += abs(pitch);
  }
  
  leftRear.writeMicroseconds(leftRearSpeed);
  leftFront.writeMicroseconds(leftFrontSpeed);
  rightFront.writeMicroseconds(rightFrontSpeed);
  rightRear.writeMicroseconds(rightRearSpeed);
}

void checkVoltage(){
   batteryVoltage = (analogRead(A0) + 65) * 1.2317;

   if (batteryVoltage < 1050 && batteryVoltage > 600) {
    digitalWrite(LEDIndicatorID, HIGH);
   }
}

void loop() {
  int throttle = map(pulseIn(throttlePulse, HIGH), 1000, 2000, 1400, 1800);
  int yaw = map(pulseIn(yawPulse,HIGH), 1000, 2000, -150, 155); 
  int pitch = map(pulseIn(pitchPulse, HIGH), 1000, 2000, -150, 155);
  
  assignRotation(throttle, yaw, 0, pitch);
  
 }
