//Nayan, robot startup

#include <tcs3200.h>

String currentState = "Null";
String oldCurrentState = "Null";

String turnDirection = "";
String turnLastDirection = "";
bool isTurning = false;
bool wallDetected = false;

#define IR_1 4
#define IR_2 7
#define IR_3 8
#define IR_4 12

#define COLOR_0 A0
#define COLOR_1 A1
#define COLOR_2 A2
#define COLOR_3 A3
#define COLOR_OUT A4

#define MOTOR_PIN1 3
#define MOTOR_PIN2 5
#define MOTOR_PIN3 6
#define MOTOR_PIN4 9

#define TRIG_PIN 10
#define ECHO_PIN 11

unsigned long irSensorMillis = 0;

unsigned long colorSensorMillis = 0;

unsigned long ultrasonicSensorMillis = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(IR_3, INPUT);
  pinMode(IR_4, INPUT);

  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);

  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - irSensorMillis >= 500) {
    irSensorMillis = currentMillis;
    readInfrared();
  }

  if (currentMillis - colorSensorMillis >= 250) {
    colorSensorMillis = currentMillis;
    readColorSensor();
  }

  if (currentMillis - ultrasonicSensorMillis >= 500) {
    ultrasonicSensorMillis = currentMillis;
    readUltrasonicSensor();
  }
  robotLogic();
}
