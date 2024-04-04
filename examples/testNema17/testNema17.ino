//
// library NewStepper.h
// Simple example of use with Nema17 step motor
// move 200 steps forward (clockwise, right) following by 50 steps backward (counterclockwise, left)
// 
// function used:
// begin() - init the timer library and stepmotor operation mode
// where() - returns the number of steps remainding to stepmotor gets to it's destination
// run(steps,speed,direction) - cause step motor to move according to parameters informed
// 

#include <NewStepper.h>

NewStepper sm(5,17,16,4);              //define constructor for driver motors pins in1,in2,in3,in4

void setup()
{
  sm.begin(0);                         //define the Nema17 step motor (mode 0)
                                       //max speed 3 for forward (clockwise, right)
                                       //max speed 5 for backward (counterclockwise, left) 
}

void loop()
{
  while (sm.where()>0){
    //wait until step motor arrives to its last destination
    //during this wait time, the microcontroller is free to do anything
    }
    
  sm.setms(500);while (sm.getms()>0){
    //wait 500ms
    //setms/getms is the way to wait some amount of time without blocking
    //during this wait time, the microcontroller is free to do anything
    }

  sm.run(200, 3, true);                //start 200 steps forward (clockwise, right) 
  while (sm.where()>0){}               //wait until step motor arrives to its last destination
  sm.setms(500);while (sm.getms()>0){} //wait 500ms
  sm.run(50, 5, false);                //start 50 steps backward (counterclockwise, left) 
}
