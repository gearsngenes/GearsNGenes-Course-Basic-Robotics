#include "EventFactory.h"
#include "Arduino.h"


GnGBLEBaseEvent::GnGBLEBaseEvent ()
{

}
GnGBLEBaseEvent::GnGBLEBaseEvent (int inputVal)
{
  decidingNumber = inputVal;
}
void GnGBLEBaseEvent::printSelf()
{
  Serial.print("Base Class "); Serial.println (" instance.");
}

 void GnGBLEBaseEvent::processEvent()
{
  // Error if this function is called.
  Serial.println ("**** Base Extern Function");
}

GnGButtonEvent::GnGButtonEvent(uint8_t p, boolean b) {
  buttonPressed = b;
  buttonNum = p;
}
void GnGButtonEvent::printSelf() {
  Serial.print("Button #: ");
  Serial.print(buttonNum);
  if (buttonPressed) {
    Serial.println(" Pressed ");
  } else {
    Serial.println("  RELEASED");
  };
  //  Serial.println(buttonPressed);
}
void GnGButtonEvent::processEvent()
{
#ifdef _Subscribe2Button
  GnGbuttonCallBack(this);
#endif
}

GnGColorEvent::GnGColorEvent(int r, int g, int b) {
  red = r;
  green = g;
  blue = b;
}

void GnGColorEvent::printSelf() {
  Serial.print("ColorEvent- R: ");
  Serial.print(red);
  Serial.print(" G:");
  Serial.print(green);
  Serial.print(" B:");
  Serial.println(blue);
}

void GnGColorEvent::processEvent()
{
#ifdef _Subscribe2Color
  GnGColorCallBack(this);
#endif
}

GnGAccEvent::GnGAccEvent(float x, float y, float z)
{
  xcoord = x;
  ycoord = y;
  zcoord = z;
}

void GnGAccEvent::printSelf() {
    Serial.print("Accel\t");
    Serial.print(xcoord); Serial.print('\t');
    Serial.print(ycoord); Serial.print('\t');
    Serial.print(zcoord); Serial.println();
}
void GnGAccEvent::processEvent()
{
#ifdef _Subscribe2Acc
  GnGAccCallBack(this);
#endif
}

GnGMagEvent::GnGMagEvent(float x, float y, float z)
{
  xv = x;
  yv = y;
  zv = z;
}


void GnGMagEvent::printSelf() {
    Serial.print("MAG EVENT\t");
    Serial.print(xv); Serial.print('\t');
    Serial.print(yv); Serial.print('\t');
    Serial.print(zv); Serial.println();
}

void GnGMagEvent::processEvent()
{
#ifdef _Subscribe2Other
  GnGMagCallBack(this);
#endif
}



GnGGyroEvent::GnGGyroEvent(float x, float y, float z)
{
  xg = x;
  yg = y;
  zg = z;
}



void GnGGyroEvent::printSelf() {
   Serial.print("Gyro\t");
    Serial.print(xg); Serial.print('\t');
    Serial.print(yg); Serial.print('\t');
    Serial.print(zg); Serial.println();
}

void GnGGyroEvent::processEvent()
{
#ifdef _Subscribe2Other
  GnGGyroCallBack(this);
#endif
}



GnGQuatEvent::GnGQuatEvent(float x, float y, float z, float w)
{

  xq = x;
  yq = y;
  zq = z;
  wq = w;
}

void GnGQuatEvent::printSelf() {
   Serial.print("Quat\t");
    Serial.print(xq); Serial.print('\t');
    Serial.print(yq); Serial.print('\t');
    Serial.print(zq); Serial.print('\t');
    Serial.print(wq); Serial.println();
}

void GnGQuatEvent::processEvent()
{
#ifdef _Subscribe2Other
  GnGQuatCallBack(this);
#endif  
}

//********Factory
GnGBleFactory::GnGBleFactory()
{

}
float GnGBleFactory::parsefloat(uint8_t *buffer)
{
  float f;
  memcpy(&f, buffer, 4);
  return f;
}

GnGBLEBaseEvent* GnGBleFactory::transformMsg2Event()
{
  char firstChar = messageChar[1];

  if (firstChar == 'B') {
    uint8_t buttnum = messageChar[2] - '0';
    boolean pressed = messageChar[3] - '0';
   GnGButtonEvent* bevent = new GnGButtonEvent(buttnum, pressed);
    return bevent;
  }
  if (firstChar == 'C') {
    int r = messageChar[2];
    int g = messageChar[3];
    int b = messageChar[4];
    GnGColorEvent* cevent = new GnGColorEvent(r, g, b);
    return cevent;
  }

  if (firstChar == 'A')
  {
    float x = GnGBleFactory:: parsefloat(messageChar + 2);
    float  y = GnGBleFactory:: parsefloat(messageChar + 6);
    float z = GnGBleFactory:: parsefloat(messageChar + 10);
    GnGAccEvent* accevent = new GnGAccEvent(x, y, z);
    return accevent;
  }

  if (firstChar == 'M') {
    float x = GnGBleFactory:: parsefloat(messageChar + 2);
    float  y = GnGBleFactory:: parsefloat(messageChar + 6);
    float z = GnGBleFactory:: parsefloat(messageChar + 10);
    GnGMagEvent* magevent = new GnGMagEvent(x, y, z);
    return magevent;
  }

  if (firstChar == 'G') {

    float x = GnGBleFactory:: parsefloat(messageChar + 2);
    float  y = GnGBleFactory:: parsefloat(messageChar + 6);
    float z = GnGBleFactory:: parsefloat(messageChar + 10);
    GnGGyroEvent* gyroevent = new GnGGyroEvent(x, y, z);
    return gyroevent;
  }
    if (firstChar == 'Q') 
    {
    float x = GnGBleFactory:: parsefloat(messageChar + 2);
    float  y = GnGBleFactory:: parsefloat(messageChar + 6);
    float z = GnGBleFactory:: parsefloat(messageChar + 10);
    float w = GnGBleFactory:: parsefloat(messageChar + 14);   
    GnGQuatEvent* quatevent = new GnGQuatEvent(x, y, z, w);

    return quatevent;
    }
}

void GnGBleFactory::setMessage(uint8_t buffer1[bufsize + 1], int len1)
{
  {
    for (int i = 0; i <= len1; i++)
    {
      messageChar[i] = buffer1[i];
    }
  }

}
void GnGBleFactory::printMessage(int len1)
{
  Serial.println ("Buffer Value from static Member:");
  for (int i = 0; i <= len1; i++)
  {
    char c = messageChar[i];
    Serial.print(c);
  }
  Serial.println();
  Serial.println("Buffer Value from static member...done"); Serial.println();
}