#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:
controller Controller1 = controller(primary);

motor lMotorA = motor(PORT13,ratio6_1, true);
motor lMotorB = motor(PORT12, ratio6_1, false);
motor lMotorC = motor(PORT11,ratio6_1, true);

motor_group leftMotors = motor_group(lMotorA, lMotorB, lMotorC);

motor rMotorA = motor(PORT3, ratio6_1, false);
motor rMotorB = motor(PORT2, ratio6_1, true);
motor rMotorC = motor(PORT1, ratio6_1, false);

motor_group rightMotors = motor_group(rMotorA, rMotorB, rMotorC);

inertial inert = inertial(PORT10);

const double wheelTravel = 2.75; 
const double trackWidth = 12; 
const double wheelBase = 10.5 ;

smartdrive drivetrain = smartdrive(leftMotors, rightMotors, inert, wheelTravel, trackWidth, wheelBase, inches);

motor stage1 = motor(PORT4,ratio18_1 ,false); // 5.5w motors = green cartridge 11w
motor stage2 = motor(PORT5, ratio18_1,false);

motor_group intake = motor_group(stage1, stage2);

rotation rSen = rotation(PORT6, false);
motor arm = motor(PORT8, ratio18_1, false);

digital_out clamp1 = digital_out(Brain.ThreeWirePort.C);
digital_out clamp2 = digital_out(Brain.ThreeWirePort.G);

bool clampHold = false;


void vexcodeInit( void ) {
  // nothing to initialize
}