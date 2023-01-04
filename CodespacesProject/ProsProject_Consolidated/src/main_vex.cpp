#include "main.h"

using namespace vex;

/* ------------------------ Drive Motors -------------------------- /
motor mtr_dt_left_front(PORT19, ratio18_1, false);
motor mtr_dt_right_front(PORT18, ratio18_1, true);
motor mtr_dt_right_back(PORT1, ratio18_1, true);
motor mtr_dt_left_back(PORT4, ratio18_1, false);
/ ------------------------ Intake Motors ------------------------- /
motor mtr_it_left(PORT6, ratio18_1, false);
motor mtr_it_right(PORT7, ratio18_1, true);
/ ------------------------ Flywheel Motors ----------------------- /
motor mtr_fw(PORT3, ratio18_1, true);
/ ------------------------ Piston Indexer ------------------------ /
digital_out piston(PORTA, false);
/ ------------------------- Sensors ------------------------- */
encoder track_encoder_forward(PORTG, PORTH, false);
encoder track_encoder_side(PORTE, PORTF, true);
inertial_sensor imu_top(PORT2);
inertial_sensor imu_bottom(PORT5);

/* ----------------------------------------------------------- /
/ Controls /
/ ----------------------------------------------------------- */
controller controller = controller(primary);
controller controller2 = controller(partner);

void pistonToggle()
{
piston.set(true);
task::sleep(200);
piston.set(false);
}

void intakeIn()
{
mtr_it_left.spin(directionType::fwd, 12000, velocityUnits::volt);
mtr_it_right.spin(directionType::fwd, 12000, velocityUnits::volt);
}

void intakeOut()
{
mtr_it_left.spin(directionType::rev, 12000, velocityUnits::volt);
mtr_it_right.spin(directionType::rev, 12000, velocityUnits::volt);
}

void intakeOff()
{
mtr_it_left.stop(brakeType::coast);
mtr_it_right.stop(brakeType::coast);
}

void flywheelOn()
{
mtr_fw.spin(directionType::fwd, 12000, velocityUnits::volt);
}

void flywheelOut() { mtr_fw.spin(directionType::rev, 500, velocityUnits::volt); }

void flywheelOff() { mtr_fw.stop(brakeType::coast); }

void move(double leftFront, double leftBack, double rightFront,
double rightBack)
{
mtr_dt_left_back.spin(directionType::fwd, leftBack * 200, velocityUnits::volt);
mtr_dt_left_front.spin(directionType::fwd, leftFront * 200, velocityUnits::volt);
mtr_dt_right_back.spin(directionType::fwd, rightBack * 200, velocityUnits::volt);
mtr_dt_right_front.spin(directionType::fwd, rightFront * 200, velocityUnits::volt);
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
moveArcade(controller.analog(analog_right_x),
controller.analog(analog_left_y),
controller.analog(analog_left_x));

    if (controller2.get_digital(digital_l1))
        flywheelOn();
    else if (controller2.get_digital(digital_l2))
        flywheelOut();
    else
        flywheelOff();

    if (controller2.get_digital(digital_r1))
        intakeIn();
    else if (controller2.get_digital(digital_r2))
        intakeOut();
    else
        intakeOff();

    while (controller2.get_digital(digital_down)){
        pistonToggle();
        break;
    }
}
}

/**

A callback function for LLEMU's center button.
When this callback is fired, it will toggle line 2 of the LCD text between
"I was pressed!" and "I was released!"
*/
void on_center_button() {
static bool pressed = false;
pressed = !pressed;
if (pressed) {
lcd::print(2, "I was pressed!");
} else {
lcd::print(2, "I was released!");
}
}
/**

Runs initialization code. This occurs as soon as the program is started.
All other competition modes are blocked by initialize; it is recommended
to keep execution time for this mode under a few seconds.
*/
void initialize() {
lcd::initialize();
lcd::set_text(1, "Hello VEX!");
lcd::register_btn1_cb(on_center_button);
}
/**

Runs while the robot is in the disabled state of Field Management System or
the VEX Competition Switch, following either autonomous or opcontrol. When
the robot is enabled, this task will exit.
*/
void disabled() {}
/**

Runs after initialize(), and before autonomous when connected to the Field
Management System or the VEX Competition Switch. This is intended for
competition-specific initialization routines, such as an autonomous selector
on the LCD.
This task will exit when the robot is enabled and autonomous or opcontrol
starts.
*/
void competition_initialize() {}
/**

Runs the user autonomous code. This function will be started in its own task
with the default priority and stack size whenever the robot is enabled via
the Field Management System or the VEX Competition Switch in the autonomous
mode. Alternatively, this function may be called in initialize or opcontrol
for non-competition testing purposes.
If the robot is disabled or communications is lost, the autonomous task
will be stopped. Re-enabling the robot will restart the task, not re-start it
from where it left off.
*/
void autonomous() {}
