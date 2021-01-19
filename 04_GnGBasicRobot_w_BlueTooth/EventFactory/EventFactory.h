#include "Arduino.h"

#ifndef GnGEventFactory_h
#define GnGEventFactory_h

class GnGBLEBaseEvent
{
  protected:
    int decidingNumber; // not used

  public:
    GnGBLEBaseEvent (int inputVal); // not used
    GnGBLEBaseEvent ();
    virtual void printSelf();
    virtual void processEvent();

};

class GnGButtonEvent: public GnGBLEBaseEvent {
  public:
    boolean buttonPressed;
    uint8_t buttonNum;
  public:
    GnGButtonEvent(uint8_t p, boolean b);
    virtual void printSelf();
    virtual void processEvent();
};
#ifdef _Subscribe2Button
extern void GnGbuttonCallBack(GnGButtonEvent* buttonEventptr);
#endif

class GnGColorEvent: public GnGBLEBaseEvent {
  public:
    int red;
    int blue;
    int green;
  public:
    GnGColorEvent(int r, int g, int b);
    virtual void printSelf();
    virtual void processEvent();
};

#ifdef _Subscribe2Color
extern void GnGColorCallBack(GnGColorEvent* colorEventptr);
#endif

class GnGAccEvent: public GnGBLEBaseEvent {
  public:
    float xcoord, ycoord, zcoord;
  public:
    GnGAccEvent(float x, float y, float z);
    virtual void printSelf();
    virtual void processEvent();
};

#ifdef _Subscribe2Acc
extern void GnGAccCallBack(GnGAccEvent* accEventptr);
#endif

class GnGMagEvent: public GnGBLEBaseEvent {
  public:
    float xv, yv, zv;
  public:
    GnGMagEvent(float x, float y, float z);
    virtual void printSelf();
    virtual void processEvent();
};

#ifdef _Subscribe2Other
extern void GnGMagCallBack(GnGMagEvent* magEventptr);
#endif

class GnGGyroEvent: public GnGBLEBaseEvent {
  public:
    float xg, yg, zg;
  public:
    GnGGyroEvent(float x, float y, float z);
    virtual void printSelf();
    virtual void processEvent();
};
#ifdef _Subscribe2Other
extern void GnGGyroCallBack(GnGGyroEvent* magEventptr);
#endif

class GnGQuatEvent: public GnGBLEBaseEvent {
  public:
    float xq, yq, zq, wq;
  public:
    GnGQuatEvent(float x, float y, float z, float w);
    virtual void printSelf();
    virtual void processEvent();
};
#ifdef _Subscribe2Other
extern void GnGQuatCallBack(GnGQuatEvent* magEventptr);
#endif

//***Factory
class GnGBleFactory
{

  public:
    static const int bufsize = 20;
    static float    parsefloat(uint8_t *buffer);
    uint8_t   messageChar[bufsize + 1];
    GnGBleFactory();
    void   setMessage(uint8_t buffer1[bufsize + 1], int len1);
    GnGBLEBaseEvent*   transformMsg2Event();
    void   printMessage(int len1);
};

#endif