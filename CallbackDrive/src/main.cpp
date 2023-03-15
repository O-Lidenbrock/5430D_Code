#include "v5_vcs.h"
#include "../../config.h"

using namespace vex;

int main() {

}

//////////////////////////////////////
// flywheel speeds, motors, methods //
//////////////////////////////////////

void intakeIn(double v) {
  mtr_it_left.spin(fwd, v, volt);
  mtr_it_right.spin(fwd, v, volt);
}

void intakeOut() {
  mtr_it_left.spin(fwd, -12, volt);//-12000 default
  mtr_it_right.spin(fwd, -12, volt);
}

void intakeOff() {
  mtr_it_left.spin(fwd, 0, volt);
  mtr_it_right.spin(fwd, 0, volt);
}

void flywheelBack() { 
  mtr_fw.spin(fwd, 6, volt); //600
}

//default is -500
void flywheelForward(double speed) { mtr_fw.spin(fwd, speed, volt); }

void flywheelOff() { mtr_fw.spin(fwd, 0, volt); }


//////////////////////////////////
// pneumatics and piston toggle //
//////////////////////////////////


// Set opposite state of piston 
void toggle()
{
    piston.open();
    wait(800, msec); // was 800 before
    piston.close();
}

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

void moveArcade(double forward, double strafe, double turn){
    move(forward + strafe + turn, forward - strafe + turn,
       forward - strafe - turn, forward + strafe - turn); //order matters
}

void userDrive(){

  while (true) {
    double turnDivisor;
    double rollerSpeed;
    // cap flywheel turn speed: slower first then a faster.:on controller2 slow = LT trigger, fast is X
    // slow intake (for the roller): also controller2

    // toggle turn speed
    if(control1.ButtonR1.pressing())
    {turnDivisor = 3;}
    else
    {
      turnDivisor = 1;
    }

    //Digital = Buttons - gives True/False
    //Analog = Joysticks - range of numbers between -100 and 100
    
    // define parameters for moveArcade as controller axises 
    moveArcade(control1.Axis1.position(),
               control1.Axis2.position(),
               control1.Axis3.position()/turnDivisor);
    

    //flywheel
    if (control2.ButtonL2.pressing())
      flywheelBack();
    else if (control2.ButtonL1.pressing())
      flywheelForward(-200);
    else if(control2.ButtonX.pressing()){
      flywheelForward(-500);
    }
    else
      flywheelOff();

    //intake & roller
    if(control2.ButtonLeft.pressing()){
      rollerSpeed = 900;
    }
    else{
      rollerSpeed = 12;
    }

    if (control2.ButtonR1.pressing())
      intakeIn(rollerSpeed);
    else if (control2.ButtonR2.pressing())
      intakeOut();
    else
      intakeOff();

    if (control2.ButtonDown.pressing())
      toggle(); 
      

    if (controller2.getDigital(ControllerDigital::B)) {
      mtr_move.spinTo(90.0, deg, 50, pct, false/*will need to look up this keyword: https://api.vexcode.cloud/v5/search/bool%20vex::motor::spinTo(double%20rotation,%20rotationUnits%20units,%20double%20velocity,%20velocityUnits%20units_v,%20bool%20waitForCompletion=true)/vex::motor/function*/);
    }
    /*else
      okapi::setBrakeMode(mtr_move.hold);
      def::mtr_move.moveVoltage(0);*/
  }
}
}
