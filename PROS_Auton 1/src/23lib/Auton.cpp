#include "main.h"
#include "okapi/api/units/QLength.hpp"
#include <string>

int velocity = 50;

void autonMove(double leftFront, double leftBack, double rightFront, double rightBack) //will intake a number of rotations from autonMiddle. The motors are operating like servos
{
        def::mtr_dt_left_back.moveRelative(leftBack, velocity); // define the motors
        def::mtr_dt_left_front.moveRelative(leftFront, velocity);
        def::mtr_dt_right_back.moveRelative(rightBack, velocity);
        def::mtr_dt_right_front.moveRelative(rightFront, velocity);
}

void autonMiddle(double forward, double strafe, double turn) //Takes in a number of inches to move forward, strafe, and a number of degrees to turn. Is called every time the robot moves in the auton code
{      
        int encoderUnits = 360;
        double diameter = 4.1; //diameter in inches
        double circumference = 2*3.14159*(diameter/2); //calculates the circumference in inches from the inputed diameter. The estimation for pi could be changed
        double forwardRotations = forward/circumference;
        double strafeRotations = strafe/circumference;
        double robotCircumference = ((2*3.14159)*(17.5/2));/*the circumference*/ //the wheels seem to be 17.5 inches apart, which can then be turned into a circumference of the bot, which then can be turned into a number of rotations to turn a number of degrees
        double rotationsPerDegree = (robotCircumference/diameter)/360; //the circumference can then be divided by the wheel diameter to find the number of rotations to complete a full turn(in place). Then, that number is divided by 360 to find the number of rotations per degree
        double turnRotations = turn*rotationsPerDegree;

        autonMove((forwardRotations + strafeRotations)*encoderUnits + turnRotations, (forwardRotations - strafeRotations)*encoderUnits + turnRotations,
         (forwardRotations - strafeRotations)*encoderUnits - turnRotations, (forwardRotations + strafeRotations)*encoderUnits - turnRotations);
}




void roller(int r)
{
    def::mtr_it_left.moveRelative(r, 50);
    def::mtr_it_right.moveRelative(r, 50);
}

void Auton::autoncontrol() {
    while (true) {
        autonMiddle(-3,0,0);
        roller();
    }
}


