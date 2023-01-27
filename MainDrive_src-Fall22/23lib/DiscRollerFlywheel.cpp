#include "23lib/DiscRollerFlywheel.hpp"
#include "23lib/definitions.hpp"
#include "main.h"

void DiscRollerFlywheel::intakeIn() {
  def::mtr_it_left.moveVoltage(12000);
  def::mtr_it_right.moveVoltage(12000);
}

void DiscRollerFlywheel::intakeOut() {
  def::mtr_it_left.moveVoltage(-12000);
  def::mtr_it_right.moveVoltage(-12000);
}

void DiscRollerFlywheel::intakeOff() {
  def::mtr_it_left.moveVoltage(0);
  def::mtr_it_right.moveVoltage(0);
}

void DiscRollerFlywheel::flywheelOn() { 
  def::mtr_fw.moveVelocity(600); 
}

void DiscRollerFlywheel::flywheelOut() { def::mtr_fw.moveVelocity(-500); }

void DiscRollerFlywheel::flywheelOff() { def::mtr_fw.moveVoltage(0); }