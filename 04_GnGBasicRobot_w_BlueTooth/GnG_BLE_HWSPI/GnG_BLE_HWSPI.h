#include "Arduino.h"
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"

#if SOFTWARE_SERIAL_AVAILABLE
#include <SoftwareSerial.h>
#endif

#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"
#ifndef GnG_BLE_HWSPI_h
#define GnG_BLE_HWSPI_h

class GnG_BLE_HWSPI
{
  private:
    char buf[60];


  protected:

  public:


    static const boolean FACTORYRESET_ENABLE = true;//false ;



    // --- NINE Parser constants 5 for sensors, 2 for button and color, buffersize and timeout.
    static const int READ_BUFSIZE = 20;
    static const int BLE_READPACKET_TIMEOUT = 500;

    static const int PACKET_BUTTON_LEN = 5;
    static const int PACKET_COLOR_LEN = 6;

    static const int PACKET_ACC_LEN = 15;
    static const int PACKET_GYRO_LEN = 15;
    static const int PACKET_MAG_LEN = 15;
    static const int PACKET_QUAT_LEN = 19;
    static const int PACKET_LOCATION_LEN = 15;



    // -- end Parser constants

    // ----- helper functions
    static void GnG_BLE_HWSPI:: printError(const __FlashStringHelper* err);
 //   static float GnG_BLE_HWSPI:: parsefloat(uint8_t *buffer);
    void printHex(const uint8_t * data, const uint32_t numBytes);

    // -- end helper functions

    int8_t memBLUEFRUIT_SPI_CS;
    int8_t memBLUEFRUIT_SPI_IRQ;
    int8_t memBLUEFRUIT_SPI_RST;

   // String givenFeatherName= "Adafruit Bluefruit LE";
    
    boolean memVerboseMode = true;

    Adafruit_BluefruitLE_SPI* internalBLE;

    //packet buffer itself
    uint8_t packetbuffer[READ_BUFSIZE + 1];


    GnG_BLE_HWSPI::GnG_BLE_HWSPI ();

    // two most important functions of BLE Controller: setup the bluetooth modulre, read packet from controller app.

    void GnG_BLE_HWSPI:: basicSetup(String givenFeatherName= "Adafruit Bluefruit LE");

    uint8_t readPacket( );
    // one more function: changing the name

    void GnG_BLE_HWSPI:: changeName(String blueFeathername);
};
#endif