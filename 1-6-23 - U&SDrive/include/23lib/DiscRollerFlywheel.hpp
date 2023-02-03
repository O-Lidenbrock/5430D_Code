#pragma once 

#include <iostream> 

class DiscRollerFlywheel
{
    public: 
        static void intakeOut(); 
        static void intakeIn(int volts); 
        static void intakeOff(); 

        static void roller(std::string color); 

        static void flywheelBack();
        static void flywheelForward(int speed); 
        static void flywheelOff(); 
};