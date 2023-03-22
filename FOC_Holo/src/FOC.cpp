#include "v5_vcs.h"
#include "math.h"
#include "..\..\config.h"

using namespace vex;

//////////////////////////////
// motor control & movement //
//////////////////////////////

void move(double leftFront, double leftBack, double rightFront,
          double rightBack){     
    mtr_dt_left_front.spin(fwd, leftFront, pct); // define the motors
    mtr_dt_left_back.spin(fwd, leftBack, pct);
    mtr_dt_right_front.spin(fwd, rightFront, pct);
    mtr_dt_right_back.spin(fwd, rightBack, pct);
}

void moveSOC(double y1, double x1, double turn){

  double angle = inertiaA.heading();
  double x2 = x1 * cos(angle) + y1 * sin(angle);
  double y2 = y1 * cos(angle) - x1 * sin(angle);

    move(y2 + x2 + turn, y2 - x2 + turn,
       y2 - x2 - turn, y2 + x2 - turn); //order matters
}

void motorSetup(){
  mtr_dt_left_front.setStopping(brake);
  mtr_dt_left_back.setStopping(brake);
  mtr_dt_right_front.setStopping(brake);
  mtr_dt_right_back.setStopping(brake);
}

void inertialSetup(){
  inertiaA.calibrate();
  inertiaA.resetHeading();
  inertiaA.resetRotation();
}

void userDrive(){

  motorSetup();
  inertialSetup();

  while (true) {
    double turnDivisor;
    // cap flywheel turn speed: slower first then a faster.:on controller2 slow = LT trigger, fast is X
    // slow intake (for the roller): also controller2

    // toggle turn speed
    if(control1.ButtonR1.pressing())
    {turnDivisor = 3;}
    else
    {
      turnDivisor = 1;
    }

    moveSOC(control1.Axis2.position(),
               control1.Axis1.position(),
               control1.Axis4.position()/turnDivisor);

    wait(10, msec);

  }
}

int main() {
  userDrive();
  return 0;
}

