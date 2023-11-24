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
  ,5

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

    Auton("Offensive Zone Auton", Offensive_Zone_Auton),
    Auton("Push Auton", Push_Auton),
    Auton("N/A", No_Movement),
    Auton("Match Auton Shoot", MatchAuton),

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

  //Defines robot electronics ports:

  pros::Motor Catapult(4);
  pros::Motor Catapult_(5);


  pros::ADIDigitalOut Wings (1, LOW);


  pros::Rotation CataPosition (12);


  void driverControl(){

   

    pros::Motor Catapult(4);
    pros::Motor Catapult_(5); //Both Cata Motors 


    pros::ADIDigitalOut Wings (1, LOW); //pneumatics 


    pros::Rotation CataPosition (12); //Rotation Sensor

    chassis.set_drive_brake(MOTOR_BRAKE_COAST);

    Wings.set_value(LOW);

    CataPosition.set_position(359);

    while (true){

       chassis.tank();

     if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ //If R2 is being held


     Wings.set_value(HIGH); //Spread the wings
       
     }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ //If R2 is not being held

       
        Wings.set_value (LOW); //Tuck the wings in 
    }

          //Controls for the Catapult
    //if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){ //If L2 is being held


     //Catapult.move_voltage(-9000); //Spin the catapult at 100% speed
     //Catapult_.move_voltage(9000); //Spin second motor at the opposite speed

    //}else{ //If L2 isn't being held


      //Catapult.move_voltage(0); //Stop the catapult
      //Catapult_.move_voltage(0); //Stop the catapult second motor
      //first ratchet 342 (335 to set) beginning
      //Second ratchet 325 (320 to set) correct
      //third ratchet 307 (300 to set) last


    //}
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
      while (CataPosition.get_angle() > 320){
      Catapult.move_voltage(-1000);
      Catapult_.move_voltage(1000);
      pros::delay(20);
      }
    }else{
      Catapult.move_voltage(0);
      Catapult_.move_voltage(0);
    }
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
      if (CataPosition.get_angle() > 358){
      Catapult.move_voltage(-1000);
      Catapult_.move_voltage(1000);
      }
    }else{      
      Catapult.move_voltage(0);
      Catapult_.move_voltage(0);
      }
    }

    
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){

      Offensive_Zone_Auton();

    }

    }

  
 //  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){ //If Left D-PAD is pressed

 //    Offensive_Zone_Auton(); //Run the Offensive Zone Autonomous code 

 //  }

 //  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){ //If Right D-PAD is pressed

 //    Defensive_Zone_Auton(); //Run the Defensive Zone Autonomous code

 //  }

 //  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){ //If the Up Button is pressed

 //    Skills_Auton(); //Run the Skills Autonomous code








  


void opcontrol() {
  // This is preference to what you like to drive on.

  while (true) {

  pros::Motor Catapult(4);
  



  pros::ADIDigitalOut Wings (1, LOW);


  pros::Rotation CataPosition (12);


    chassis.tank(); // Tank control
    // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .

  


  //Controls for the controller

      //Controls for Wing Mech

    driverControl();






    

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}

