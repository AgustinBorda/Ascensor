#include "ModeloAscensor.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>


ModeloAscensor::ModeloAscensor(double tasaArribos):
    fF(*this),
    dBoard(*this),
    c1(*this),
    mov1(*this),
    c2(*this),
    mov2(*this),
    tEspera("Tiempos de Espera"),
    ocupacionServidor("Ocupacion ascensor", *this),
    arribos(eosim::dist::MT19937, tasaArribos),
    dispAscensor1(1,1),
    dispAscensor2(1,1) {
    controladores[0] = Controller(Elevator());
    controladores[1] = Controller(Elevator());
    }

ModeloAscensor::~ModeloAscensor()
{
    //dtor
}

void ModeloAscensor::init()
{
    registerBEvent(&fF);
    registerBEvent(&dBoard);
    registerBEvent(&c1);
    registerBEvent(&mov1);
    registerBEvent(&c2);
    registerBEvent(&mov2);

    registerDist(&arribos);

}

void ModeloAscensor::doInitialSchedules()
{
    schedule(0.0,new Floor(),FloorF);
}
