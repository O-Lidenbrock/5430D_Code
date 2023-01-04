/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\mcallisters7328                                  */
/*    Created:      Wed Jan 04 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// piston               digital_out   B               
// Controller1          controller                    
// Controller2          controller                    
// mtr_dt_left_front    motor         19              
// mtr_dt_right_front   motor         18              
// mtr_dt_right_back    motor         1               
// mtr_dt_left_back     motor         4               
// mtr_it_left          motor         6               
// mtr_it_right         motor         7               
// mtr_fw               motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

/*
  WARNING: NEED TO CONFIGURE REVERSE OR NOT AND PORTS IF IT IS NOT WORKING 
*/

using namespace vex;

void pistonToggle()
{
piston.set(true);
task::sleep(200);
piston.set(false);
}

void intakeIn()
{
mtr_it_left.spin(directionType::fwd, 12000, volt);
mtr_it_right.spin(directionType::fwd, 12000, volt);
}

void intakeOut()
{
mtr_it_left.spin(directionType::rev, 12000, volt);
mtr_it_right.spin(directionType::rev, 12000, volt);
}

void intakeOff()
{
mtr_it_left.stop(brakeType::coast);
mtr_it_right.stop(brakeType::coast);
}

void flywheelOn()
{
mtr_fw.spin(directionType::fwd, 12000, volt);
}

void flywheelOut() { mtr_fw.spin(directionType::rev, 500, volt); }

void flywheelOff() { mtr_fw.stop(brakeType::coast); }

void move(double leftFront, double leftBack, double rightFront,
double rightBack)
{
mtr_dt_left_back.spin(directionType::fwd, leftBack * 200, volt);
mtr_dt_left_front.spin(directionType::fwd, leftFront * 200, volt);
mtr_dt_right_back.spin(directionType::fwd, rightBack * 200, volt);
mtr_dt_right_front.spin(directionType::fwd, rightFront * 200, volt);
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
moveArcade(Controller1.Axis1.position(percent), Controller1.Axis2.position(percent), Controller1.Axis3.position(percent));

    if (Controller2.ButtonL1.pressing())
        flywheelOn();
    else if (Controller2.ButtonL2.pressing())
        flywheelOut();
    else
        flywheelOff();

    if (Controller2.ButtonR1.pressing())
        intakeIn();
    else if (Controller2.ButtonR2.pressing())
        intakeOut();
    else
        intakeOff();

    while (Controller2.ButtonDown.pressing() && buttonPressed != true){
        buttonPressed 
        pistonToggle();
        break;
    }
}
}
