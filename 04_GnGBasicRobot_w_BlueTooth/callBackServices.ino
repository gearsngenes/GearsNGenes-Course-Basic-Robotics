#ifdef _Subscribe2Button
void GnGbuttonCallBack(GnGButtonEvent* buttonEventptr)
{
  buttonEventptr->printSelf();
  Serial.print("Buttion Number:::::"); Serial.println(buttonEventptr->buttonNum);

  switch (buttonEventptr->buttonNum)
  {
    case 4: {
        blueRobot.stopRobot();
      };
      break;
    case 5: {
        if (buttonEventptr-> buttonPressed) {
          blueRobot.moveRobotForward();

        }
      };
      break;
    case 6: {
        if (buttonEventptr-> buttonPressed) {
          blueRobot.moveRobotBackward();

        };
      }
      break;
    case 7: {
        blueRobot.processRightTurn(buttonEventptr-> buttonPressed);
      }
      break;
    case 8: {
        blueRobot.processLeftTurn(buttonEventptr-> buttonPressed);

      }
      break;
    case 1:
      {
        blueRobot.increaseSpeed();
        Serial.println ("....in increase speed");

      }
      break;
    case 3:
      {
        blueRobot.decreaseSpeed();
        Serial.println ("....in decrease speed");
      }
      break;
  }
}
#endif

#ifdef _Subscribe2Color
void GnGColorCallBack(GnGColorEvent* colorEventptr)
{
  colorEventptr->printSelf();
}
#endif

#ifdef _Subscribe2Acc
void GnGAccCallBack(GnGAccEvent* accEventptr)
{
  accEventptr->printSelf();
}
#endif

#ifdef _Subscribe2Other
void GnGMagCallBack(GnGMagEvent* magEventptr)
{
  magEventptr->printSelf();
}
#endif

#ifdef _Subscribe2Other
void GnGGyroCallBack(GnGGyroEvent* gyroEventptr)
{
  gyroEventptr->printSelf();
}
#endif

#ifdef _Subscribe2Other
void GnGQuatCallBack(GnGQuatEvent* quatEventptr)
{
  quatEventptr->printSelf();
}
#endif