#ifndef FLOOR_HPP
#define FLOOR_HPP
#include <eosim/core/entity.hpp>


class Floor: public eosim::core::Entity
{
public:
    Floor();
    ~Floor();
    int getFloor();
    double getArriveTime();
    void setArriveTime(double time);

private:
    int floor;
    double arriveTime;
};




#endif // FLOORS_H
