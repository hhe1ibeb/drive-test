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

void usercontrol(void) {
  while (1) {
    int left_y = Controller1.Axis3.position(percent);
    int right_x = Controller1.Axis1.position(percent);

    if(abs(right_x) < deadzone) right_x = 0;
    else if(abs(left_y) < deadzone) left_y = 0;

    RFMotor.spin(vex::directionType::fwd, (left_y-right_x)*5, rpm);
    RBUMotor.spin(vex::directionType::fwd, (left_y-right_x)*5, rpm);
    RBDMotor.spin(vex::directionType::fwd, (left_y-right_x)*5, rpm);
    LFMotor.spin(vex::directionType::fwd, (left_y+right_x)*5, rpm);
    LBUMotor.spin(vex::directionType::fwd, (left_y+right_x)*5, rpm);
    LBDMotor.spin(vex::directionType::fwd, (left_y+right_x)*5, rpm);

    wait(20, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
