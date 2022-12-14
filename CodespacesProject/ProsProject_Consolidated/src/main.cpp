// this is WIP, due to consolidation and transfer from okapi to pros. when finished I'll re-upload - Stephen M.
 
#include "main.h"
 
using namespace pros;
 
/* ------------------------ Drive Motors -------------------------- */
Motor mtr_dt_left_front(19);
Motor mtr_dt_right_front(-18);
Motor mtr_dt_right_back(-1);
Motor mtr_dt_left_back(4);
/* ------------------------ Intake Motors ------------------------- */
Motor mtr_it_left(-6);
Motor mtr_it_right(-7);
/* ------------------------ Flywheel Motors ----------------------- */
Motor mtr_fw(3);  
/* ------------------------ Piston Indexer ------------------------ */
ADIDigitalOut piston ('A', false);
/* ------------------------- Sensors ------------------------- */
ADIEncoder track_encoder_forward('G', 'H', false);
ADIEncoder track_encoder_side('E', 'F', true);
pros::Imu imu_top(2);
pros::Imu imu_bottom(5);
 
/* ----------------------------------------------------------- */
/*                           Controls                          */
/* ----------------------------------------------------------- */
Controller controller = CONTROLLER_MASTER;
Controller controller2 = E_CONTROLLER_PARTNER;

void pistonToggle()
{
    piston.set_value(true);
    delay(200);
    piston.set_value(false);
}
 
void intakeIn()
{
    mtr_it_left.move_voltage(12000);
    mtr_it_right.move_voltage(12000);
}
 
void intakeOut()
{
    mtr_it_left.move_voltage(-12000);
    mtr_it_right.move_voltage(-12000);
}
 
void intakeOff()
{
    mtr_it_left.move_voltage(0);
    mtr_it_right.move_voltage(0);
}
 
void flywheelOn()
{
    mtr_fw.move_voltage(12000);
}
 
void flywheelOut() { mtr_fw.move_voltage(-500); }
 
void flywheelOff() { mtr_fw.move_voltage(0); }
 
void move(double leftFront, double leftBack, double rightFront,
          double rightBack)
{
    mtr_dt_left_back.move_voltage(leftBack * 200); // define the motors
    mtr_dt_left_front.move_voltage(leftFront * 200);
    mtr_dt_right_back.move_voltage(rightBack * 200);
    mtr_dt_right_front.move_voltage(rightFront * 200);
}
 
void moveArcade(double forward, double strafe, double turn)
{
    move(forward + strafe + turn, forward - strafe + turn,
         forward - strafe - turn, forward + strafe - turn);
}
 
void usercontrol()
{
    while (true)
    {
        moveArcade(controller.get_analog(ANALOG_RIGHT_X),
                   controller.get_analog(ANALOG_LEFT_Y),
                   controller.get_analog(ANALOG_LEFT_X));
 
        if (controller2.get_digital(DIGITAL_L1))
            flywheelOn();
        else if (controller2.get_digital(DIGITAL_L2))
            flywheelOut();
        else
            flywheelOff();
 
        if (controller2.get_digital(DIGITAL_R1))
            intakeIn();
        else if (controller2.get_digital(DIGITAL_R2))
            intakeOut();
        else
            intakeOff();
 
        while (controller2.get_digital(DIGITAL_DOWN)){
            pistonToggle();
            break;
        }
    }
}
 
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
/* void on_center_button()
{
    static bool pressed = false;
    pressed = !pressed;
    if (pressed)
    {
        pros::lcd::set_text(2, "I was pressed!");
    }
    else
    {
        pros::lcd::clear_line(2);
    }
} */
 
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
    pros::lcd::initialize();
}
 
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}
 
/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
 
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
void autonomous() {}
 
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
void opcontrol()
{
    Controller master(E_CONTROLLER_MASTER);
    Motor left_mtr(1);
    Motor right_mtr(2);
 
    while (true)
    {
        pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
                         (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
                         (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		
        int left = master.get_analog(ANALOG_LEFT_Y);
        int right = master.get_analog(ANALOG_RIGHT_Y);
 
        left_mtr = left;
        right_mtr = right;
 
        delay(20);
    }
}
 


// ------------------- Autonomous Code -------------------//

/* This is sudo-code for now. ~Stephen

Robot wheel configuration: 

NW  / \ NE
SW  \ / SE

therefore,

mtr_dt_left_front(19) = NW
mtr_dt_right_front(-18); = NE
mtr_dt_right_back(-1); = SE
mtr_dt_left_back(4); = SW


void auton()
{

}


void autonMiddle(double forward, double strafe, double turn)
{       
        double diameter = 4.1; //diameter in inches
        double circumference = 2*3.14159*(diameter/2); //calculates the circumference in inches from the inputed diameter. The estimation for pi could be changed
        double forwardRotations = forward/circumference;
        double strafeRotations = strafe/circumference;
        double robotCircumference = ((2*3.14159)*(17.5/2));/*the circumference*/ //the wheels seem to be 17.5 inches apart, which can then be turned into a circumference of the bot, which then can be turned into a number of rotations to turn a number of degrees
/*        double rotationsPerDegree = (robotCircumference/diameter)/360; //the circumference can then be divided by the wheel diameter to find the number of rotations to complete a full turn(in place). Then, that number is divided by 360 to find the number of rotations per degree
        double turnRotations = turn*rotationsPerDegree;

        autonMove(forwardRotations + strafeRotations + turnRotations, forwardRotations - strafeRotations + turnRotations,
         forwardRotations - strafeRotations - turnRotations, forwardRotations + strafeRotations - turnRotations);
}


void autonMove(double leftFront, double leftBack, double rightFront, double rightBack) //will intake a number of rotations from autonMiddle. The motors are operating like servos
{

}
*/