#include "Arduino.h"
#include <string.h>
#include <Adafruit_NeoPixel.h>

#define _Subscribe2Color

#include <EventFactory.h>
#include <EventFactory.CPP>

#include <GnG_BLE_HWSPI.h>

int pin = 5; // On Trinket or Gemma, suggest changing this to 1
int numberPixels = 1; //#define NUMPIXELS 1 // Popular NeoPixel ring size
int delayV = 200;

Adafruit_NeoPixel pixels(numberPixels, pin, NEO_RGB + NEO_KHZ800);
GnG_BLE_HWSPI blueToothFeather;

void setup()
{
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  blueToothFeather.basicSetup("GnG BF2");
}


void readAndProcessEvents()
{

  uint8_t len = blueToothFeather.readPacket();
  if (len == 0) return;

  GnGBleFactory eventFactory;
  eventFactory.setMessage(blueToothFeather.packetbuffer, len);
  GnGBLEBaseEvent* bleEvent= eventFactory.transformMsg2Event();
  
  bleEvent-> processEvent();
  free(bleEvent);
}


void loop() {
  readAndProcessEvents();
  //pixels.clear(); // Set all pixel colors to 'off'

  //pixels.setPixelColor(0, pixels.Color(0, 150, 0));

  //pixels.show();   // Send the updated pixel colors to the hardware.

  //delay(delayV); // Pause before next pass through loop
  //pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  //pixels.show();   // Send the updated pixel colors to the hardware.
  //delay(delayV);
}
