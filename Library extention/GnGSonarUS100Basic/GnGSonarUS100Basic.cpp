/*
  GearsNGEnes released this library
  It is a simple wrapper to the US100 sonar.
  The code here is influenced by the work of
  https://sites.google.com/site/myscratchbooks/home/projects/project-09-ultrasonic-sensor
  This is released under Creative Commons and you should include this comment when you are using.
  See GearsNGenes at:
  Code: https://github.com/gearsngenes
  Website: https://gearsngenes.com/
  Blogs: https: //gearsngenes.com/blog/

*/ 


#include "Arduino.h"
#include "GnGSonarUS100Basic.h"

GnGSonarUS100Basic:: GnGSonarUS100Basic(int tpin, int epin)
{
  this->triggerPin = tpin;
  this -> echoPin = epin;
  this->setUp();
}
void GnGSonarUS100Basic::setUp()
{
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
}


int GnGSonarUS100Basic:: getDistanceCM()
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(50);// does not matter as long as it is >10 or so micro sec
  digitalWrite(triggerPin, LOW);


  const unsigned long duration = pulseIn(echoPin, HIGH);
  int distance = (duration / 29) / 2; //simple formula from the speed of sound in air.

  return distance;
};