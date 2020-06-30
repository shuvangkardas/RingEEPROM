#ifndef _H_EEP_H_
#define _H_EEP_H_
#include <Arduino.h>

class RingEEPROM
{
  public:
    RingEEPROM(int addrPtr, byte bufSz, byte paramSize);
    void savePacket(byte *dataBuf);
    void readPacket(byte *dataBuf);
    void printStatusBuf();
    void printArray(byte *data, byte len);
    void populateStatus();  
    uint16_t getParamPtr();
    uint16_t getBufLastAddr();
    void _clrStatusBuf();
  private:
    
    byte _getStatusPtr();
    
    int _initAddr;
    byte _bufSz;
    byte _paramPacketSz;

    uint16_t _paramPtr;
    
};

#endif
