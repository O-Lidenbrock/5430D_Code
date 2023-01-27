#pragma once 

#include <iostream> 

class DiscRollerFlywheel
{
    public: 
        static void intakeOut(); 
        static void intakeIn(); 
        static void intakeOff(); 

        static void roller(std::string color); 

        static void flywheelOn();
        static void flywheelOut(); 
        static void flywheelOff(); 
};