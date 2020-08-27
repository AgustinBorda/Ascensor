#ifndef MODELOASCENSOR_HPP
#define MODELOASCENSOR_HPP
#include <eosim/core/model.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/statics/timeweighted.hpp>
#include <eosim/statics/observation.hpp>
#include"Floor.hpp"
#include "Events.hpp"
#include "Controller.hpp"
#include "Elevator.hpp"

class ModeloAscensor:public eosim::core::Model
{
    public:
        Controller controladores[2];
        ModeloAscensor(double tasaArribos);
        eosim::dist::NegexpDist arribos;
        ~ModeloAscensor();
        // inicializa y registra los atributos del modelo, operacion abstracta de eosim::core::Model
        void init();
        // lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
        void doInitialSchedules();
        eosim::core::Renewable dispAscensor1;
        eosim::core::Renewable dispAscensor2;
        eosim::utils::EntityQueueFifo cola;
        eosim::statics::Observation tEspera;
        eosim::statics::TimeWeighted ocupacionServidor;



    protected:

    private:
        FloorFeeder fF;
        DumbBoard dBoard;
        ControladorAscensor1 c1;
        MoverAscensor1 mov1;
        ControladorAscensor2 c2;
        MoverAscensor2 mov2;

};
#endif // MODELOASCENSOR_HPP
