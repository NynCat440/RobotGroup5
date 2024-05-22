void robotLogic() {
  motorLogic();
}

void motorLogic() {
  int* IRvalues;
  IRvalues = readInfrared();

  if (IRvalues[1] == 1 && IRvalues[2] == 1) {
    motorControl(100, 100);
    currentState = "forward";
  } else if (IRvalues[1] == 0 && IRvalues[2] == 1) {
    motorControl(80, 100);
    currentState = "left";
  } else if (IRvalues[1] == 1 && IRvalues[2] == 0) {
    motorControl(100, 80);
    currentState = "right";
  } else if (IRvalues[0] == 1 && IRvalues[1] == 1 && IRvalues[2] == 1 && IRvalues[3] == 1) {

    if (currentState == "forard") {
      motorControl(100, 100);
    } else if (currentState == "left") {
      motorControl(80, 100);
    } else if (currentState == "right") {
      motorControl(100, 80);
    }
  }
}