#include <EEPROM.h>
#include "eep.h"
#define ADDR_PTR 0
#define BUFFER_SIZE 4
#define PACKET_SIZE 3
byte data[6] = {1, 2, 3, 4, 5, 6};
byte dataRead[6];

EEProm myeepRom(10, 10, 6);

void setup()
{
  Serial.begin(9600);
  //populateEEP();
  //myeepRom.populateStatus();

  Serial.println("Done");
//  myeepRom.printStatusBuf();
//  byte ptr = myeepRom._getStatusPtr();
//  Serial.print(F("Status ptr: ")); Serial.println(ptr);

  
}

void loop()
{
  myeepRom.printStatusBuf();
  byte ptr = myeepRom._getStatusPtr();
  Serial.print(F("Status ptr: ")); Serial.println(ptr);
  populateData();
  myeepRom.savePacket(data);
  myeepRom.printStatusBuf();
  myeepRom.readPacket(dataRead);
  Serial.println(F("------------------------"));
  delay(5000);
}

void populateData()
{
  Serial.println(F("Generated Data"));
  for(byte i =0; i<6;i++)
  {
    data[i] = random(1,100);
    Serial.print(data[i]);Serial.print("  ");
  }
  Serial.println();
}

void populateEEP()
{
  //  int currentAdd = STATUS_BUF_START_ADD;
  //  int firstVal = STATUS_BUF_START_ADD+16;
  //  EEPROM.put(currentAdd, firstVal);
  //  EEPROM.put(currentAdd+2, firstVal+1*PARAM_PACKET_SIZE);
  //  EEPROM.put(currentAdd+4, firstVal+2*PARAM_PACKET_SIZE);
  //  EEPROM.put(currentAdd+6, firstVal+3*PARAM_PACKET_SIZE);
  //  EEPROM.put(currentAdd+8, firstVal+4*PARAM_PACKET_SIZE);
  //
  for (byte i = 0; i < 200; i++)
  {
    EEPROM.write(i, 0);
  }
}
