#include "Arduino.h"
#include <string.h>

#define _Subscribe2Button
#define _Subscribe2Color
#define _Subscribe2Acc

//#define _Subscribe2Other

#include <EventFactory.h>
#include <EventFactory.CPP>

#include <GnGBasicRobot.h>
//#include "GnGBasicRobot.CPP"

#include <GnG_BLE_HWSPI.h>



GnG_BLE_HWSPI blueToothFeather;

GnGBasicRobot blueRobot;//(12, 11, 10, 9, 6, 50 );

void setup() {

  Serial.begin(115200);
  delay(2000);
  
  blueToothFeather.basicSetup("GnG BF1");

}


void readAndProcessEvents()
{

  uint8_t len = blueToothFeather.readPacket();
  if (len == 0) return;

  GnGBleFactory eventFactory;
  eventFactory.setMessage(blueToothFeather.packetbuffer, len);
  GnGBLEBaseEvent* bleEvent= eventFactory.transformMsg2Event();
  
  bleEvent-> processEvent();
  free( bleEvent);
}

void loop() {
  readAndProcessEvents();
  delay(5);
}
