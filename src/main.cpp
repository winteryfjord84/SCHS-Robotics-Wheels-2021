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
// Conveyor             motor_group   9, 10           
// Lift                 motor_group   11, 12          
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// ---- START GLOBAL VARIABLES ----
vex::competition Competition;

const int DELAY_MS = 10;
// Base wheels speed scaling
const float SPEED_SCALE = 0.60;
// Following two constants are percentages
const int LIFT_SPEED = 50;
const int CONVEYOR_SPEED = 60;
// ---- END GLOBAL VARIABLES ----

// Utility Functions
void moveStraight(bool forward, int seconds, int percentSpeed) {
  if (forward) {
    BaseLeft.spin(vex::forward, percentSpeed, percent);
    BaseRight.spin(vex::forward, percentSpeed, percent);
  } else {
    BaseLeft.spin(vex::forward, percentSpeed, percent);
    BaseRight.spin(vex::forward, percentSpeed, percent);
  }
    wait(seconds, vex::seconds);
    BaseLeft.stop();
    BaseRight.stop();
}


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

void autonomous(void) {
  // Lower lift, move forward, lift a goal, move backward
  Conveyor.spin(reverse, LIFT_SPEED, percent);
  wait(15, seconds);
  Conveyor.stop();
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


void userControl(void) {
  // Loops through all movement input checks
  while (true) {
    // Base Movement
    BaseLeft.spin(forward, Controller1.Axis3.position(percent) * SPEED_SCALE, percent);
    BaseRight.spin(forward, Controller1.Axis2.position(percent) * SPEED_SCALE, percent);

    // Goal Lift
    if (Controller1.ButtonR1.pressing()) {
      Lift.spin(forward, LIFT_SPEED, percent);
    } else if (Controller1.ButtonR2.pressing()) {
      Lift.spin(reverse, LIFT_SPEED, percent);
    } else {
      Lift.stop();
    }

    // Conveyor Control
    if (Controller1.ButtonL1.pressing()) {
      Conveyor.spin(forward, CONVEYOR_SPEED, percent);
    } else if (Controller1.ButtonL2.pressing()) {
      Conveyor.spin(reverse, CONVEYOR_SPEED, percent);
    } else {
      Conveyor.stop();
    }
    
    wait(DELAY_MS, msec);
  }
}

int main() {
  preAutonomous();

  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);

  // Prevent main from returning 
  while (true) {
    wait(100, msec);
  }
}
