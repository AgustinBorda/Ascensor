#include "Message.hpp"

Message::Message(int m)
{
    msg = m;
}

Message::~Message()
{
    //dtor
}

int Message::getMessage() {
    return msg;
}
