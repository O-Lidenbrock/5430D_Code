#include "v5_vcs.h"
#include "././config.h"

using namespace vex;

int main() {

}

void piston(){
}

void move(double leftFront, double leftBack, double rightFront, //flatten these numbers with the curve here: https://www.desmos.com/calculator/rerhnlaim4

//////////////////////////////////////
// flywheel speeds, motors, methods //
//////////////////////////////////////

void intakeIn(double volts) {
  mtr_it_left.spin(forward, volts, volt);
  mtr_it_right.spin(volts);
}

void intakeOut() {
  mtr_it_left.spin(-12000);//-12000 default
  mtr_it_right.moveVoltage(-12000);
}

void intakeOff() {
  mtr_it_left.moveVoltage(0);
  mtr_it_right.moveVoltage(0);
}

void flywheelBack() { 
  mtr_fw.moveVelocity(600); //600
}

//default is -500
void flywheelForward(int speed) { def::mtr_fw.moveVelocity(speed); }

void flywheelOff() { def::mtr_fw.moveVoltage(0); }


//////////////////////////////////
// pneumatics and piston toggle //
//////////////////////////////////

// Constructor 
Pneumatic::Pneumatic(char iPort, bool initState) : piston(iPort), state(initState)
{
    piston.set_value(state);
}

// Set opposite state of piston 
void Pneumatic::toggle()
{
    state = !state; 
    piston.set_value(state);
    sleep(800); // was 800 before
    state = !state; 
    piston.set_value(state);
}

// Set state of Piston 
void Pneumatic::set(bool iState)
{
    state = iState; 
    piston.set_value(iState); 
    sleep(1000);
}

// Get state of Piston 
bool Pneumatic::getState() const
{
    return state; 
}


//////////////////////////////
// motor control & movement //
//////////////////////////////

void move(double leftFront, double leftBack, double rightFront,
          double rightBack){     
    mtr_dt_left_front.setVelocity(leftFront, percent); // define the motors
    mtr_dt_left_back.setVelocity(leftBack, percent);
    mtr_dt_right_front.setVelocity(rightFront, percent);
    mtr_dt_right_back.setVelocity(rightBack, percent);
}

void moveArcade(double forward, double strafe, double turn){
    move(forward + strafe + turn, forward - strafe + turn,
       forward - strafe - turn, forward + strafe - turn); //order matters
}

void userDrive(){
       moveArcade(controller1.getAnalog(rightY),
               controller1.getAnalog(rightX),
               controller1.getAnalog(leftX)/turnDivisor);
}

void intakeIn(int speed){
    mtr_it_left.spin()
}