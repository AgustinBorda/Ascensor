#include "Events.hpp"
#include "ModeloAscensor.hpp"
#include "Message.hpp"
#include <iostream>


FloorFeeder::FloorFeeder(eosim::core::Model& model): BEvent(FloorF, model) {}

FloorFeeder::~FloorFeeder() {}

void FloorFeeder::eventRoutine(eosim::core::Entity* who)
{
    std::cout << "feeder" << std::endl;
    std::cout << "llego un pedido en " << who->getClock() << "\n";
    ModeloAscensor& h = dynamic_cast<ModeloAscensor&>(owner);
    Floor* f = dynamic_cast<Floor*>(who);
    std::cout << "con numero " << f->getFloor() << std::endl;
    h.schedule(h.arribos.sample(),new Floor(),FloorF);
    h.schedule(0.0, who, DumbB);
}

DumbBoard::DumbBoard(eosim::core::Model& model): BEvent(DumbB, model) {}

DumbBoard::~DumbBoard() {}

void DumbBoard::eventRoutine(eosim::core::Entity* who)
{
    std::cout << "tablero" << std::endl;
    ModeloAscensor& h = dynamic_cast<ModeloAscensor&>(owner);
    Floor* f = dynamic_cast<Floor*>(who);
    if(h.dispAscensor1.isAvailable(1))
    {
        std::cout << "tomo ascensor 1 con "<<f->getFloor() << "\n";
        h.ocupacionServidor.log((h.dispAscensor1.getMax()+h.dispAscensor2.getMax())-(h.dispAscensor1.getQuantity()+h.dispAscensor2.getQuantity()));
        h.dispAscensor1.acquire(1);
        h.schedule(0.0,who,con1);
    }
    else
    {
        if(h.dispAscensor2.isAvailable(1))
        {
            std::cout << "tomo ascensor 2 con "<<f->getFloor() << "\n";
            h.tEspera.log(h.getSimTime() - who->getClock());
            h.ocupacionServidor.log((h.dispAscensor1.getMax()+h.dispAscensor2.getMax())-(h.dispAscensor1.getQuantity()+h.dispAscensor2.getQuantity()));
            h.dispAscensor2.acquire(1);
            h.schedule(0.0,who,con2);
        }
        else
        {
            std::cout << "hago cola, con " <<f->getFloor()  << "\n";
            f->setArriveTime(f->getClock());
            h.cola.push(f);
        }
    }
}

// constructor
ControladorAscensor1::ControladorAscensor1(eosim::core::Model& model):BEvent(con1, model) {}
// destructor
ControladorAscensor1::~ControladorAscensor1() {}
// rutina del evento fijo
void ControladorAscensor1::eventRoutine(eosim::core::Entity* who)
{
    std::cout << "controlador" << std::endl;
    ModeloAscensor& h = dynamic_cast<ModeloAscensor&>(owner);
    /*Como el controlador estaba ocioso, si le llega algo le llega del tablero*/
    if(h.controladores[0].getDesiredFloor()==-1)
    {
        Floor* f = dynamic_cast<Floor*>(who);
        h.controladores[0].setDesiredFloor(f->getFloor());
        delete f;
        h.schedule(0.0,new Message(0),mover1);
        //enviamos un mensaje al ascensor para que nos diga donde esta
    }
    else
    {
        Message* msg = dynamic_cast<Message*>(who);

        if(h.controladores[0].getDesiredFloor() > msg->getMessage())
        {
            /*subimos por primera vez*/
            h.schedule(2.0,new Message(1),mover1);
        }
        else
        {
            if(h.controladores[0].getDesiredFloor() < msg->getMessage())
            {
                /*bajamos por primera vez*/
                h.schedule(2.0,new Message(-1),mover1);
            }
            else
            {
                if(h.controladores[0].getDesiredFloor() == msg->getMessage())
                {
                    //paramos
                    h.ocupacionServidor.log((h.dispAscensor1.getMax()+h.dispAscensor2.getMax())-(h.dispAscensor1.getQuantity()+h.dispAscensor2.getQuantity()));
                    h.dispAscensor1.returnBin(1); //devolvemos el recurso del ascensor
                    h.schedule(0.0,new Message(0),mover1);
                    std::cout << "Ascensor 1 para "<<"\n";
                    h.controladores[0].setDesiredFloor(-1);
                    if(!h.cola.empty())
                    {
                        Floor* f = dynamic_cast<Floor*>(h.cola.pop());
                        std::cout << "primero en cola es: "<< f->getFloor()<<"\n";
                        h.tEspera.log(h.getSimTime() - who->getClock());
                        h.schedule(0.0,f,DumbB);
                        std::cout << "Avanza la cola"<< "\n";
                        if(!h.cola.empty())
                        {
                            Floor* f = dynamic_cast<Floor*>(h.cola.pop());
                            std::cout << "primero en cola es: "<< f->getFloor()<<"\n";
                            h.tEspera.log(h.getSimTime() - f->getClock());
                            h.schedule(0.0,f,DumbB);
                            std::cout << "Avanza la cola 1"<< "\n";
                        }
                    }
                }
            }
        }
        delete msg;
    }
}

MoverAscensor1::MoverAscensor1(eosim::core::Model& model):BEvent(mover1, model) {}
// destructor
MoverAscensor1::~MoverAscensor1() {}
// rutina del evento fijo
void MoverAscensor1::eventRoutine(eosim::core::Entity* who)
{
    std::cout << "movimiento" << std::endl;
    ModeloAscensor& h = dynamic_cast<ModeloAscensor&>(owner);
    Message* msg = dynamic_cast<Message*>(who);
    if(msg->getMessage()==1)
    {
        h.controladores[0].getElevator().setActualFloor(h.controladores[0].getElevator().getActualFloor()+1);
        std::cout << "Ascensor 1 sube a "<<h.controladores[0].getElevator().getActualFloor()<<"\n";
        h.schedule(0.0,new Message(h.controladores[0].getElevator().getActualFloor()),con1);
    }
    else
    {
        if(msg->getMessage()==-1)
        {
            h.controladores[0].getElevator().setActualFloor(h.controladores[0].getElevator().getActualFloor()-1);
            std::cout << "Ascensor 1 baja a "<<h.controladores[0].getElevator().getActualFloor()<<"\n";
            h.schedule(0.0,new Message(h.controladores[0].getElevator().getActualFloor()),con1);
        }
        else
        {
            if(!h.dispAscensor1.isAvailable(1))
            {
                h.controladores[0].getElevator().setActualFloor(h.controladores[0].getElevator().getActualFloor());
                h.schedule(0.0,new Message(h.controladores[0].getElevator().getActualFloor()),con1);
                std::cout << "Ascensor 1 en "<<h.controladores[0].getElevator().getActualFloor()<<"\n";
            }
        }
    }
    delete msg;
}


// constructor
ControladorAscensor2::ControladorAscensor2(eosim::core::Model& model):BEvent(con2, model) {}
// destructor
ControladorAscensor2::~ControladorAscensor2() {}
// rutina del evento fijo
void ControladorAscensor2::eventRoutine(eosim::core::Entity* who)
{
    std ::cout << "c2" << std::endl;
    ModeloAscensor& h = dynamic_cast<ModeloAscensor&>(owner);
    /*Como el controlador estaba ocioso, si le llega algo le llega del tablero*/
    if(h.controladores[1].getDesiredFloor()==-1)
    {
        Floor* f = dynamic_cast<Floor*>(who);
        h.controladores[1].setDesiredFloor(f->getFloor());
        delete f;
        h.schedule(0.0,new Message(0),mover2);
        //enviamos un mensaje al ascensor para que nos diga donde esta
    }
    else
    {
        Message* msg = dynamic_cast<Message*>(who);

        if(h.controladores[1].getDesiredFloor() > msg->getMessage())
        {
            /*subimos por primera vez*/
            h.schedule(2.0,new Message(1),mover2);
        }
        else
        {
            if(h.controladores[1].getDesiredFloor() < msg->getMessage())
            {
                /*bajamos por primera vez*/
                h.schedule(2.0,new Message(-1),mover2);
            }
            else
            {
                if(h.controladores[1].getDesiredFloor() == msg->getMessage())
                {
                    //paramos
                    h.ocupacionServidor.log((h.dispAscensor1.getMax()+h.dispAscensor2.getMax())-(h.dispAscensor1.getQuantity()+h.dispAscensor2.getQuantity()));
                    h.dispAscensor2.returnBin(1); //devolvemos el recurso del ascensor
                    //h.schedule(0.0,new Message(0),mover2);
                    std::cout << "Ascensor 2 para "<<"\n";
                    h.controladores[1].setDesiredFloor(-1);
                    if(!h.cola.empty())
                    {
                        Floor* f = dynamic_cast<Floor*>(h.cola.pop());
                        std::cout << "primero en cola es: "<< f->getFloor()<<"\n";
                        h.tEspera.log(h.getSimTime() - f->getArriveTime());
                        h.schedule(0.0,f,DumbB);
                        std::cout << "Avanza la cola 2"<< "\n";
                    }
                }
            }
        }
        delete msg;
    }
}

MoverAscensor2::MoverAscensor2(eosim::core::Model& model):BEvent(mover2, model) {}
// destructor
MoverAscensor2::~MoverAscensor2() {}
// rutina del evento fijo
void MoverAscensor2::eventRoutine(eosim::core::Entity* who)
{
    std::cout << "movimiento" << std::endl;
    ModeloAscensor& h = dynamic_cast<ModeloAscensor&>(owner);
    Message* msg = dynamic_cast<Message*>(who);
    if(msg->getMessage()==1)
    {
        h.controladores[0].getElevator().setActualFloor(h.controladores[1].getElevator().getActualFloor()+1);
        std::cout << "Ascensor 2 sube a "<<h.controladores[1].getElevator().getActualFloor()<<"\n";
        h.schedule(0.0,new Message(h.controladores[1].getElevator().getActualFloor()),con2);
    }
    else
    {
        if(msg->getMessage()==-1)
        {
            h.controladores[0].getElevator().setActualFloor(h.controladores[1].getElevator().getActualFloor()-1);
            std::cout << "Ascensor 2 baja a "<<h.controladores[1].getElevator().getActualFloor()<<"\n";
            h.schedule(0.0,new Message(h.controladores[1].getElevator().getActualFloor()),con2);
        }
        else
        {
            if(!h.dispAscensor2.isAvailable(1))
            {
                h.controladores[0].getElevator().setActualFloor(h.controladores[1].getElevator().getActualFloor());
                h.schedule(0.0,new Message(h.controladores[1].getElevator().getActualFloor()),con2);
                std::cout << "Ascensor 2 en "<<h.controladores[1].getElevator().getActualFloor()<<"\n";
            }
        }
    }
    delete msg;
}


