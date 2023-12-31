#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Intake = motor(PORT6, ratio6_1, false);
motor RightMiddle = motor(PORT1, ratio6_1, false);
motor LeftMiddle = motor(PORT17, ratio6_1, true);
motor RightBack = motor(PORT18, ratio6_1, true);
motor RightFront = motor(PORT10, ratio6_1, false);
motor LeftFront = motor(PORT11, ratio6_1, true);
rotation Rotational = rotation(PORT2, false);
motor Catapult = motor(PORT21, ratio36_1, true);
motor LeftBack = motor(PORT20, ratio6_1, false);
controller Controller1 = controller(primary);
digital_out Pneumatic = digital_out(Brain.ThreeWirePort.B);
digital_out Hang = digital_out(Brain.ThreeWirePort.H);

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