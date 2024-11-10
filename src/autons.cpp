#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */

// void drive_test(){
//   chassis.drive_distance(6);
//   chassis.drive_distance(12);
//   chassis.drive_distance(18);
//   chassis.drive_distance(-36);
// }

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

// void turn_test(){
//   chassis.turn_to_angle(5);
//   chassis.turn_to_angle(30);
//   chassis.turn_to_angle(90);
//   chassis.turn_to_angle(225);
//   chassis.turn_to_angle(0);
// }

/**
 * Should swing in a fun S shape.
 */

// void swing_test(){
//   chassis.left_swing_to_angle(90);
//   chassis.right_swing_to_angle(0);
// }

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

// void full_test(){
//   chassis.drive_distance(24);
//   chassis.turn_to_angle(-45);
//   chassis.drive_distance(-36);
//   chassis.right_swing_to_angle(-90);
//   chassis.drive_distance(24);
//   chassis.turn_to_angle(0);
// }

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

// void odom_test(){
//   chassis.set_coordinates(0, 0, 0);
//   while(1){
//     Brain.Screen.clearScreen();
//     Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
//     Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
//     Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
//     Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
//     Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
//     task::sleep(20);
//   }
// }

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

// void tank_odom_test(){
//   odom_constants();
//   chassis.set_coordinates(0, 0, 0);
//   chassis.turn_to_point(24, 24);
//   chassis.drive_to_point(24,24);
//   chassis.drive_to_point(0,0);
//   chassis.turn_to_angle(0);
// }

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

// void holonomic_odom_test(){
//   odom_constants();
//   chassis.set_coordinates(0, 0, 0);
//   chassis.holonomic_drive_to_pose(0, 18, 90);
//   chassis.holonomic_drive_to_pose(18, 0, 180);
//   chassis.holonomic_drive_to_pose(0, 18, 270);
//   chassis.holonomic_drive_to_pose(0, 0, 0);
//}

void on_goal_safe_auto(){
  odom_constants(); 
//   // inert.calibrate(); //ON GOAL SAFE AUTO, Nub going down setup
//   // inert.resetHeading();
  chassis.drive_distance(-16); //drive to first goal closest to us
  chassis.turn_to_angle(-45, 8);
  chassis.drive_distance(-15);
  clamp1.set(true); //clamp down on goal
  clamp2.set(true);
   wait(0.5, sec); //wait on clamp
  intake.spin(reverse, 100, velocityUnits::pct); //score preload
  chassis.turn_to_angle(-80, 8); //turn to ring stack
  chassis.drive_distance(30); //drive and pick up second ring
  chassis.drive_distance(3); //shimmy and shake
  chassis.drive_distance(-3);
  intake.stop();
  chassis.drive_distance(3);
  chassis.drive_distance(-3);
  chassis.drive_distance(3);
  chassis.turn_to_angle(90, 8); //turn for winpoint
  intake.spin(fwd, 100, velocityUnits::pct); //outtake excess ring
  chassis.drive_distance(40); //hit the ladder
}

void off_goal_safe_auto(){
odom_constants(); 
chassis.drive_distance(-10); //drive to first goal closest to us //OFF GOAL SAFE AUTO nub going up setuo
chassis.turn_to_angle(35, 8);
chassis.drive_distance(-17);
clamp1.set(true); //clamp down on goal
clamp2.set(true);
wait(0.5, sec); //wait on clamp
intake.spin(reverse, 100, velocityUnits::pct); //score preload
chassis.turn_to_angle(90, 8); //turn to ring stack
chassis.drive_distance(30); //drive and pick up second ring
chassis.drive_distance(3); //shimmy and shake
chassis.drive_distance(-3);
intake.stop();
chassis.drive_distance(3);
chassis.drive_distance(-3);
chassis.drive_distance(3);
chassis.turn_to_angle(-90, 8); //turn for winpoint
intake.spin(fwd, 100, velocityUnits::pct); //outtake excess ring
chassis.drive_distance(40); //hit the ladder
}
 
void skills_auto(){
  odom.constants();
  chassis.drive_distance(); //drive to first clamp
  clamp1.set(true); //clamp down on goal
  clamp2.set(true);
  wait(0.5, sec); //wait to secure clamp
  chassis.turn_to_angle(); //turn to first close mid ring
  intake.spin(reverse, 100, velocityUnits::pct); //score preload & start intake
chassis.drive_distance(cc ll8ii); //drive to first close mid ring
chassis.turn_to_angle(); //turn to second close mid ring
chassis.drive_distance(); //drive to second close mid ring
chassis.turn_to_angle(); //turn to close double rings
chassis.drive_distance(); //drive to and pick up the rings
chassis.turn_to_angle(); //turn for last ring on this side
chassis.drive_distance(); //drive to last ring
chassis.turn_to_angle(); //line up for corner
chassis.drive_distance(); //go to corner
intake.stop();
clamp1.set(false); //release goal
clamp2.set(false);
chassis.drive distance(); //drive to line up with other goal on close side
chassis.turn_to_angle(); //turn to the angle MAKE SURE CLAMP IS FACING TOWARDS GOAL
chassis.drive_distance(); //drive to goal
clamp1.set(true); //release goal
clamp2.set(true);
wait(0.5, sec);
chassis.turn_to_angle(); //line up with rings
intake.spin(reverse, 100, velocityUnits::pct); //start intake
chassis.drive_distance(); //drive to ring
chassis.turn_to_angle(); //turn to next ring
chassis.drive_distnce(); //drive to ring
chassis.turn_to_angle(); //turn to double ring();
chassis.drive_distance(); //drive through rings
chassis.turn_to_angle(); //turn to penultimate ring
chassis.drive_distance(); //intake penultimate ring
chassis.turn_to_angle(); //turn to ultimate ring
chassis.drive_distance(); //drive to ultimate ring
chassis.drive_distance(); //drive back to corner
clamp1.set(false); //release goal
clamp2.set(false);
chassis.drive_distance(); //get away from corner
}