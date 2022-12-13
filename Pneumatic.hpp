#pragma once 
#include "okapi/api.hpp" 
#include "pros/adi.hpp"

using namespace okapi; 

class Pneumatic // class made for Pneumatic Code 
{
    /* ------------------------ Variables ------------------------ */
    pros::ADIDigitalOut piston;
    bool state; 

    /* ------------------------ Methods ------------------------ */
    public: 
        Pneumatic(char iPort, bool initState = false); // constructor for definition class 

        void toggle(); // change to the opposite of the current state of the piston 

        void set(bool iState); // set state of piston

        bool getState() const; // return state of piston 
}; 