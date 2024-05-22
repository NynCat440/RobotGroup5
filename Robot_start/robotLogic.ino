bool initialForwardMotion = false;
const unsigned long initialMotionDuration = 350;

unsigned long turnStartTime = 0;
const unsigned long initialTurnDuration = 600;
int turnSpeed = 150;

const unsigned long sensorCheckThreshold = 50;

unsigned long firstDetectionTime1 = 0;
unsigned long firstDetectionTime4 = 0;

void robotLogic() {
  motorLogic();

  turnLogic();
}

void motorLogic() {
  int* IRvalues;
  IRvalues = readInfrared();

  if (IRvalues[1] == 1 && IRvalues[2] == 1) {
    motorControl(200, 200);
    currentState = "forward";
  } else if (IRvalues[1] == 0 && IRvalues[2] == 1) {
    motorControl(180, 200);
    currentState = "left";
  } else if (IRvalues[1] == 1 && IRvalues[2] == 0) {
    motorControl(200, 180);
    currentState = "right";
  } else if (IRvalues[0] == 1 && IRvalues[1] == 1 && IRvalues[2] == 1 && IRvalues[3] == 1) {

    if (currentState == "forard") {
      motorControl(200, 200);
    } else if (currentState == "left") {
      motorControl(180, 200);
    } else if (currentState == "right") {
      motorControl(200, 180);
    }
  }
}

turnLogic() {

}