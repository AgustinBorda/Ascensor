#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <eosim/core/entity.hpp>


class Message: public eosim::core::Entity
{
    public:
        Message(int m);
        virtual ~Message();
        int getMessage();

    protected:

    private:
        int msg;
        /*Si es del controlador al ascensor: -1 bajar
                                              0 parar
                                              1 subir*/
        /*Si es del controlador al ascensor, el numero indica en donde esta el ascensor*/
};

#endif // MESSAGE_HPP
