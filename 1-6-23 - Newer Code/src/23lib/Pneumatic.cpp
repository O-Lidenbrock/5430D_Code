#include "23lib/Pneumatic.hpp"
#include "main.h"

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
    pros::delay(500);
    state = !state; 
    piston.set_value(state);
    pros::delay(500);
}

// Set state of Piston 
void Pneumatic::set(bool iState)
{
    state = iState; 
    piston.set_value(iState); 
    pros::delay(1000);
}

// Get State of Piston 
bool Pneumatic::getState() const
{
    return state; 
}