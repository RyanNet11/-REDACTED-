#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 89; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}




///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .

//Skills auton program
void skillsAuton() {
 pros::Motor Left1(-14);
 pros::Motor Left2(-2);
 pros::Motor Right1(8);
 pros::Motor Right2(20);
pros::ADIAnalogIn sensor (2);
 pros::Motor_Group Left({Left1,Left2});
 pros::Motor_Group Right({Right1,Right2});
 pros::Motor Catapult(9);
 pros::Motor Catapult_(-1);
 pros::Motor_Group Cata({Catapult, Catapult_});
 pros::ADIDigitalOut Wings (1, LOW);
 pros::Rotation CataPos(10);
 pros::Controller master(pros::E_CONTROLLER_MASTER);
 pros::IMU IMU(12);
 int AutonTimer();
 int i = 0;
  chassis.set_turn_pid(-45, TURN_SPEED); //tuen
  chassis.wait_drive();
  chassis.set_drive_pid(-20, DRIVE_SPEED,true); //drive back
  chassis.wait_drive();
  chassis.set_turn_pid(45, TURN_SPEED); // turn again
  chassis.wait_drive();
  chassis.set_drive_pid(-10, 40,true);
  chassis.set_exit_condition(chassis.drive_exit, 20,  20, 100, 150, 500, 500); //back into bar
  pros::delay(500);
  IMU.set_heading(45);
  pros::delay(500);
  chassis.set_swing_pid(ez::RIGHT_SWING, 32, 30); //swing
  Left.brake();
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, 32, 30); //swing
  chassis.set_drive_pid(-0.2, DRIVE_SPEED,true); //drive back
  chassis.wait_drive();
  chassis.set_drive_brake(pros::E_MOTOR_BRAKE_HOLD);
  Cata.move_voltage(8000);
  chassis.set_drive_pid(-1, 10,true); //drive back
    chassis.set_swing_pid(ez::LEFT_SWING, 31, 30); //swing
    pros::delay(5000);
  chassis.set_swing_pid(ez::LEFT_SWING, 31, 30); //swing
  pros::delay(5000);
  //chassis.set_swing_pid(ez::LEFT_SWING, 31, 30); //swing
 // pros::delay(5000);
 // chassis.set_swing_pid(ez::LEFT_SWING, 31, 30); //swing
 //   pros::delay(5000);
//chassis.set_swing_pid(ez::LEFT_SWING, 31, 30); //swing
 //   pros::delay(5000);
//  chassis.set_swing_pid(ez::LEFT_SWING, 31, 30); //swing
   // pros::delay(5000);
  //chassis.set_swing_pid(ez::LEFT_SWING, 31, 30); //swing
   // pros::delay(5000);
  //chassis.set_swing_pid(ez::LEFT_SWING, 31, 30); //swing
  //pros::delay(5000);
    Cata.move_voltage(0);
  chassis.wait_drive();
    chassis.set_turn_pid(45, TURN_SPEED); //tuen
  chassis.wait_drive();
  chassis.set_drive_pid(60, DRIVE_SPEED,true); //drive back
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, 90, 70); //swing
  chassis.wait_drive();
    chassis.set_swing_pid(ez::LEFT_SWING, 90, 70); //swing

  chassis.set_drive_pid(20, DRIVE_SPEED,true); //drive back
  chassis.wait_drive();

  while(sensor.get_value() > 2790) {
    // drive forward until a line is hit
    chassis.set_drive_pid(-1, 89,true); //drive back
    pros::delay(0.01);
    
  }


  chassis.wait_drive();
    chassis.set_swing_pid(ez::LEFT_SWING, 0, 89); //swing
       chassis.wait_drive();
    chassis.set_turn_pid(0, 89); //tuen
           chassis.wait_drive();
        while(CataPos.get_angle() > 30350){
              Cata.move_voltage(8000); 
              pros::delay(0.2); 
        }
              Cata.move_voltage(0); 

        chassis.set_drive_pid(30, 89,true); //drive back
               chassis.wait_drive();

               Wings.set_value(true);

                       chassis.set_drive_pid(50, 89,true); //drive back
               chassis.wait_drive();

        chassis.set_drive_pid(-30, 89,true); //drive back
               chassis.wait_drive();

        chassis.set_drive_pid(40, 89,true); //drive back
       chassis.wait_drive();


  

}



  




//Defensive zone 2v2 auton program
void defensiveAuton(){

  pros::Motor Catapult(9);
 pros::Motor Catapult_(-1);
 pros::Motor_Group Cata({Catapult, Catapult_});
 pros::ADIDigitalOut Wings (1, LOW);
 pros::Rotation CataPos(10);
 pros::Controller master(pros::E_CONTROLLER_MASTER);
 pros::IMU IMU(12);


//turn the robot towards the goal 
chassis.set_turn_pid(30, TURN_SPEED);
chassis.wait_drive();

//Push the Triball into the goal
chassis.set_drive_pid(24, DRIVE_SPEED);
chassis.wait_drive();

//Back up
chassis.set_drive_pid(-24, DRIVE_SPEED);
chassis.wait_drive();

//turn the robot to the climb bar
chassis.set_turn_pid(120, TURN_SPEED);
chassis.wait_drive();

//move the robot forward onto the climb bar
chassis.set_drive_pid(36, DRIVE_SPEED);
chassis.wait_drive();

//open the wings once the robot is in position
Wings.set_value(true);
}

//Offensive zone 2v2 auton program
void offensiveAuton(){
 pros::Motor Catapult(9);
 pros::Motor Catapult_(-1);
 pros::Motor_Group Cata({Catapult, Catapult_});
 pros::ADIDigitalOut Wings (1, LOW);
 pros::Rotation CataPos(10);
 pros::Controller master(pros::E_CONTROLLER_MASTER);
 pros::IMU IMU(12);

//Turn the robot towards the low goal
chassis.set_turn_pid(-30, TURN_SPEED);
chassis.wait_drive();

 //push the triball into the goal
 chassis.set_drive_pid(24, DRIVE_SPEED);
 chassis.wait_drive();

 //back up
 chassis.set_drive_pid(-24, DRIVE_SPEED);
 chassis.wait_drive();

 //turn the robot back to the climb goal
 chassis.set_turn_pid(-120, TURN_SPEED);
 chassis.wait_drive();

 //move the robot to the bar
 chassis.set_drive_pid(36, DRIVE_SPEED);
 chassis.wait_drive();

//Opens the wings
 Wings.set_value(true);

}
