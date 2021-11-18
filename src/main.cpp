/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\tonyc                                            */
/*    Created:      Tue Sep 28 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// BaseLeft             motor_group   19, 20          
// BaseRight            motor_group   17, 18          
// Lift                 motor         11              
// Conveyor             motor_group   9, 10           
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// Global Variables
vex::competition Competition;

const int DELAY_MS = 10;
// End Global Variables


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void preAutonomous(void) {
  vexcodeInit();
  BaseLeft.setStopping(brake);
  BaseRight.setStopping(brake);
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

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


// Loops through all movement input checks
void userControl(void) {
  while (true) {
    BaseLeft.spin(forward, Controller1.Axis3.position(percent), percent);
    BaseRight.spin(forward, Controller1.Axis2.position(percent), percent);

    if (Controller1.ButtonR1.pressing()) {
      Lift.spin(forward, 70, percent);
    } else if (Controller1.ButtonR2.pressing()) {
      Lift.spin(reverse, 70, percent);
    } else {
      Lift.stop();
    }

    if (Controller1.ButtonL1.pressing()) {
      Conveyor.spin(forward, 75, percent);
    } else if (Controller1.ButtonL2.pressing()) {
      Conveyor.spin(reverse, 75, percent);
    } else {
      Conveyor.stop();
    }
    // Keep iterations constant speed
    wait(DELAY_MS, msec);
  }
}

int main() {
  preAutonomous();

  Competition.drivercontrol(userControl);

  // Prevent main from returning 
  while (true) {
    wait(100, msec);
  }
}
