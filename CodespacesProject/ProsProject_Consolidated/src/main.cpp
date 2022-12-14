// this is WIP, due to consolidation and transfer from okapi to pros. when finished I'll re-upload - Stephen M.
 
#include "main.h"
 
using namespace pros;
 
/* -------------------------- Motors ------------------------- */
Motor mtr_dt_left_front(19);
Motor mtr_dt_right_front(-18);
Motor mtr_dt_right_back(-1);
Motor mtr_dt_left_back(4);
/* ----------------------------------------------------------- */
Motor mtr_it_left(-6);
Motor mtr_it_right(-7);
/* ----------------------------------------------------------- */
Motor mtr_fw(3);
 
Motor mtr_move(-17);
 
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
 
        if (controller2.getDigital(ControllerDigital::L1))
            flywheelOn();
        else if (controller2.getDigital(ControllerDigital::L2))
            flywheelOut();
        else
            flywheelOff();
 
        if (controller2.getDigital(ControllerDigital::R1))
            intakeIn();
        else if (controller2.getDigital(ControllerDigital::R2))
            intakeOut();
        else
            intakeOff();
 
        if (def::controller2.getDigital(ControllerDigital::down))
            air.toggle();
        else
            mtr_move.move_voltage(0);
    }
}
 
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button()
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
}
 
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
    pros::lcd::initialize();
    pros::lcd::set_text(1, "Hello PROS User!");
 
    pros::lcd::register_btn1_cb(on_center_button);
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
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    pros::Motor left_mtr(1);
    pros::Motor right_mtr(2);
 
    while (true)
    {
        pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
                         (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
                         (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
        int left = master.get_analog(ANALOG_LEFT_Y);
        int right = master.get_analog(ANALOG_RIGHT_Y);
 
        left_mtr = left;
        right_mtr = right;
 
        pros::delay(20);
    }
}
 

