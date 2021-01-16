#ifndef GnGEuglina_h
#define GnGEuglina_h
#include "Arduino.h"
 

    hp_BH1750 sens1;          //  create first sensor
    hp_BH1750 sens2;          //  create second sensor


    unsigned int lux1, lux2; //  hold the results
    bool ready1, ready2;     //  measurement finished?
    bool forceReading;       //  force readings and do not only
    //wait for estimated measurement time.

  
#endif
