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
// LeftBaseMotor        motor         2               
// RightBaseMotor       motor         1               
// LeftLiftMotor        motor         3               
// RightLiftMotor       motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// Global Variables
vex::competition Competition;

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

// Checks for input related to the base of the robot
void baseMovement(void) {
  // Moves the wheels based on the corresponding axis and percent
  LeftBaseMotor.spin(vex::directionType::rev, Controller1.Axis3.position(), vex::velocityUnits::pct);
  RightBaseMotor.spin(vex::directionType::rev, Controller1.Axis2.position(), vex::velocityUnits::pct);
}

void liftMovement(void) {
  // Move the Lift Up
  if (Controller1.ButtonR1.pressing())
  {
    LeftLiftMotor.spin(directionType::rev, 60, velocityUnits::pct);
    RightLiftMotor.spin(directionType::rev, 60, velocityUnits::pct);
  } 
  // Move the Lift Down
  else if (Controller1.ButtonL1.pressing())
  {
    LeftLiftMotor.spin(directionType::fwd, 60, velocityUnits::pct);
    RightLiftMotor.spin(directionType::fwd, 60, velocityUnits::pct);
  }
  // Stop Movement
  else 
  {
    LeftLiftMotor.stop(brakeType::hold);
    RightLiftMotor.stop(brakeType::hold);
  }
}

// Loops through all movement input checks
void userControl(void) {
  while (true) {
    baseMovement();
    liftMovement();

    // prevent wasting resources
    wait(20, msec);
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
