#include <tcs3200.h>

//Nayan, robot startup

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

unsigned long irSensorMillis = 0;

unsigned long colorSensorMillis = 0;

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

  motorControl(255, 255);
  delay(1000);
  motorControl(0, 0);
  delay(100);
  motorControl(255, -255);
  delay(500);
  motorControl(0, 0);
  delay(100);
}
