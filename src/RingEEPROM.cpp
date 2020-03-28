/************************************************************************
* The idea of the library is simple. I am  Saving a particular parameters
* into multiple location of the eeprom. Suppose I want to store a variable
* in eeprom. Everytime I want to store the variable, I change my location.
* Thus i am using 4 location for my varibale. By this I am getting, 4 times
* endurance of eeprom for that variable. 

*So for saving value in eeprom, we need two types of buffer 
* 1. Parameter Buffer : This is the intended value we want to store in EEPROM
* 2. Status Buffer: This buffer keeps track of my current location in buffer.
**************************************************************************/


/**************************************************************************
                           Author Information
***************************************************************************
Author : Shuvangkar Shuvo
email: sshuvo93[at]gmail.com
Dhaka, Bangladesh- March 2020
**************************************************************************/


#include "RingEEPROM.h"
#include <EEPROM.h>


//#define EEP_DEBUG
#ifdef EEP_DEBUG
#define debugEep(...) Serial.print(__VA_ARGS__)
#define debugEepln(...) Serial.println(__VA_ARGS__)
#else
#define debugEep(...)   __VA_ARGS__
#define debugEepln(...)  __VA_ARGS__
#endif


RingEEPROM::RingEEPROM(int addrPtr, byte bufSz, byte paramSize)
{
  _initAddr = addrPtr; //First address of the buffer
  _bufSz = bufSz;      //Total number of buffer 
  _paramPacketSz = paramSize;// Total byte in a parameter packet
  //_clrStatusBuf();
}

/*************************************************************
* When status buffer becomes full, this method clears the status buffer
*************************************************************/
void RingEEPROM::_clrStatusBuf()
{
  
  for (byte i = 0; i < _bufSz; i++) {
    EEPROM.write(_initAddr + i, 0);
  }
  debugEepln(F("Status Buf Cleared"));
  //Extra protection is needed here. after setting zero read and check
  // whether all values are zero.
}

/************************************************************
*This methods scan the status buffer and find out the current
*location to write
*************************************************************/
byte RingEEPROM::_getStatusPtr()
{
  byte ptr;
  byte i = 0;
  do
  {
    ptr = EEPROM.read( _initAddr + i);
    //debugEepln(i);
  } while (++i && ptr && (i <= _bufSz));
  return i;
}

/************************************************************
*user call this methods to save the parameter packet
*************************************************************/
void RingEEPROM::savePacket(byte *dataBuf)
{
  byte statusPtr = _getStatusPtr();
  if (statusPtr > _bufSz)
  {
     debugEepln(F("<<<<<<<<<Buf Full>>>>>"));
    _clrStatusBuf();
     //first value of status pointer is 1, zero indicates
     // the location is not used yet
    statusPtr = 1;
  }

  byte index = statusPtr - 1;
  //Status pointer address ends, param pointer address starts
  int paramInitAddr = _initAddr + _bufSz;
  _paramPtr = paramInitAddr + (index * _paramPacketSz);
  //debugEep(F("Data Save Addr: ")); debugEepln(_paramPtr);
  for (byte i = 0; i < _paramPacketSz; i++)
  {
    int addr = _paramPtr + i;
    EEPROM.write(addr, dataBuf[i]);
  }
  EEPROM.write(_initAddr + index, statusPtr); // update status pointer
}

/************************************************************
*user call this methods to read last saved value
*************************************************************/
void  RingEEPROM::readPacket(byte *dataBuf)
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

/************************************************************
*This function retunrs the last address of the complete buffers. 
* So that use can know what is the end pointer for the eeprom object
*************************************************************/
uint16_t RingEEPROM::getBufLastAddr()
{
  uint16_t totalByte = _bufSz + (_bufSz*_paramPacketSz);
  totalByte = _initAddr + totalByte;
  return totalByte;
}

/************************************************************
*Return the current address of EEPROM parameter
*************************************************************/
uint16_t  RingEEPROM::getParamPtr()
{
	return _paramPtr;
}

void RingEEPROM::printStatusBuf()
{
  Serial.print(F("Status Buf: "));
  byte value;
  for (byte i = 0; i < _bufSz; i++)
  {
    value = EEPROM.read( _initAddr + i);
    Serial.print(value); Serial.print("  ");
  }
  Serial.println();
}
void RingEEPROM::printArray(byte *data, byte len)
{
  for (byte i = 0; i < len; i++)
  {
    debugEep(*(data+i)); debugEep("  ");
  }
  debugEepln();
}

void RingEEPROM::populateStatus()
{

  for (byte i = 0; i < _bufSz - 3; i++)
  {
    EEPROM.write(_initAddr + i, i + 1);
  }
}

