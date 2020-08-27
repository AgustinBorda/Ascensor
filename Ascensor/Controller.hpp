#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <eosim/core/entity.hpp>
#include "Elevator.hpp"

class Controller
{
    public:
        Controller();
        Controller(Elevator e);
        virtual ~Controller();
        int getDesiredFloor();
        void setDesiredFloor(int floor);
        int getLastFloor();
        void setLastFloor(int floor);
        Elevator getElevator();
        void setElevator(Elevator e);

    private:
        int desiredFloor;
        int lastFloor;
        Elevator elevator;
};

#endif // CONTROLLER_HPP
