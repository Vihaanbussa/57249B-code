#include "vex.h"
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Intake               motor         6               
// RightMiddle          motor         1               
// LeftMiddle           motor         17              
// RightBack            motor         18              
// RightFront           motor         10              
// LeftFront            motor         11              
// Rotational           rotation      2               
// Catapult             motor         21              
// LeftBack             motor         20              
// Controller1          controller                    
// Pneumatic            digital_out   B               
// Hang                 digital_out   H               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;
bool turn;
bool cata;



/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to.                                                       */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Specify your drive setup below. There are seven options:
//ZERO_TRACKER, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
//For example, if you are not using odometry, put ZERO_TRACKER below:
ZERO_TRACKER,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(LeftFront, LeftMiddle, LeftBack),

//Right Motors:
motor_group(RightFront, RightMiddle, RightBack),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT14,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.6,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//PAUSE! The rest of the drive constructor is for robot using POSITION TRACKING.
//If you are not using position tracking, leave the rest of the values as they are.

//Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, leave it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

void driveForward(float x) {
  LeftFront.spinFor(forward, x, turns, false);
  RightFront.spinFor(forward, x, turns, false);
  LeftBack.spinFor(forward, x, turns, false);
  RightBack.spinFor(forward, x, turns, false);
  LeftMiddle.spinFor(forward, x, turns, false); 
  RightMiddle.spinFor(forward, x, turns, true);
}
void driveReverse(float x) {
  LeftFront.spinFor(reverse, x, turns, true);
  RightFront.spinFor(reverse, x, turns, true);
  LeftBack.spinFor(reverse, x, turns, true);
  RightBack.spinFor(reverse, x, turns, true);
  LeftMiddle.spinFor(reverse, x, turns, true);
  RightMiddle.spinFor(reverse, x, turns, true);
}
void turnRight(float x){
  LeftFront.spinFor(reverse, x, degrees, false);
  RightFront.spinFor(forward, x, degrees, false);
  LeftMiddle.spinFor(reverse, x, degrees, false);
  RightMiddle.spinFor(forward, x, degrees, false);
  LeftBack.spinFor(reverse, x, degrees, false);
  RightBack.spinFor(forward, x, degrees, true);
}
void turnLeft(float x){
  LeftFront.spinFor(reverse, x, degrees, true);
  RightFront.spinFor(reverse, x, degrees, true);
  LeftMiddle.spinFor(reverse, x, degrees, true);
  RightMiddle.spinFor(reverse, x, degrees, true);
  LeftBack.spinFor(reverse, x, degrees, true);
  RightBack.spinFor(reverse, x, degrees, true);
}

void catapult_shoot(){
  Catapult.spinFor(reverse, 100, degrees);
  cata = true;
  while (cata == true) {
    Catapult.spin(reverse);
    //while (cata == true){
      if (Rotational.position(degrees) <= 0 && cata == true){
        cata = false;
        Catapult.stop();
      }
    //}
  }
}

//piston - boosted
void catapult_shoot_boost(){
  Pneumatic.set(true);
  Catapult.spinFor(reverse, 100, degrees);
  Pneumatic.set(false);
  cata = true;
  while (cata == true) {
    Catapult.spin(reverse);
    if (Rotational.position(degrees) <= 0){
      cata = false;
      Catapult.stop();
    }
  }
}

//piston - boosted-down
void catapult_shoot_boost_down(){
  Pneumatic.set(true);
  Catapult.spinFor(reverse, 100, degrees);
  cata = true;
  while (cata == true) {
    Catapult.spin(reverse);
    if (Rotational.position(degrees) <= 0){
      cata = false;
      Catapult.stop();
    }
  }
}

void setDrivetrainVelocity(float x) {
  RightFront.setVelocity(x, percent);
  RightMiddle.setVelocity(x, percent);
  RightBack.setVelocity(x, percent);
  LeftFront.setVelocity(x, percent);
  LeftMiddle.setVelocity(x, percent);
  LeftBack.setVelocity(x, percent);
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

int current_auton_selection = 4;
bool auto_started = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();
  //sets motor velocities and stopping
  RightFront.setStopping(coast);
  RightMiddle.setStopping(coast);
  RightBack.setStopping(coast);
  LeftFront.setStopping(coast);
  LeftMiddle.setStopping(coast);
  LeftBack.setStopping(coast);
  Catapult.setStopping(hold);
  Intake.setVelocity(100, percent);
  Catapult.setVelocity(100, percent);
  RightFront.setVelocity(100, percent);
  RightMiddle.setVelocity(100, percent);
  RightBack.setVelocity(100, percent);
  LeftFront.setVelocity(100, percent);
  LeftMiddle.setVelocity(100, percent);
  LeftBack.setVelocity(100, percent);
  catapult_shoot();
  
  //switch function for auton selection
  while(auto_started == false){
    Brain.Screen.clearScreen();
    switch(current_auton_selection){
      case 0:
        Brain.Screen.printAt(50, 50, "OffRoller");
        break;
      case 1:
        Brain.Screen.printAt(50, 50, "OnRoller");
        break;
      case 2:
        Brain.Screen.printAt(50, 50, "93 point Skills");
        break;
      case 3:
        Brain.Screen.printAt(50, 50, "Full Skills");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 4){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

void autonomous(void) {
  // 1 tile for drive_distance should have value of 75
  // 90 degree rotation (clockwise with intake facing 12-o'clock) for turn_to_angle should have a value of 100
  auto_started = true;
  switch(current_auton_selection){  
    case 0: //offroller
      
      driveForward(3.5);
      turnRight(-700);
      driveForward(0.85);
      Intake.spinFor(forward, 600, degrees);
      driveForward(-1);
      chassis.turn_to_angle(180);
      catapult_shoot();
  
    break;

    case 1: //on roller
      
      chassis.drive_distance(20);
      Intake.spinFor(forward, 1800, degrees);
      chassis.drive_distance(-25);
      chassis.turn_to_angle(100);
      catapult_shoot();
      
      break;

    case 2: //skills
      RightFront.setVelocity(30, percent);
      RightMiddle.setVelocity(30, percent);
      RightBack.setVelocity(30, percent);
      LeftFront.setVelocity(30, percent);
      LeftMiddle.setVelocity(30, percent);
      LeftBack.setVelocity(30, percent);
      Intake.setVelocity(100, percent);

      turnRight(35);
      catapult_shoot();
      catapult_shoot();
      turnRight(-70);
      driveForward(8);
      turnRight(700);
      driveForward(1.25);
      Intake.setVelocity(100, percent);
      Intake.spinFor(forward, 820, degrees);
      driveForward(-4.5);
      turnRight(-700);
      driveForward(4);
      Intake.spinFor(forward, 800, degrees);
      driveForward(-9);
      turnRight(675);
      driveForward(4);
      driveForward(-15);

      Intake.setVelocity(80, percent);
      RightFront.setVelocity(100, percent);
      RightMiddle.setVelocity(100, percent);
      RightBack.setVelocity(100, percent);
      LeftFront.setVelocity(100, percent);
      LeftMiddle.setVelocity(100, percent);
      LeftBack.setVelocity(100, percent);
      wait(3, sec);
      Pneumatic.set(true);
      wait(0.5, sec);
      Pneumatic.set(false);
      wait(0.5,sec);
      Pneumatic.set(true);
      break;
    case 3: //newskills
      wait(1.5, sec);
      chassis.set_drive_exit_conditions(9, 200, 1000);
      chassis.set_turn_exit_conditions(1, 300, 1000);
      chassis.drive_distance(20);
      Intake.spinFor(forward, 3400, degrees);
      chassis.drive_distance(-25);
      setDrivetrainVelocity(60);
      chassis.turn_to_angle(120);
      Intake.setVelocity(80, percent);
      Intake.spin(reverse),
      setDrivetrainVelocity(30);
      chassis.drive_distance(80);
      setDrivetrainVelocity(100);
      wait(1,sec);
      Intake.stop();
      Intake.setVelocity(100, percent);
      chassis.turn_to_angle(80);
      chassis.drive_distance(47);
      Intake.spinFor(forward, 3700, degrees);
      chassis.drive_distance(-35);
      chassis.turn_to_angle(351);
      chassis.set_drive_exit_conditions(9, 200, 2000);
      setDrivetrainVelocity(70);
      chassis.drive_distance(-150);
      chassis.drive_distance(-45);
      chassis.turn_to_angle(23);
      catapult_shoot();
      chassis.turn_to_angle(-19);
      chassis.drive_distance(128);
      chassis.turn_to_angle(226);
      Intake.spin(reverse);
      setDrivetrainVelocity(50);
      chassis.drive_distance(145);
      setDrivetrainVelocity(70);
      wait(0.5, sec);
      Intake.stop();
      chassis.turn_to_angle(328);
      catapult_shoot_boost();
      chassis.turn_to_angle(215);
      setDrivetrainVelocity(100);
      driveForward(6);
      chassis.turn_to_angle(223);
      setDrivetrainVelocity(1);
      Intake.setVelocity(100, percent);
      Intake.spin(reverse);
      chassis.drive_distance(50);
      chassis.drive_distance(25);
      wait(0.5, sec);
      setDrivetrainVelocity(75);
      chassis.turn_to_angle(278);
      wait(0.5, sec);
      Intake.setVelocity(100, percent);
      Intake.stop();
      chassis.drive_distance(-140);
      
      chassis.turn_to_angle(246.5);
      catapult_shoot();
      chassis.turn_to_angle(280);
      chassis.drive_distance(162);
      chassis.turn_to_angle(180);
      chassis.drive_distance(40);
      Intake.spinFor(forward, 3400, degrees);
      chassis.drive_distance(-90);
      chassis.turn_to_angle(270);
      chassis.drive_distance(92.5);
      Intake.spinFor(reverse, 3400, degrees);
      chassis.drive_distance(-75);
      chassis.turn_to_angle(45);
      //chassis.drive_distance(-60);



      


      


      
      
      //chassis.drive_distance(50);
      //chassis.turn_to_angle(163);
      //chassis.drive_distance(75);

      


      break;
    case 4:
      break;
 }
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

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    
    //sets motor presets needed
    RightFront.setStopping(coast);
    RightMiddle.setStopping(coast);
    RightBack.setStopping(coast);
    LeftFront.setStopping(coast);
    LeftMiddle.setStopping(coast);
    LeftBack.setStopping(coast);
    Intake.setVelocity(100, percent);
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    if (cata == true){
      Catapult.spin(reverse);
      if (Rotational.position(degrees) <= 0){
        cata = false;
        Catapult.stop();
      }
    }

    // Intake (spins the intake | NOT TOGGLE, MUST HOLD)
    if(Controller1.ButtonL1.pressing()){
      Intake.setVelocity(100, percent);
      Intake.spin(reverse);
    }
    else if(Controller1.ButtonL2.pressing()){
      Intake.setVelocity(100, percent);
      Intake.spin(forward);
    }
    else{
      Intake.stop();
    }

    //Catapult (shoots catapult and then it pulls it back down)
    if (Controller1.ButtonR2.pressing()){
      Catapult.spin(reverse);
    }

    if (Controller1.ButtonR1.pressing()){
      cata = true;
    }

    if (Controller1.ButtonX.pressing()){
      Catapult.spinFor(reverse, 180, degrees);
      cata = true;
    }

    // if(Controller1.ButtonA.pressing()){
    //   if(Controller1.ButtonLeft.pressing()){
    //     catapult_shoot_boost();
    //   }  
    // }


    //expansion (makes it so that both ButtonB and ButtonDown must be pressed in order to launch expansion. Used as safety mechanism)
    if (Controller1.ButtonB.pressing()){
      Pneumatic.set(false);
    }

    if (Controller1.ButtonA.pressing()){
        Pneumatic.set(true);
    }

    if (Controller1.ButtonUp.pressing()){
        Hang.set(true);
    }

    if (Controller1.ButtonDown.pressing()){
        Hang.set(false);
    }

    
    //Drivetrain
    //Replace this line with chassis.control_tank(); for tank drive.
    chassis.control_arcade();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
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
