#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP


class Elevator
{
    public:
        Elevator();
        virtual ~Elevator();
        int getActualFloor();
        void setActualFloor(int f);

    private:
        int actualFloor;
};

#endif // ELEVATOR_HPP
