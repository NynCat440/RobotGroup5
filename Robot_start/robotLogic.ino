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
  unsigned long currentMillis = millis();
  int* IRvalues;
  IRvalues = readInfrared();



  if (!isTurning && !wallDetected) {
    IRvalues = readInfrared();

    if (IRvalues[1] == 1 && IRvalues[2] == 1) {
      motorControl(100, 100);
      motorControl(200, 200);
      currentState = "forward";
    } else if (IRvalues[1] == 0 && IRvalues[2] == 1) {
      motorControl(80, 100);
      motorControl(180, 200);
      currentState = "left";
    } else if (IRvalues[1] == 1 && IRvalues[2] == 0) {
      motorControl(100, 80);
      motorControl(200, 180);
      currentState = "right";
    } else if (IRvalues[0] == 1 && IRvalues[1] == 1 && IRvalues[2] == 1 && IRvalues[3] == 1) {

      if (currentState == "forard") {
        motorControl(100, 100);
        motorControl(200, 200);
      } else if (currentState == "left") {
        motorControl(80, 100);
        motorControl(180, 200);
      } else if (currentState == "right") {
        motorControl(100, 80);
        motorControl(200, 180);
      }
    }

  } else if (isTurning && !wallDetected) {

    if (initialForwardMotion) {
      motorControl(200, 200);
      currentState = "Bumping Out...";
      delay(initialMotionDuration);
      initialForwardMotion = false;

    } else {


      if (turnDirection == "left") {


        if (currentMillis - turnStartTime >= initialTurnDuration && IRvalues[2] == 1) {
          Serial.println("Detected Center IR Sensor after initial turn duration");
          isTurning = false;
          motorControl(0, 0);
          currentState = "Turning Left - Next Line Detected";
          motorControl(turnSpeed, -turnSpeed);
          delay(50);
          motorControl(0, 0);
          delay(50);
          currentState = "Forward";
        } else {
          motorControl(-turnSpeed, turnSpeed);
          currentState = "Turning Left - No Line Yet Detected";
        }


      } else if (turnDirection == "right") {


        if (currentMillis - turnStartTime >= initialTurnDuration && IRvalues[1] == 1) {
          Serial.println("Detected Center IR Sensor");
          isTurning = false;
          currentState = "Turning Right - Next Line Detected";
          motorControl(-turnSpeed, turnSpeed);
          delay(50);
          motorControl(0, 0);
          delay(50);
          currentState = "Forward";

        } else {

          motorControl(turnSpeed, -turnSpeed);
          currentState = "Turning Right - No Line Yet Detected";
        }
      }
    }


  } else if (isTurning && wallDetected) {

    if (initialForwardMotion) {
      motorControl(-200, -200);
      currentState = "Stopping...";
      delay(100);
      initialForwardMotion = false;
    } else {
      if (currentMillis - turnStartTime >= initialTurnDuration && IRvalues[2] == 1) {
        Serial.println("Detected Center IR Sensor after initial turn duration");
        isTurning = false;
        currentState = "Turning Left - Next Line Detected";
        motorControl(turnSpeed, -turnSpeed);
        delay(50);
        motorControl(0, 0);
        delay(50);
        wallDetected = false;
        currentState = "Forward";
      } else {
        motorControl(-turnSpeed, turnSpeed);
        currentState = "Turning Left - No Line Yet Detected";
      }
    }
  }
}

void turnLogic() {
  unsigned long currentMillis = millis();
  int* IRvalues;
  IRvalues = readInfrared();

  if (currentDistance < 8 && wallDetected == false) {
    isTurning = true;
    wallDetected = true;
    turnStartTime = currentMillis;
    initialForwardMotion = true;
  }

  if (!isTurning && wallDetected == false) {


    if (IRvalues[3] == 1 && firstDetectionTime1 == 0) {
      firstDetectionTime1 = currentMillis;
      Serial.println("Detected Left Sensor");
    }
    if (IRvalues[0] == 1 && firstDetectionTime4 == 0) {
      firstDetectionTime4 = currentMillis;
      Serial.println("Detected Right Sensor");
    }


    if (firstDetectionTime1 > 0 && currentMillis - firstDetectionTime1 < sensorCheckThreshold && firstDetectionTime4 > 0 && currentMillis - firstDetectionTime4 < sensorCheckThreshold) {
      isTurning = true;
      initialForwardMotion = true;
      turnStartTime = currentMillis;
      turnDirection = lastTurnDirection;
      firstDetectionTime1 = 0;
      firstDetectionTime4 = 0;
      lastTurnDirection = turnDirection;
      Serial.print("Solid Line Detected (Sensors 1 and 4) - turning ");
      Serial.println(turnDirection);
    } else if (firstDetectionTime1 > 0 && currentMillis - firstDetectionTime1 >= sensorCheckThreshold) {
      isTurning = true;
      initialForwardMotion = true;
      turnStartTime = currentMillis;
      turnDirection = "left";
      firstDetectionTime1 = 0;
      lastTurnDirection = turnDirection;
      Serial.println("Left Turn Detected");
    } else if (firstDetectionTime4 > 0 && currentMillis - firstDetectionTime4 >= sensorCheckThreshold) {
      isTurning = true;
      initialForwardMotion = true;
      turnStartTime = currentMillis;
      turnDirection = "right";
      firstDetectionTime4 = 0;
      lastTurnDirection = turnDirection;
      Serial.println("Right Turn Detected");
    }
  }
}
