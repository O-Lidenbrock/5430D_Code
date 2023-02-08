#include "23lib/DiscRollerFlywheel.hpp"
#include "23lib/definitions.hpp"
#include "main.h"

void DiscRollerFlywheel::intakeIn(int volts) {
  def::mtr_it_left.moveVoltage(volts);
  def::mtr_it_right.moveVoltage(volts);
}

void DiscRollerFlywheel::intakeOut() {
  def::mtr_it_left.moveVoltage(-12000);//-12000 default
  def::mtr_it_right.moveVoltage(-12000);
}

void DiscRollerFlywheel::intakeOff() {
  def::mtr_it_left.moveVoltage(0);
  def::mtr_it_right.moveVoltage(0);
}

void DiscRollerFlywheel::flywheelBack() { 
  def::mtr_fw.moveVelocity(600); //600
}

//default is -500
void DiscRollerFlywheel::flywheelForward(int speed) { def::mtr_fw.moveVelocity(speed); }

void DiscRollerFlywheel::flywheelOff() { def::mtr_fw.moveVoltage(0); }