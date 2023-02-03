#include "main.h"
#include "okapi/api/units/QLength.hpp"
#include <string>

void move(double leftFront, double leftBack, double rightFront,
          double rightBack) {

  def::mtr_dt_left_front.moveVelocity(leftFront * 200);
  def::mtr_dt_left_back.moveVelocity(leftBack * 200); // define the motors
  def::mtr_dt_right_front.moveVelocity(rightFront * 200);
  def::mtr_dt_right_back.moveVelocity(rightBack * 200);
}

void moveArcade(double forward, double strafe, double turn) {
  move(forward + strafe + turn, forward - strafe + turn,
       forward - strafe - turn, forward + strafe - turn); //order matters
}

void UserControl::usercontrol() {
  while (true) {
    double turnDivisor;
    double rollerSpeed;
    // cap flywheel turn speed: slower first then a faster.:on controller2 slow = LT trigger, fast is X
    // slow intake (for the roller): also controller2

    // toggle turn speed
    if(def::controller.getDigital(ControllerDigital::R1))
    {turnDivisor = 3;}
    else
    {
      turnDivisor = 1;
    }

    //Digital = Buttons - gives True/False
    //Analog = Joysticks - range of numbers between -100 and 100
    
    // define parameters for moveArcade as controller axises 
    moveArcade(def::controller.getAnalog(ControllerAnalog::rightY),
               def::controller.getAnalog(ControllerAnalog::rightX),
               def::controller.getAnalog(ControllerAnalog::leftX)/turnDivisor);

    //flywheel
    if (def::controller2.getDigital(ControllerDigital::L1))
      DiscRollerFlywheel::flywheelOn();
    else if (def::controller2.getDigital(ControllerDigital::L2))
      DiscRollerFlywheel::flywheelOut(-300);
    else if(def::controller2.getAnalog(ControllerDigital::X)){
      DiscRollerFlywheel::flywheelOut(-500);
    }
    else
      DiscRollerFlywheel::flywheelOff();

    //intake & roller
    if(def::controller2.getDigital(ControllerDigital::left)){
      rollerSpeed = 500;
    }
    else{
      rollerSpeed = 1200;
    }

    if (def::controller2.getDigital(ControllerDigital::R1))
      DiscRollerFlywheel::intakeIn(rollerSpeed);
    else if (def::controller2.getDigital(ControllerDigital::R2))
      DiscRollerFlywheel::intakeOut();
    else
      DiscRollerFlywheel::intakeOff();

    if (def::controller2.getDigital(ControllerDigital::down))
      def::air.toggle(); 
      

    if (def::controller2.getDigital(ControllerDigital::B)) {
      def::mtr_move.moveRelative(90.0,90);
    }
    /*else
      okapi::setBrakeMode(mtr_move.hold);
      def::mtr_move.moveVoltage(0);*/
  }
}