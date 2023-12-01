#include "main.h"


// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-10, -20}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{1, 11}

  // IMU Port
  ,3

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,2.75

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,200

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,0.6


  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({

    Auton("This is skills auton lmao", skillsAuton),

  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 pros::Motor Catapult(-4);
 pros::Motor Catapult_(5);
 pros::Motor_Group Cata({Catapult, Catapult_});
 pros::ADIDigitalOut Wings (1, LOW);
 pros::Rotation CataPos(12);
 pros::Controller master(pros::E_CONTROLLER_MASTER);

  void diverControl(){
    chassis.set_drive_brake(MOTOR_BRAKE_COAST);
    Wings.set_value(LOW);
    while (true){

       chassis.tank();

     if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ //If R2 is being held


     Wings.set_value(HIGH); //Spread the wings
       
     }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ //If R2 is not being held

       
        Wings.set_value (LOW); //Tuck the wings in 
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X) && CataPos.get_angle() > 34400){  //34500
        //^^if X is being pressed and the ratchet angle is greater than 33000
        //this makes sure the ratchet is above the cata launch position


        Cata.move_voltage(9000); //spin the motors untill it slots into the ratchet
        pros::delay(1); // Delay is here to prevent code breaking.. yay C++
       //This part of the code is used for testing and if we need to set the catapult to the
       //middle ratchet for any reason.

      }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ // If L1 is being pressed


          Cata.move_voltage(9000); // Spin the motors
          //This is just the normal spin function of the robot's catapult


      }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && CataPos.get_angle() > 30350) {

        //If the curent angle is greater than 30330, we spin the catapult down untill it hits 30330

        Cata.move_voltage(8000); // Spins the motors
        pros::delay(0.2); //delay ensures the catapult doesnt break 

        //The goal of our L2 button program is to be able to pull back the catapult to the normal
        //launching position where the match loads can be loaded into the robot. 

      }else{ // If nothing is being pressed

        Cata.move_voltage(0); //stop the motors
    
      }
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
      //when the Y button is pressed


      master.print(1, 1, "Position: %d", CataPos.get_angle());
      //use the screen on the controler to print the position of
      //curent catapult position, shown as a 36000-00001

    }
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) ){


        skillsAuton();

    }
    
  }
  }
void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while (true) {

    chassis.tank(); // Tank control
    // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .
    diverControl();
    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
