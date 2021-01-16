#include "GnGSonarUS100Basic.h"
//#include "GnGSonarUS100Basic.CPP"
#include <GnGBasicRobot.h>

GnGBasicRobot robot1;
GnGSonarUS100Basic sonar1 = GnGSonarUS100Basic(A3, A4);
void setup() {

}

void loop() {
  int distance = sonar1.getDistanceCM();
  Serial.print("distance to nearest object:");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 10) {
    robot1.stopRobot();
    robot1.moveRobotBackward();
    robot1.turnRobotRight(250);
  }
  robot1.moveRobotForward(100);
}
