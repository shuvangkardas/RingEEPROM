#include "RingEEPROM.h"
#define FIRST_ADDR 0
#define BUFFER_SIZE 4
#define PARAM_PACKET_SIZE 6

typedef struct sensor_t
{
  float temp;
  float volt;
};
sensor_t sensorWrite,sensorRead;

byte writeBuffer[PARAM_PACKET_SIZE];
byte readBuffer[PARAM_PACKET_SIZE];

RingEEPROM myeepRom(FIRST_ADDR, BUFFER_SIZE, sizeof(sensor_t));

void setup()
{
  Serial.begin(9600);
  Serial.println("Setup Done");
}

void loop()
{
  Serial.println(F("---------------------------------------"));
  myeepRom.printStatusBuf();//Ovserve the inititial state of status buffer

  measureSensor();//populat sensor data in Sensor structure
  //uint8_t 
  myeepRom.savePacket((byte*)&sensorWrite); //Saving data array into eeprom
  Serial.print(F("Param Saved Addr : ")); Serial.println(myeepRom.getParamPtr());
  myeepRom.printStatusBuf();//Ovserve the status buffer after writing a data packet

  myeepRom.readPacket((byte*)&sensorRead);//Read the last saved data packet
  //Print Saved array. match the generated random array and read data array.
  Serial.print(F("Saved  Temp & Volt : "));
  Serial.print(sensorRead.temp);Serial.print(" & ");Serial.println(sensorRead.volt);

  delay(5000);
}

void measureSensor()
{
  Serial.print(F("Measured Temp & Volt : "));
  sensorWrite.temp = random(30,40);
  sensorWrite.volt = random(8,14);
  Serial.print(sensorWrite.temp);Serial.print(" & ");Serial.println(sensorWrite.volt);
}

