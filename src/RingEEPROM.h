#ifndef _H_EEP_H_
#define _H_EEP_H_
#include <Arduino.h>

class RingEEPROM
{
  public:
    RingEEPROM(int addrPtr, byte bufSz, byte paramSize);
    void determineAddr();
    void savePacket(byte *dataBuf);
    void readPacket(byte *dataBuf);
    void printStatusBuf();
    void printArray(byte *data, byte len);
    void populateStatus();
    void _clrStatusBuf();

    byte _getStatusPtr();
    uint16_t getParamPtr();
  private:

    int _initAddr;
    byte _bufSz;
    byte _paramPacketSz;

    uint16_t _paramPtr;
    
};

#endif
