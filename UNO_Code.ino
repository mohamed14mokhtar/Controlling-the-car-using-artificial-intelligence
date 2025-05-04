#include <AFMotor.h>
#include <SoftwareSerial.h>

// Define pins for the ultrasonic sensor
#define TRIG_PIN A2
#define ECHO_PIN A1

// Define pins for the IR Sensors
#define IR_SENSOR_RIGHT A4
#define IR_SENSOR_LEFT  A3

// Speed profiles
const int HIGH_SPEED = 255;
const int MEDIUM_SPEED = 170;
const int LOW_SPEED = 100;
int SPEED = MEDIUM_SPEED;

// Stopping distances
const int STOP_DISTANCE_HIGH_SPEED = 25;
const int STOP_DISTANCE_MEDIUM_SPEED = 15;
const int STOP_DISTANCE_LOW_SPEED = 10;

// Line detection thresholds
const int IR_THRESHOLD = 500; // Adjust based on calibration
const int IR_NO_LINE_THRESHOLD = 100; // Value below which line is not detected

SoftwareSerial HC05(9, 10); // RX, TX
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

char command;
bool selfDrivingEnabled = false;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  Serial.begin(9600);
  HC05.begin(9600);
}

void loop() {
  static unsigned long lastCheckTime = 0;
  unsigned long currentTime = millis();
  

  // Handle Bluetooth commands
  if (HC05.available() > 0) {
    command = HC05.read();
    stop();

    Serial.print("Command: ");
    Serial.println(command);
    
      switch (command) {
        case 'H':
          SPEED = HIGH_SPEED;
          break;
        case 'M':
          SPEED = MEDIUM_SPEED;
          break;
        case 'N':
          SPEED = LOW_SPEED;
          break;
        case 'F':
          forward(SPEED);
          break;
        case 'B':
          back(SPEED);
          break;
        case 'L':
          left(SPEED);
          break;
        case 'R':
          right(SPEED);
          break;
        case 'S':
          selfDrivingEnabled = true;
          break;
        case 'X':
          selfDrivingEnabled = false;
          break;
      }
    if (currentTime - lastCheckTime >= 50) {
      lastCheckTime = currentTime;
      int obstacleDistance = getDistance();
      int stopDistance = getStopDistance();
      if ((obstacleDistance <= stopDistance) && (obstacleDistance != 0)) {
        stop();
        Serial.print("Obstacle detected at: ");
        Serial.println(obstacleDistance);
        return;
      }
    }
  }

  //Self-driving mode
  if (selfDrivingEnabled) {
    self_Drive(SPEED);
  }
}

void forward(int CAR_SPEED) {
  motor1.setSpeed(CAR_SPEED);
  motor1.run(FORWARD);
  motor2.setSpeed(CAR_SPEED);
  motor2.run(FORWARD);
  motor3.setSpeed(CAR_SPEED);
  motor3.run(FORWARD);
  motor4.setSpeed(CAR_SPEED);
  motor4.run(FORWARD);
}

void back(int CAR_SPEED) {
  motor1.setSpeed(CAR_SPEED);
  motor1.run(BACKWARD);
  motor2.setSpeed(CAR_SPEED);
  motor2.run(BACKWARD);
  motor3.setSpeed(CAR_SPEED);
  motor3.run(BACKWARD);
  motor4.setSpeed(CAR_SPEED);
  motor4.run(BACKWARD);
}

void left(int CAR_SPEED) {
  motor1.setSpeed(CAR_SPEED);
  motor1.run(BACKWARD);
  motor2.setSpeed(CAR_SPEED);
  motor2.run(FORWARD);
  motor3.setSpeed(CAR_SPEED);
  motor3.run(FORWARD);
  motor4.setSpeed(CAR_SPEED);
  motor4.run(BACKWARD);
}

void right(int CAR_SPEED) {
  motor1.setSpeed(CAR_SPEED);
  motor1.run(FORWARD);
  motor2.setSpeed(CAR_SPEED);
  motor2.run(BACKWARD);
  motor3.setSpeed(CAR_SPEED);
  motor3.run(BACKWARD);
  motor4.setSpeed(CAR_SPEED);
  motor4.run(FORWARD);
}

void stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(100); // Ensure full stop
}

int getDistance() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}


int getStopDistance() {
  if (SPEED == HIGH_SPEED) return STOP_DISTANCE_HIGH_SPEED;
  if (SPEED == MEDIUM_SPEED) return STOP_DISTANCE_MEDIUM_SPEED;
  return STOP_DISTANCE_LOW_SPEED;
}

void self_Drive(int CAR_SPEED) {
  if(command != 'S'){
    return;
  }
  else{
    Serial.println(digitalRead(IR_SENSOR_LEFT));
    Serial.println(digitalRead(IR_SENSOR_RIGHT));

  //line detected by both
  if(digitalRead(IR_SENSOR_LEFT)==0 && digitalRead(IR_SENSOR_RIGHT)==0){
    //Forward
    motor1.run(FORWARD);
    motor1.setSpeed(150);
    motor2.run(FORWARD);
    motor2.setSpeed(150);
    motor3.run(FORWARD);
    motor3.setSpeed(150);
    motor4.run(FORWARD);
    motor4.setSpeed(150);
  }
  //line detected by left sensor
  else if(digitalRead(IR_SENSOR_LEFT)==0 && !digitalRead(IR_SENSOR_RIGHT)==0){
    //turn left
    motor1.run(FORWARD);
    motor1.setSpeed(200);
    motor2.run(BACKWARD);
    motor2.setSpeed(200);
    motor3.run(BACKWARD);
    motor3.setSpeed(200);
    motor4.run(FORWARD);
    motor4.setSpeed(200);
    
  }
  //line detected by right sensor
  else if(!digitalRead(IR_SENSOR_LEFT)==0 && digitalRead(IR_SENSOR_RIGHT)==0){
    //turn right
    motor1.run(BACKWARD);
    motor1.setSpeed(200);
    motor2.run(FORWARD);
    motor2.setSpeed(200);
    motor3.run(FORWARD);
    motor3.setSpeed(200);
    motor4.run(BACKWARD);
    motor4.setSpeed(200);
   
  }
  //line detected by none
  else if(!digitalRead(IR_SENSOR_LEFT)==0 && !digitalRead(IR_SENSOR_RIGHT)==0){
    //stop
    motor1.run(RELEASE);
    motor1.setSpeed(0);
    motor2.run(RELEASE);
    motor2.setSpeed(0);
    motor3.run(RELEASE);
    motor3.setSpeed(0);
    motor4.run(RELEASE);
    motor4.setSpeed(0);
   
  }
  }
  
}
