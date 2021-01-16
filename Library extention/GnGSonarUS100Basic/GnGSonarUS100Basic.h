/*
   GearsNGEnes released this library
   It is a simple wrapper to the US100 sonar.
   The code here is influenced by the work of  https://sites.google.com/site/myscratchbooks/home/projects/project-09-ultrasonic-sensor
   This is released under Creative Commons and you should include this comment when you are using.
   See GearsNGenes at:
   Code: https://github.com/gearsngenes
   Website: https://gearsngenes.com/
   Blogs:https://gearsngenes.com/blog/
*/

#ifndef GnGSonarUS100Basic_h
#define GnGSonarUS100Basic_h
#include "Arduino.h"

class GnGSonarUS100Basic
{
  private:
    int triggerPin;
    int echoPin;

  public:
    GnGSonarUS100Basic(int triggerpin, int echopin); // can be digital or analog pins; dont need to be PWM pins.

    void setUp(); // assign pinModes for each of the pins


    int getDistanceCM();

};
#endif