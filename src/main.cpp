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

// Delay between every loop during user control loop to prevent
// wasted resources
// (In milliseconds)
const int DELAY = 10;

// Scale for the speed of the base wheels
const float BASE_SPEED_SCALE = 0.60;

// Scales of lift and conveyor
// (each is out of 100)
const int LIFT_SPEED = 50;
const int CONVEYOR_SPEED = 60;
// ---- END GLOBAL VARIABLES ----

// ---- START UTILITY FUNCTIONS ----
// Functions that might be used during autonomous or user-control.

/* Moves the robot forward
 *
 * @param forward is movement is forward
 * @param seconds durations in integer seconds
 * @param percentSpeed percent of current maximum speed (less than 1)
 */
void moveStraight(bool forward, int seconds, int percentSpeed) {
  if (forward) {
    BaseLeft.spin(vex::forward, percentSpeed, percent);
    BaseRight.spin(vex::forward, percentSpeed, percent);
  } else {
    BaseLeft.spin(vex::reverse, percentSpeed, percent);
    BaseRight.spin(vex::reverse, percentSpeed, percent);
  }

  wait(seconds, vex::seconds);

  BaseLeft.stop();
  BaseRight.stop();
}

// ---- END UTILITY FUNCTIONS ----

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
  // Initialize robot configuration
  vexcodeInit();

  // Set brake mode of wheels
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
  // Current actions: Lower lift, move forward, lift a goal, move backward
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
  // current base speed scale: float 0 to 1
  float baseSpeedScale = BASE_SPEED_SCALE;
  Controller1.Screen.print("A: Reset");
  Controller1.Screen.newLine();

  // Continuously loops through all controller input checks
  while (true) {
    Controller1.Screen.clearLine();
    Controller1.Screen.print("Current Speed: ");
    Controller1.Screen.print(baseSpeedScale);

    // Change speed scale
    if (Controller1.ButtonA.pressing()) {
      baseSpeedScale = BASE_SPEED_SCALE;
    } else if (Controller1.ButtonUp.pressing()) {
      baseSpeedScale += 0.10;
    } else if (Controller1.ButtonDown.pressing()) {
      baseSpeedScale -= 0.10;
    } else if (Controller1.ButtonX.pressing()) {
      baseSpeedScale = 1.0;
    }

    // Robot Base control: left and right joysticks
    BaseLeft.spin(forward, Controller1.Axis3.position(percent) * baseSpeedScale,
                  percent);
    BaseRight.spin(
        forward, Controller1.Axis2.position(percent) * baseSpeedScale, percent);

    // Mobile Goal Lift: front right hand buttons
    if (Controller1.ButtonR1.pressing()) {
      Lift.spin(forward, LIFT_SPEED, percent);
    } else if (Controller1.ButtonR2.pressing()) {
      Lift.spin(reverse, LIFT_SPEED, percent);
    } else {
      Lift.stop();
    }

    // Conveyor Control: front left hand buttons
    if (Controller1.ButtonL1.pressing()) {
      Conveyor.spin(forward, CONVEYOR_SPEED, percent);
    } else if (Controller1.ButtonL2.pressing()) {
      Conveyor.spin(reverse, CONVEYOR_SPEED, percent);
    } else {
      Conveyor.stop();
    }
    // waits DELAY duration to prevent wasted resources
    wait(DELAY, msec);
  }
}

// Sets up competition functions and callbacks
int main() {
  // Run pre-autonomous function
  preAutonomous();

  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);

  // Prevent main from returning with an infinite loop
  while (true) {
    wait(100, msec);
  }
}
