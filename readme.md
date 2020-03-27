# Hign Endurance EEEPROM 
## Problem Statement 
In many situation we need to write the EEPROM memory frequently.For an energy meter application, The energy parameter needs  to update frequently in EEPROM to persist the value for a long time. 
Let's Think about a situation. 
I need to write energy value in eeprom after 10s interval.
- total number of writes for one day would be 8640. 
- one month 259.2K 

Atmel AVR microcontroller such as atmega328 ensures EEPROM data reliability  upto 100k write/erase cycle. Oops!! That means we will cross that limit after 11 days. That is very sad. 

One more thing we need to clarify that 100k write/erase cycle for each cell, not for a whole EEPROM memory segment. Here is the point we are going to play with. 

# RingEEPROM Arduino Library

![Arduino EEPROM Endurance, EEPROM Ring buffer](/resources/parallel_o_buffer.png "Parallel  O Buffer | Source: AVR101: High Endurance EEPROM Storage")

For solving the eeprom wear out problem, I have developed an Arduino library  [RingEEPROM]().

## Solution
The idea is simple. I cannot write/erase safely each cell more than 100k times. Suppose I want to store a variable in EEPROM. What I will is, at First I will write the variable in first location, second time I will write the variable in the second location.Third time I will write the variable in the third location, Fourth time I will write the variable in the first location. I am repeating the pattern after 3 locatons. Thus I am getting 3 times endurance for a single variable. 

I will store my value in different cells in each write cycle. So let's consider our buffer size i 8. I am planning to write a byte in EEPROM. As I am using 8 cells for a single byte. Now I get 8*100k = 800k write cycles. That's huge. The bigger buffer size is, the more I get write cycles.  

In this library, I will not store a single variable, I have developed the library such a way so that I can handle any size of buffer. 

So for saving value in eeprom, we need two types of buffer 
 1. Parameter Buffer : This is the intended value we want to store in EEPROM
 2. Status Buffer: This buffer keeps track of my current location in buffer.

For more information please go through the Microchip [application note](http://ww1.microchip.com/downloads/en/appnotes/doc2526.pdf)

License
----
MIT
