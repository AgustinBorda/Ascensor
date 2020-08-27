#ifndef EVENTS_HPP
#define EVENTS_HPP
#include <iostream>
#include <eosim/core/bevent.hpp>

const std::string FloorF = "FloorFeeder";

class FloorFeeder: public eosim::core::BEvent {
    public:
    // constructor
	FloorFeeder(eosim::core::Model& model);
	// destructor
	~FloorFeeder();
	// rutina del evento fijo
    void eventRoutine(eosim::core::Entity* who);
};

const std::string DumbB = "DumbBoard";

class DumbBoard: public eosim::core::BEvent {
    public:
    // constructor
	DumbBoard(eosim::core::Model& model);
	// destructor
	~DumbBoard();
	// rutina del evento fijo
    void eventRoutine(eosim::core::Entity* who);
};

const std::string con1 = "ControladorAscensor1";

class ControladorAscensor1: public eosim::core::BEvent {
    public:
    // constructor
	ControladorAscensor1(eosim::core::Model& model);
	// destructor
	~ControladorAscensor1();
	// rutina del evento fijo
    void eventRoutine(eosim::core::Entity* who);
};

const std::string mover1 = "MoverAscensor1";

class MoverAscensor1: public eosim::core::BEvent {
    public:
    // constructor
	MoverAscensor1(eosim::core::Model& model);
	// destructor
	~MoverAscensor1();
	// rutina del evento fijo
    void eventRoutine(eosim::core::Entity* who);
};


const std::string con2 = "ControladorAscensor2";

class ControladorAscensor2: public eosim::core::BEvent {
    public:
    // constructor
	ControladorAscensor2(eosim::core::Model& model);
	// destructor
	~ControladorAscensor2();
	// rutina del evento fijo
    void eventRoutine(eosim::core::Entity* who);
};

const std::string mover2 = "MoverAscensor2";

class MoverAscensor2: public eosim::core::BEvent {
    public:
    // constructor
	MoverAscensor2(eosim::core::Model& model);
	// destructor
	~MoverAscensor2();
	// rutina del evento fijo
    void eventRoutine(eosim::core::Entity* who);
};


#endif // EVENTS_HPP
