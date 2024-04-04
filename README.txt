------------------------------------------------------------------------------
This is an ESP-32 nonblocking step motor library based on interrupts for Nema17 and 28byj-48 
By Antonio Testa, April/2024

Special thanks to @gfvalvo from https://forum.arduino.cc who fixed the error: invalid-use-of-non-static-member-function and gave all tricks to use hardware timers inside the library

https://forum.arduino.cc/t/error-invalid-use-of-non-static-member-function/1240240

------------------------------------------------------------------------------
In the main program is mandatory to define the following:

#include <NewStepper.h>     //include the NewStepper.h library                   

NewStepper name(5,17,16,4); //constructor for driver motor pins in1,in2,in3,in4

name.begin(mode);           //At setup(), issue begin() command to init the library timer and set stepmotor mode operation
------------------------------------------------------------------------------

CONSTRUCTOR:

NewStepper name(pin1, pin2, pin3, pin4); 
name is any name for instance stepmotor
uint8_t pin1,2,3,4 reffers to ESP-32 pins connected to in1,2,3,4 of motor driver


METHODS:

name.begin(uint8_t mode);
at setup() section, to init the library timer and step motor model and mode of operation
uint8_t mode should be:
0 = For Nema17, 200 steps per turn
1 = For 28byj-48 full step, 2048 steps per turn, low torque, low consumption
2 = For 28byj-48 full step, 2048 steps per turn, high torque, high consumption
3 = For 28byj-48 half step, 4096 steps per turn, middle torque, middle consumption

name.run(steps,vel,cw);
uint32_t steps is the number of steps to travel
uint8_t vel is the speed (from 2 to ...) higher values lower speed
boolean cw define direction of turn (true for right, clockwise; false for left, counterclockwise)
IMPORTANT: the name.run can only be called if the name.where()==0  

name.where();
retun in an uint32_t value the number of steps remainding to motor arrives to destination
if name.where()==0 means the motor is already in the last destination and is stopped at this moment

name.setms(uint32_t ms);
set the ms counter down (nonblock to be used in substitution of delay function).
As soon as initiated this ms counter is decremented each millisecond

name.getms();
return the ms counter at moment (initial ms value setted by previously name.setms)
------------------------------------------------------------------------------
