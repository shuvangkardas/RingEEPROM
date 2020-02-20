#ifndef _H_EEP_H_
#define _H_EEP_H_
#include <Arduino.h>

class EEProm
{
  public:
    EEProm(int addrPtr, byte bufSz, byte paramSize);
    void determineAddr();
    void savePacket(byte *dataBuf);
    void readPacket(byte *dataBuf);
    void printStatusBuf();
    void printArray(byte *data, byte len);
    void populateStatus();
    byte _getStatusPtr();
    void _clrStatusBuf();
  private:

    int _initAddr;
    byte _bufSz;
    byte _paramPacketSz;
    
};

#endif
