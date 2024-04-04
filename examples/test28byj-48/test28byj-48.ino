//
// library NewStepper.h
// Simple example of use with 28byj-48 step motor
// move 2048 steps forward (clockwise, right) following by 512 steps backward (counterclockwise, left)
// 
// function used:
// begin() - init the timer library and stepmotor operation mode
// where() - returns the number of steps remainding to stepmotor gets to it's destination
// run()   - cause step motor to move according to parameters informed
// setms() - set the accessible milliseconds counterdown
// getms() - get the state of milliseconds counterdown
// 

#include <NewStepper.h>

NewStepper sm(5,17,16,4);              //define constructor for driver motors pins in1,in2,in3,in4

void setup()
{
  sm.begin(2);                         //define the 28byj-48 step motor mode 2 operation
                                       //1 = full step, 2048 steps per turn, low torque, low consumption
                                       //2 = full step, 2048 steps per turn, high torque, high consumption
                                       //3 = half step, 4096 steps per turn, middle torque, middle consumption

                                       //the max speed depending on mode selected:
                                       //mode 1 - max speed 3 for clockwise and 5 for counterclockwise
                                       //mode 2 - max speed 3 for clockwise and 5 for counterclockwise
                                       //mode 3 - max speed 2 for clockwise and 2 for counterclockwise
}

void loop()
{
  while (sm.where()>0){
    //wait until step motor arrives to its last destination
    //during this wait time, the microcontroller is free to do anything
    }
    
  sm.setms(250);while (sm.getms()>0){
    //wait 500ms
    //setms/getms is the way to wait some amount of time without blocking
    //during this wait time, the microcontroller is free to do anything
    }

  sm.run(2048, 3, true);               //start 2048 steps forward (clockwise, right) 
  while (sm.where()>0){}               //wait until step motor arrives to its last destination
  sm.setms(250);while (sm.getms()>0){} //wait 500ms
  sm.run(2048, 6, false);               //start 512 steps backward (counterclockwise, left) 
}
