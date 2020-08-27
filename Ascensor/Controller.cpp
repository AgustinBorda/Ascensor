#include "Controller.hpp"

Controller::Controller()
{
    //si el piso deseado esta en -1, quiere decir que el controlador esta ocioso.
    desiredFloor = -1;
    lastFloor = 0;
}

Controller::Controller(Elevator e)
{
    //si el piso deseado esta en -1, quiere decir que el controlador esta ocioso.
    desiredFloor = -1;
    lastFloor = 0;
    elevator = e;
}

Controller::~Controller()
{
    //dtor
}

int Controller::getDesiredFloor()
{
    return desiredFloor;
}

void Controller::setDesiredFloor(int floor) {
    desiredFloor = floor;
}

int Controller::getLastFloor()
{
    return lastFloor;
}

void Controller::setLastFloor(int floor) {
    lastFloor = floor;
}

Elevator Controller::getElevator()
{
    return elevator;
}

void Controller::setElevator(Elevator e) {
    elevator = e;
}
