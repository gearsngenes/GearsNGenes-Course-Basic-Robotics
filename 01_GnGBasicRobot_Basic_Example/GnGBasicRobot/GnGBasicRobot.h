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

#ifndef GnGBasicRobot_h
#define GnGBasicRobot_h
#include <Arduino.h>
class GnGBasicRobot
{
  private:
    int Motor1In1;
    int Motor1In2;
    int PWMIn;
    int Motor2In1;
    int Motor2In2;
    int BoardAlive;
    int speedval;
    int state;


  public:
    GnGBasicRobot();
    GnGBasicRobot(int m1I1, int m1I2, int pwmpin, int m2I1, int m2I2, int spval);

    void setUp(); // assign pinModes for each of the pins
    
    void printVals(); // diagnostic
    void moveM1Forward(); // First motor m1 to move forward
    void moveM1Backward(); // First motor m2 to move forward
    void moveM2Backward(); // First motor m1 to move backward 
    void moveM2Forward();// First motor m2 to move backward 
    void stopM1();
    void stopM2();

    
    void setRobotSpeed(int speedval1); // set a speed between 0 to 255
    void increaseSpeed(int detlaSp=10); // increase by 10 default
    void decreaseSpeed(int detlaSp=10); // decrease by 10 default
    
    
    void moveRobotForward(int delTime = 500);
    void moveRobotBackward(int delTime = 500);
    void turnRobotRight(int delTime = 500); // for delTime ms, the robot will turn 'in place' around the vertical axis through the center
    void turnRobotLeft(int delTime = 500);// for delTime ms, the robot will turn 'in place' around the vertical axis through the center
    void stopRobot(int delTime = 500);

    void pivotTurnRobotRight(int delTime= 500); //for delTime ms, the robot will turn right around the other wheel - not center
    void pivotTurnRobotLeft(int delTime= 500);//for delTime ms, the robot will turn left around the other wheel- not center
    
    void processRightTurn(boolean start);//start = true means start the turn. start = false means stop the turn
    void processLeftTurn(boolean start);//start = true means start the turn. start = false means stop the turn
    
    
};
#endif
