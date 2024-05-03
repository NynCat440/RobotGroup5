//#include <tcs3200.h>

//Nayan, robot startup

#define IR_1 2
#define IR_2 4
#define IR_3 7
#define IR_4 8

//#define COLOR_0 A0
//#define COLOR_1 A1
//#define COLOR_2 A2
//#define COLOR_3 A3
//#define COLOR_4 A4

unsigned long irSensorMillis = 0;
void setup() {
  Serial.begin(9600);
  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(IR_3, INPUT);
  pinMode(IR_4, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - irSensorMillis >= 500) {
    irSensorMillis = currentMillis;
    readInfrared();
  }
}
