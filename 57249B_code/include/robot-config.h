using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Intake;
extern motor RightMiddle;
extern motor LeftMiddle;
extern motor RightBack;
extern motor RightFront;
extern motor LeftFront;
extern rotation Rotational;
extern motor Catapult;
extern motor LeftBack;
extern controller Controller1;
extern digital_out Pneumatic;
extern digital_out Hang;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );