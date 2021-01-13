#include <GnGBasicRobot.h>
//#include <GnGBasicRobot.CPP>
GnGBasicRobot robot1;

void setup() {
  // put your setup code here, to run once:
  robot1.setUp();
  robot1.setRobotSpeed(50);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

Serial.println("Forward");
  robot1.moveRobotForward(2000);

  Serial.println("Backward");
  robot1.moveRobotBackward(2000);

  Serial.println("turn Right");
  robot1.turnRobotRight(2000);

  Serial.println("turn Left");
  robot1.turnRobotLeft(2000);

  Serial.println("Stop");
  robot1.stopRobot(2000);

  Serial.println("pivot Turn Right");
  robot1.pivotTurnRobotRight (2000);

  Serial.println("pivot Turn Left");
  robot1.pivotTurnRobotLeft (2000);

  Serial.println("Stop");
  robot1.stopRobot(2000);
 
  Serial.println();
}
