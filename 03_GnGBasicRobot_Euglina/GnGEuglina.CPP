#include "GnGEuglina.h"
void EuglinaSetup()
{
  forceReading = true;   //  also try false
  sens1.begin(BH1750_TO_VCC);     //  adress pin is connected to VCC (5V or 3.3V)
  sens2.begin(BH1750_TO_GROUND);  //  adress pin is connected to ground
  sens1.calibrateTiming();  //  Calibrate for fastest conversion time
  sens2.calibrateTiming();  //  Calibrate for fastest conversion time

  sens1.start(BH1750_QUALITY_HIGH2, BH1750_MTREG_DEFAULT); //  same settings for both sensors
  sens2.start(BH1750_QUALITY_HIGH2, BH1750_MTREG_DEFAULT);
}

bool EuglinaisDone() {
  ready1 = sens1.hasValue(forceReading);
  ready2 = sens2.hasValue(forceReading);
  return (ready1 == true) && (ready2 == true);
}

void updateDeltaLux(int* temp) {
  if (EuglinaisDone()) {  //*  when both seniors have completed their measurement,
    lux1 = sens1.getLux();
    lux2 = sens2.getLux();
    Serial.print(lux1);
    Serial.print("\t");
    Serial.print(lux2);
    Serial.print("\t Delta: ");
    *temp = (int)(lux1) - (int)(lux2);
    Serial.println  (*temp);
    sens1.start();  //  start again after measuremnt is finished
    sens2.start();
  }
} 
