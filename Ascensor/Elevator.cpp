#include "Elevator.hpp"

Elevator::Elevator()
{
    actualFloor = 0;
}

Elevator::~Elevator()
{
    //dtor
}


int Elevator::getActualFloor()
{
    return actualFloor;
}

void Elevator::setActualFloor(int f)
{
    actualFloor = f;
}
