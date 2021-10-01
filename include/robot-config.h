using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftBaseMotor;
extern motor RightBaseMotor;
extern motor LeftLiftMotor;
extern motor RightLiftMotor;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );