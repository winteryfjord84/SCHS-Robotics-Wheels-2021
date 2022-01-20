using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group BaseLeft;
extern motor_group BaseRight;
extern motor_group Conveyor;
extern motor_group Lift;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );