#include "RingEEPROM.h"
#define FIRST_ADDR 10
#define BUFFER_SIZE 10
#define PARAM_PACKET_SIZE 6

byte writeBuffer[PARAM_PACKET_SIZE];
byte readBuffer[PARAM_PACKET_SIZE];

RingEEPROM myeepRom(FIRST_ADDR, BUFFER_SIZE, PARAM_PACKET_SIZE);

void setup()
{
  Serial.begin(9600);
  Serial.println("Setup Done");
}

void loop()
{
  Serial.println(F("---------------------------------------"));
  myeepRom.printStatusBuf();//Ovserve the inititial state of status buffer
//  byte ptr = myeepRom._getStatusPtr();//get current position 
//  Serial.print(F("Current Status ptr: ")); Serial.println(ptr);

  populateArray(writeBuffer, PARAM_PACKET_SIZE);//Generate a random data array to write
  myeepRom.savePacket(writeBuffer); //Saving data array into eeprom
  Serial.print(F("Param Saved Addr : ")); Serial.println(myeepRom.getParamPtr());
  myeepRom.printStatusBuf();//Ovserve the status buffer after writing a data packet

  myeepRom.readPacket(readBuffer);//Read the last saved data packet
  //Print Saved array. match the generated random array and read data array.
  Serial.print(F("Saved Data : "));
  myeepRom.printArray(readBuffer, PARAM_PACKET_SIZE);

  delay(5000);
}

void populateArray(byte *buffer, byte bufSize)
{
  Serial.print(F("Generated Data : "));
  for (byte i = 0; i < bufSize; i++)
  {
    *(buffer + i) = random(1, 100);
    Serial.print(*(buffer + i) ); Serial.print("  ");
  }
  Serial.println();
}

