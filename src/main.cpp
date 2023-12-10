#include "main.h"


// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  {-14, -2}

  // Right Chassis Ports (negative port will reverse it!)
  ,{8, 20}

  // IMU Port
  ,12

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!) (or tracking wheel diameter)
  ,2.75

  // Cartridge RPM (or tick per rotation if using tracking wheels)
  ,200

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,0.6

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
S
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
 pros::Motor Catapult(9);
 pros::Motor Catapult_(-1);
 pros::Motor_Group Cata({Catapult, Catapult_});
 pros::ADIDigitalOut Wings (1, LOW);
 pros::Rotation CataPos(10);
 pros::Controller master(pros::E_CONTROLLER_MASTER);
 bool i = false;




void diverControl(){


  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  Wings.set_value(LOW);

  while (true){

      chassis.tank();

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){        //If R2 is being held


    Wings.set_value(HIGH);    //Spread the wings
      
    }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ //If R2 is not being held

      
      Wings.set_value (LOW); //Tuck the wings in 
  }

  //* Runs the catapult functions 

      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ 
        Cata.move_voltage(9000); 

        /**  Runs the normal cycle through function of the catapult while the 
       * L1 button is being pressed.. 
       * 
       * Nothing fancy about this snippet of code, when the button is 
       * held, the motor group will spin!!
      */
      
    }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && CataPos.get_angle() > 30350) {
      Cata.move_voltage(8000); 
      pros::delay(0.2); 

        /**  Runs the last ratchet placement when L2 is being pressed
       * 
       * While the L2 button is being pressed, we first check if the catapult 
       * angle is more than 30350, or 303.50 degrese. This is about where
       * the catapult's third ratchet will click into place, similar to the X 
       * button above. When the value reads false, we assume that the angle is 
       * passed where we need to set the value. While true, we sping the
       * motors at 8000 voltage. The other motors use 9000, however we found
       * that this is too fast for the values to read. Delay is also added to
       * make sure the brin can keep up with the values. The main goal of
       * the L2 setting is for match loading, as the trajectory of the third
       * ratchet when launched is almost perfect.
       */

    }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
      i = true;
      
    }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
      i = false;
    }else if(i == true){
      if(CataPos.get_angle() > 30350) {

          //If the curent angle is greater than 30330, we spin the catapult down untill it hits 30330

          Cata.move_voltage(8000); // Spins the motors
          pros::delay(.1); //delay ensures the catapult doesnt break 

          //The goal of our L2 button program is to be able to pull back the catapult to the normal
          //launching position where the match loads can be loaded into the robot. 
      }
      else if(CataPos.get_angle() < 30360){
        pros::delay(.5);
        Cata.move_voltage(9000);
     }    }
    else
    { 
      Cata.move_voltage(0); 

        /**  STOPS all motors when values read false
       * 
       * When values above read false, such as the angle being less than 
       * a set value, or a button is no longer being pressed, we have 
       * to have a part of the function that stated what to do. We make 
       * the motor group stop at all times the values above are not true
      */

    }

    //Debugging for catapult angle

  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
    master.print(1, 1, "Position: %d", CataPos.get_angle());

    /** During the making of the catapult angle functions,
     * we needed a way to see the curent angle of the cata-
     * rotation sensor. To do this, we mapped the Y button
     * on the controller to print out the angle. This 
     * proved to be essential for our understanding of the 
     * rotation sensor and how it worked.
     * 
    */

  }




  // Skills auton selecter 

  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) ){
    master.print(1, 1, "Starting skillsAuton");
    skillsAuton();

    /** While practicing and testing, it can be easier to
     * have a button to exicute the auton programs. This
     * saves us time and makes the testing prosses more 
     * simplistic. Here we program the UP key on the 
     * controller to print "staring skills auton" and
     * it will start the skills Auton
    */

  }

  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
    master.print(1,1, "Starting Offensive Auton %d");
    offensiveAuton();
  }

  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
    master.print(1,1, "Starting Defensive Auton %d");
    defensiveAuton();
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

