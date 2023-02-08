#include "v5_vcs.h"
#include "C:\Users\mcallisters7328\Desktop\VSCode\5430D_Code\config.h"

int main() {
    
}

void piston(){
}

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