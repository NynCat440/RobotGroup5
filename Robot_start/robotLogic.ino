void robotLogic() {
  motorLogic();
}

void motorLogic() {
  int* IRvalues;
  IRvalues = readInfrared();

  if (IRvalues[1] == 1 && IRvalues[2] == 1) {
    motorControl(200, 200);
    currentState = "forward";
  } else if (IRvalues[1] == 0 && IRvalues[2] == 1) {
    motorControl(150, 200);
    currentState = "left";
  } else if (IRvalues[1] == 1 && IRvalues[2] == 0) {
    motorControl(200, 150);
    currentState = "right";
  } else if (IRvalues[0] == 1 && IRvalues[1] == 1 && IRvalues[2] == 1 && IRvalues[3] == 1) {

    if (currentState == "forard") {
      motorControl(200, 200);
    } else if (currentState == "left") {
      motorControl(150, 200);
    } else if (currentState == "right") {
      motorControl(200, 150);
    }
  }
}