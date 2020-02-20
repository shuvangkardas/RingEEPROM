#include "eep.h"
#include <EEPROM.h>


//#define EEP_DEBUG
#ifdef EEP_DEBUG
#define debugEep(...) Serial.print(__VA_ARGS__)
#define debugEepln(...) Serial.println(__VA_ARGS__)
#else
#define debugEep(...)   __VA_ARGS__
#define debugEepln(...)  __VA_ARGS__
#endif


EEProm::EEProm(int addrPtr, byte bufSz, byte paramSize)
{
  _initAddr = addrPtr;
  _bufSz = bufSz;
  _paramPacketSz = paramSize;
  //_clrStatusBuf();
}

void EEProm::_clrStatusBuf()
{
  
  for (byte i = 0; i < _bufSz; i++) {
    EEPROM.write(_initAddr + i, 0);
  }
  debugEepln(F("Status Buf Cleared"));
  //Extra protection is needed here. after setting zero read and check
  // whether all values are zero.
}
byte EEProm::_getStatusPtr()
{
  byte ptr;
  byte i = 0;
  do
  {
    ptr = EEPROM.read( _initAddr + i);
    //debugEepln(i);
  } while (++i && ptr && i <= _bufSz);
  return i;
}

void EEProm::savePacket(byte *dataBuf)
{
  byte statusPtr = _getStatusPtr();
  if (statusPtr > _bufSz)
  {
     debugEepln(F("<<<<<<<<<Buf Full>>>>>"));
    _clrStatusBuf();
    statusPtr = 1;
  }
  byte index = statusPtr - 1;
  int paramInitAddr = _initAddr + _bufSz;
  int paramPtr = paramInitAddr + (index * _paramPacketSz);
  debugEep(F("Data Save Addr: ")); debugEepln(paramPtr);
  for (byte i = 0; i < _paramPacketSz; i++)
  {
    int addr = paramPtr + i;
    EEPROM.write(addr, dataBuf[i]);
  }
  EEPROM.write(_initAddr + index, statusPtr); // update status pointer
}

void  EEProm::readPacket(byte *dataBuf)
{
  byte statusPtr = _getStatusPtr();
  byte index = statusPtr - 2;
  int paramInitAddr = _initAddr + _bufSz;
  int paramPtr = paramInitAddr + (index * _paramPacketSz);
  debugEep(F("Data Read Addr: ")); debugEepln(paramPtr);
  //byte value;
  for(byte i =0 ; i<_paramPacketSz; i++)
  {
    dataBuf[i] = EEPROM.read(paramPtr+i);
    //Serial.print(dataBuf[i]);Serial.print("  ");
  }
  //Serial.println();
}
void EEProm::printStatusBuf()
{
  byte value;
  for (byte i = 0; i < _bufSz; i++)
  {
    value = EEPROM.read( _initAddr + i);
    Serial.print(value); Serial.print("  ");
  }
  Serial.println();
}
void EEProm::printArray(byte *data, byte len)
{
  for (byte i = 0; i < len; i++)
  {
    debugEep(data[i]); debugEep("  ");
  }
  debugEepln();
}

void EEProm::populateStatus()
{

  for (byte i = 0; i < _bufSz - 3; i++)
  {
    EEPROM.write(_initAddr + i, i + 1);
  }
}

