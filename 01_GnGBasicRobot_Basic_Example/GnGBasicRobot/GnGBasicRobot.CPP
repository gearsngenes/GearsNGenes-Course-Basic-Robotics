/*
 * GearsNGEnes released this library
 * GnGBasicRobot is a basic Robot class that works with Adafruit's Feather Format (pin configurations work for 32u4, 32u4 ble, Huzzah ESP8266 and M0)
 * It can be hooked up with most H-Bridges.
 * It comes with a corresponding PCB open-source hardware (OSHpark will sell)
 * It provides various basic robot movements with a couple of advanced ones ("process" turns) for bluetooth libraries.
 * This is released under Creative Commons and you should include this comment when you are using.
 * See GearsNGenes at: 
 * Code: https://github.com/gearsngenes
 * Website: https://gearsngenes.com/
 * Blogs:https://gearsngenes.com/blog/
 */
 
#include <GnGBasicRobot.h>
#include "Arduino.h"

GnGBasicRobot::GnGBasicRobot()
{
  Motor1In1 = 11;
  Motor1In2 = 12;
  PWMIn = 10;
  Motor2In1 = 9;
  Motor2In2 = 6;
  speedval = 150;
  state = 0;
  this->setUp();
}
GnGBasicRobot::GnGBasicRobot(int m1I1, int m1I2, int pwmpin, int m2I1, int m2I2, int spval)
{
  Motor1In1 = m1I1;
  Motor1In2 = m1I2;
  PWMIn = pwmpin;
  Motor2In1 = m2I1;
  Motor2In2 = m2I2;
  speedval = spval;
  state = 0;
  this->setUp();
}
void GnGBasicRobot::setUp() {
  pinMode(Motor1In1, OUTPUT);
  pinMode(Motor1In2, OUTPUT);
  pinMode(Motor2In1, OUTPUT);
  pinMode(Motor2In2, OUTPUT);
  pinMode(PWMIn, OUTPUT);
//  stopRobot(); // default at the beginning is to stop the robot
  
}



void GnGBasicRobot::printVals()
{
  Serial.println("in printvals");
}
void GnGBasicRobot::moveM1Forward()
{
  analogWrite(PWMIn, speedval);
  digitalWrite(Motor1In1, HIGH);
  digitalWrite (Motor1In2, LOW );
}


void GnGBasicRobot:: moveM1Backward() {
  analogWrite(PWMIn, speedval);
  digitalWrite(Motor1In1, LOW);
  digitalWrite (Motor1In2, HIGH);
}

void GnGBasicRobot::moveM2Backward() {
  analogWrite(PWMIn, speedval);
  digitalWrite(Motor2In1, HIGH);
  digitalWrite (Motor2In2, LOW );
}

void GnGBasicRobot::moveM2Forward() {
  analogWrite(PWMIn, speedval);
  digitalWrite(Motor2In1, LOW);
  digitalWrite (Motor2In2, HIGH);
}

void GnGBasicRobot::stopM1()
{
  digitalWrite(Motor1In1, LOW);
  digitalWrite(Motor1In2, LOW);
}

void GnGBasicRobot::stopM2()
{
  digitalWrite(Motor2In1, LOW);
  digitalWrite(Motor2In2, LOW);
}
void GnGBasicRobot::moveRobotForward(int delTime)
{
  state = 1;
  moveM1Forward();
  moveM2Forward();
  delay(delTime);
}


void GnGBasicRobot::moveRobotBackward(int delTime)
{
  state = 0;
  moveM1Backward();
  moveM2Backward();
  delay(delTime);
}


void GnGBasicRobot::turnRobotRight(int delTime)
{
  moveM2Forward();
  moveM1Backward();
  delay(delTime);
}
void GnGBasicRobot::turnRobotLeft(int delTime)
{
  moveM2Backward();
  moveM1Forward();
  delay(delTime);
}
void GnGBasicRobot::pivotTurnRobotRight(int delTime)
{
  moveM2Forward();
  stopM1();
  delay(delTime);
}
void GnGBasicRobot::pivotTurnRobotLeft(int delTime)
{
  stopM2();
  moveM1Forward();
  delay(delTime);
}
void GnGBasicRobot::stopRobot(int delTime )
{
  state = -1;
  stopM1();
  stopM2();
  delay(delTime);
}

void GnGBasicRobot::processRightTurn(boolean start)
/* start turning if "start = true"; otherwise, stop turning,
   go back to whatever state it was (forard or backward)
*/
{
  if (start)
  {
    turnRobotRight();
  }
  else {
    if (state == 1) {
      moveRobotForward();
    } else if (state == 0) {
      moveRobotBackward();
    } else {
      stopRobot();
    }
  };

}
void GnGBasicRobot::processLeftTurn(boolean start)
/* start turning if "start = true"; otherwise, stop turning,
   go back to whatever state it was (forard or backward)
*/
{
  if (start)
  {
    turnRobotLeft();
  }
  else {
    if (state == 1) {
      moveRobotForward();
    } else if (state == 0) {
      moveRobotBackward();
    } else {
      stopRobot();
    }
  };

}
void GnGBasicRobot::setRobotSpeed(int speedval1)
{
  speedval = speedval1;
  analogWrite(PWMIn, speedval);
}
void GnGBasicRobot::increaseSpeed(int detlaSp)
{
  speedval = (speedval + detlaSp);
  if (speedval >= 255) {
    speedval = 255;
  }
  analogWrite(PWMIn, speedval);
  Serial.print("Speed: "); Serial.println(speedval);
}
void GnGBasicRobot::decreaseSpeed(int detlaSp)
{
  speedval = (speedval - detlaSp);
  if (speedval <= 10) {
    speedval = 0;
  }
  analogWrite(PWMIn, speedval);
  Serial.print("Speed: "); Serial.println(speedval);
}
