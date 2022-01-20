#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor BaseLeftMotorA = motor(PORT19, ratio18_1, true);
motor BaseLeftMotorB = motor(PORT20, ratio18_1, true);
motor_group BaseLeft = motor_group(BaseLeftMotorA, BaseLeftMotorB);
motor BaseRightMotorA = motor(PORT17, ratio18_1, false);
motor BaseRightMotorB = motor(PORT18, ratio18_1, false);
motor_group BaseRight = motor_group(BaseRightMotorA, BaseRightMotorB);
motor ConveyorMotorA = motor(PORT9, ratio18_1, false);
motor ConveyorMotorB = motor(PORT10, ratio18_1, false);
motor_group Conveyor = motor_group(ConveyorMotorA, ConveyorMotorB);
motor LiftMotorA = motor(PORT11, ratio36_1, false);
motor LiftMotorB = motor(PORT12, ratio36_1, true);
motor_group Lift = motor_group(LiftMotorA, LiftMotorB);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}