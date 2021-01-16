#include "GnGBasicRobot.h"
#include <Arduino.h>
#include <hp_BH1750.h>

#include "GnGEuglina.h"
#include "GnGEuglina.CPP"

GnGBasicRobot robot1;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("");
  EuglinaSetup();
  robot1.setRobotSpeed(90);
}


int x = 0;
void loop() {

  updateDeltaLux(&x);

  if (x > 100) {
    robot1.turnRobotRight(50);
  } else if (x < -100) {
    robot1.turnRobotLeft(50);
  }
  else {
    robot1.moveRobotForward(50);
  }
}
