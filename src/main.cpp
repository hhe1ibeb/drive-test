/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       elainehou29                                               */
/*    Created:      4/28/2023, 10:42:45 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
controller Controller1 = controller(primary);
motor LFMotor = motor(PORT20, ratio6_1, true);
motor RFMotor = motor(PORT11, ratio6_1, false);
motor LBUMotor = motor(PORT9, ratio6_1, false);
motor RBUMotor = motor(PORT2, ratio6_1, true);
motor LBDMotor = motor(PORT10, ratio6_1, true);
motor RBDMotor = motor(PORT1, ratio6_1, false);


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

int drivePID(){

  return 1;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  vex::task getBlock(drivePID);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

const int deadzone = 5;
bool cmode = true; // 1 tank mode 0 arcade mode

void usercontrol(void) {
  while (1) {
    int left_speed, right_speed;

    if(Controller1.ButtonDown.pressing()){
      cmode = !cmode;
      wait(500, msec);
    }

    if(cmode){
      left_speed = Controller1.Axis3.position(percent) * 5;
      right_speed = Controller1.Axis2.position(percent) * 5;
    } else{
      left_speed = (Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent)) * 5;
      right_speed = (Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent)) * 5;
    }

    if(abs(right_speed) < deadzone) right_speed = 0;
    else if(abs(left_speed) < deadzone) left_speed = 0;

    RFMotor.spin(vex::directionType::fwd, right_speed, rpm);
    RBUMotor.spin(vex::directionType::fwd, right_speed, rpm);
    RBDMotor.spin(vex::directionType::fwd, right_speed, rpm);
    LFMotor.spin(vex::directionType::fwd, left_speed, rpm);
    LBUMotor.spin(vex::directionType::fwd, left_speed, rpm);
    LBDMotor.spin(vex::directionType::fwd, left_speed, rpm);

    wait(20, msec);
  }
}
int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
