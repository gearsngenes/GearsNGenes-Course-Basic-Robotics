#include "GnG_BLE_HWSPI.h"


static void  GnG_BLE_HWSPI:: printError(const __FlashStringHelper* err)
{
  Serial.println(err);
  while (1);
}

GnG_BLE_HWSPI::GnG_BLE_HWSPI ()
{
  memBLUEFRUIT_SPI_CS = 8;
  memBLUEFRUIT_SPI_IRQ   = 7;
  memBLUEFRUIT_SPI_RST = 4;
  internalBLE = new Adafruit_BluefruitLE_SPI (memBLUEFRUIT_SPI_CS, memBLUEFRUIT_SPI_IRQ, memBLUEFRUIT_SPI_RST );

}

void GnG_BLE_HWSPI:: changeName(String blueFeathername)
{
  String broadcastCMD = String("AT+GAPDEVNAME=" + blueFeathername);
  char buf[60];
  broadcastCMD.toCharArray(buf, 60);
  if (internalBLE->sendCommandCheckOK(buf))
  {
    Serial.println("name changed");
  }

}

void GnG_BLE_HWSPI:: basicSetup(String givenFeatherName)
{

//  while (!Serial);  // required for Flora & Micro

  delay(500);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit App Controller Example"));
  Serial.println(F("-----------------------------------------"));


  Serial.print(F("Initialising the Bluefruit LE module: "));


  if ( !(internalBLE->begin(memVerboseMode)) )
  {
    // error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
    GnG_BLE_HWSPI:: printError (F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if (GnG_BLE_HWSPI::FACTORYRESET_ENABLE )
  {

    Serial.println(F("Performing a factory reset: "));
    if ( ! (internalBLE->factoryReset() )) {
      //error(F("Couldn't factory reset"));
      GnG_BLE_HWSPI:: printError (F("Couldn't factory reset"));
    }
  }


  internalBLE->echo(false);

  Serial.println("Requesting Bluefruit info:");

  internalBLE->info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in Controller mode"));
  Serial.println(F("Then activate/use the sensors, color picker, game controller, etc!"));
  Serial.println();

  internalBLE->verbose(false);  // debug info is a little annoying after this point!
  
  this->changeName(givenFeatherName);

  while (! (internalBLE->isConnected())) {
    delay(500);
  }

  Serial.println(F("******************************"));

  // LED Activity command is only supported from 0.6.6
  if (internalBLE->isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    internalBLE->sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Set Bluefruit to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  internalBLE->setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("******************************"));
}



/**************************************************************************/
/*!
    @brief  Casts the four bytes at the specified address to a float
*/
/**************************************************************************/
/*
 * 
 float GnG_BLE_HWSPI::parsefloat(uint8_t *buffer)
{
  float f;
  memcpy(&f, buffer, 4);
  return f;
}
*/
/**************************************************************************/
/*!
    @brief  Prints a hexadecimal value in plain characters
    @param  data      Pointer to the byte data
    @param  numBytes  Data length in bytes
*/
/**************************************************************************/
void GnG_BLE_HWSPI::printHex(const uint8_t * data, const uint32_t numBytes)
{
  uint32_t szPos;
  for (szPos = 0; szPos < numBytes; szPos++)
  {
    Serial.print(F("0x"));
    // Append leading 0 for small values
    if (data[szPos] <= 0xF)
    {
      Serial.print(F("0"));
      Serial.print(data[szPos] & 0xf, HEX);
    }
    else
    {
      Serial.print(data[szPos] & 0xff, HEX);
    }
    // Add a trailing space if appropriate
    if ((numBytes > 1) && (szPos != numBytes - 1))
    {
      Serial.print(F(" "));
    }
  }
  Serial.println();
}

/**************************************************************************/
/*!
    @brief  Waits for incoming data and parses it
*/
/**************************************************************************/

uint8_t GnG_BLE_HWSPI::readPacket()
{
  //  uint16_t origtimeout = timeout, replyidx = 0;
  uint16_t timeout = GnG_BLE_HWSPI::BLE_READPACKET_TIMEOUT;
  uint16_t origtimeout = timeout;
  uint16_t replyidx = 0;

  memset(packetbuffer, 0, GnG_BLE_HWSPI::READ_BUFSIZE);

  while (timeout--) {
    if (replyidx >= 20) break;
    if ((packetbuffer[1] == 'A') && (replyidx == GnG_BLE_HWSPI::PACKET_ACC_LEN))
      break;
    if ((packetbuffer[1] == 'G') && (replyidx == GnG_BLE_HWSPI::PACKET_GYRO_LEN))
      break;
    if ((packetbuffer[1] == 'M') && (replyidx == GnG_BLE_HWSPI::PACKET_MAG_LEN))
      break;
    if ((packetbuffer[1] == 'Q') && (replyidx == GnG_BLE_HWSPI::PACKET_QUAT_LEN))
      break;
    if ((packetbuffer[1] == 'B') && (replyidx == GnG_BLE_HWSPI::PACKET_BUTTON_LEN))
      break;
    if ((packetbuffer[1] == 'C') && (replyidx == GnG_BLE_HWSPI::PACKET_COLOR_LEN))
      break;
    if ((packetbuffer[1] == 'L') && (replyidx == GnG_BLE_HWSPI::PACKET_LOCATION_LEN))
      break;

    //    while (ble->available()) {
    //     char c =  ble->read();

    while (internalBLE->available()) {
      char c =  internalBLE->read();

      if (c == '!') {
        replyidx = 0;
      }
      packetbuffer[replyidx] = c;
      replyidx++;
      timeout = origtimeout;
    }

    if (timeout == 0) break;
    delay(1);
  }

  packetbuffer[replyidx] = 0;  // null term

  if (!replyidx)  // no data or timeout
    return 0;
  if (packetbuffer[0] != '!')  // doesn't start with '!' packet beginning
    return 0;

  // check checksum!
  uint8_t xsum = 0;
  uint8_t checksum = packetbuffer[replyidx - 1];

  for (uint8_t i = 0; i < replyidx - 1; i++) {
    xsum += packetbuffer[i];
  }
  xsum = ~xsum;

  // Throw an error message if the checksum's don't match
  if (xsum != checksum)
  {
    Serial.print("Checksum mismatch in packet : ");
    printHex(packetbuffer, replyidx + 1);
    return 0;
  }

  // checksum passed!
  return replyidx;
}

//PacketParser::PacketParser() {
//PacketParser::packetbuffer = new uint8_t[PacketParser::READ_BUFSIZE + 1];
//}