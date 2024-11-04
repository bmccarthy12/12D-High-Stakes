using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:

extern smartdrive drivetrain;

extern controller Controller1;

extern motor stage1;
extern motor stage2;
extern motor_group intake;

extern digital_out clamp1;
extern digital_out clamp2;
extern bool clampHold;

extern motor lMotorA;
extern motor lMotorB;
extern motor lMotorC;
extern motor_group leftMotors;

extern motor rMotorA;
extern motor rMotorB;
extern motor rMotorC;
extern motor_group rightMotors;

extern rotation rSen;
extern motor arm;
extern inertial inert;






void  vexcodeInit( void );