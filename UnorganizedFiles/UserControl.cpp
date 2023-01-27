#include "main.h"
#include "okapi/api/units/QLength.hpp"
#include <string>

void move(double leftFront, double leftBack, double rightFront,
          double rightBack) {
  def::mtr_dt_left_back.moveVelocity(leftBack * 200); // define the motors
  def::mtr_dt_left_front.moveVelocity(leftFront * 200);
  def::mtr_dt_right_back.moveVelocity(rightBack * 200);
  def::mtr_dt_right_front.moveVelocity(rightFront * 200);
}

void moveArcade(double forward, double strafe, double turn) {
  move(forward + strafe + turn, forward - strafe + turn,
       forward - strafe - turn, forward + strafe - turn);
}

void UserControl::usercontrol() {
  while (true) {
    moveArcade(def::controller.getAnalog(ControllerAnalog::rightY),
               def::controller.getAnalog(ControllerAnalog::rightX),
               def::controller.getAnalog(ControllerAnalog::leftX));

    if (def::controller2.getDigital(ControllerDigital::L1))
      DiscRollerFlywheel::flywheelOn();
    else if (def::controller2.getDigital(ControllerDigital::L2))
      DiscRollerFlywheel::flywheelOut();
    else
      DiscRollerFlywheel::flywheelOff();

    if (def::controller2.getDigital(ControllerDigital::R1))
      DiscRollerFlywheel::intakeIn();
    else if (def::controller2.getDigital(ControllerDigital::R2))
      DiscRollerFlywheel::intakeOut();
    else
      DiscRollerFlywheel::intakeOff();

    if (def::controller2.getDigital(ControllerDigital::down))
      def::air.toggle(); 
    else
      def::mtr_move.moveVoltage(0);
  }
}