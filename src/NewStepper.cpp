#include "NewStepper.h"

//----------------------------------------------------------------------
NewStepper::NewStepper(uint8_t pin4, uint8_t pin3, uint8_t pin2, uint8_t pin1)
{
  pinMode(pin4,OUTPUT);                              //define the driver motor pins as output
  pinMode(pin3,OUTPUT);                              //
  pinMode(pin2,OUTPUT);                              //
  pinMode(pin1,OUTPUT);                              //

  digitalWrite(pin4,0);                              //initialize then with zeroes
  digitalWrite(pin3,0);                              //
  digitalWrite(pin2,0);                              //
  digitalWrite(pin1,0);                              //

  p4=pin4, p3=pin3, p2=pin2, p1=pin1;                //copy pins to internal variables
}


//----------------------------------------------------------------------
void NewStepper::begin(uint8_t model) {
  xmodel=model;
  const uint8_t timerNumber = 0;
  hw_timer_t *timer1ms = NULL;
  timer1ms = timerBegin(timerNumber, 80, true);
  isrTable[timerNumber] = this;
  auto isr = getIsr(timerNumber);
  timerAttachInterrupt(timer1ms, isr, false);
  timerAlarmWrite(timer1ms, 1000, true);
  timerAlarmEnable(timer1ms);
}


//----------------------------------------------------------------------
void NewStepper::run(uint32_t steps, uint8_t vel, boolean cw)
{
  inivel=vel;xvel=vel;xcw=cw;xsteps=steps;
  if (cw){xfase=-1;}else{xfase=4;}
}


//----------------------------------------------------------------------
uint32_t NewStepper::where()
{
  return xsteps;
}


//----------------------------------------------------------------------
void NewStepper::setms(uint32_t ms){
  xms=ms;
}


//----------------------------------------------------------------------
uint32_t NewStepper::getms() {
  return xms;
}


//----------------------------------------------------------------------
void IRAM_ATTR NewStepper::onTimer1ms()
{
  if (xms>0){xms--;}
  xvel--;
  if (xvel==0){
    xvel=inivel;
    if (xsteps>0){
      int nf=3;if (xmodel==3){nf=7;}
      if (xcw){xfase++;if (xfase>nf){xfase=0;}}else{xfase--;if (xfase<0){xfase=nf;}}
      NewStepper::go();
      xsteps--;
    }
    if (xsteps==0){digitalWrite(p1, 0);digitalWrite(p2, 0);digitalWrite(p3, 0);digitalWrite(p4, 0);}
  }
}

NewStepper *NewStepper::isrTable[SOC_TIMER_GROUP_TOTAL_TIMERS];


//----------------------------------------------------------------------
void NewStepper::go()
{
  switch (xmodel) {
    case 0: NewStepper::move0(); break;   //Nema17, 200 steps
    case 1: NewStepper::move1(); break;   //28byj-48, 2048 steps, full step, low torque, low consumption
    case 2: NewStepper::move2(); break;   //28byj-48, 2048 steps, full step, high torque, high consumption
    case 3: NewStepper::move3(); break;   //28byj-48, 4096 steps, half step, high torque, high consumption
  }
}


//----------------------------------------------------------------------
void NewStepper::move0(){   //Nema17, 200 steps
  switch (xfase) {
    case 0: NewStepper::writ(1,0,1,0); break;   //0x0A
    case 1: NewStepper::writ(0,1,1,0); break;   //0x06
    case 2: NewStepper::writ(0,1,0,1); break;   //0x05
    case 3: NewStepper::writ(1,0,0,1); break;   //0x09
  }
}

void NewStepper::move1(){   //28byj-48, 2048 steps, full step, low torque, low consumption
  switch (xfase) {
    case 0: NewStepper::writ(0,0,0,1); break;   //0x01
    case 1: NewStepper::writ(0,0,1,0); break;   //0x02
    case 2: NewStepper::writ(0,1,0,0); break;   //0x04
    case 3: NewStepper::writ(1,0,0,0); break;   //0x08
  }
}

void NewStepper::move2(){   //28byj-48, 2048 steps, full step, high torque, high consumption
  switch (xfase) {
    case 0: NewStepper::writ(1,0,0,1); break;   //0x09
    case 1: NewStepper::writ(0,0,1,1); break;   //0x03
    case 2: NewStepper::writ(0,1,1,0); break;   //0x06
    case 3: NewStepper::writ(1,1,0,0); break;   //0x0C    
  }
}

void NewStepper::move3(){   //28byj-48, 4096 steps, half step, high torque, high consumption
  switch (xfase) {
    case 0: NewStepper::writ(1,0,0,1); break;   //0x09
    case 1: NewStepper::writ(0,0,0,1); break;   //0x01
    case 2: NewStepper::writ(0,0,1,1); break;   //0x03
    case 3: NewStepper::writ(0,0,1,0); break;   //0x02
    case 4: NewStepper::writ(0,1,1,0); break;   //0x06
    case 5: NewStepper::writ(0,1,0,0); break;   //0x04
    case 6: NewStepper::writ(1,1,0,0); break;   //0x0C
    case 7: NewStepper::writ(1,0,0,0); break;   //0x08
  } 
}


//----------------------------------------------------------------------
void NewStepper::writ(uint8_t px1, uint8_t px2, uint8_t px3, uint8_t px4)
{
  digitalWrite(p1, px1);
  digitalWrite(p2, px2);
  digitalWrite(p3, px3);
  digitalWrite(p4, px4);
}

//----------------------------------------------------------------------


