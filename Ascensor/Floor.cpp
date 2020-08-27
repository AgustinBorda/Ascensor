#include "Floor.hpp"
#include <iostream>
#include <cstdlib>
#include "ModeloAscensor.hpp"
Floor::Floor()
{
    floor = (rand() % 11);
}
Floor::~Floor() {}

int Floor::getFloor()
{
    return floor;
}

double Floor::getArriveTime()
{
    return arriveTime;
}

void Floor::setArriveTime(double t)
{
    arriveTime=t;
}
