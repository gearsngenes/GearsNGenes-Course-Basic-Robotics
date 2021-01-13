#include "GnGSonarUS100Basic.h"
//#include "GnGSonarUS100Basic.CPP"
GnGSonarUS100Basic sonar1 = GnGSonarUS100Basic(A3, A4);
void setup() {

}

void loop() {
  int distance = sonar1.getDistanceCM();
  Serial.print("distance to nearest object:");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100);
}
