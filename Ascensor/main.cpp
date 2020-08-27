#include <iostream>
#include <fstream>
#include "ModeloAscensor.hpp"
#include <eosim/core/experiment.hpp>

const unsigned int repeticiones = 100;

int main ()
{
    std::string s;
    for (int i = 0; i < repeticiones; i++)
    {
        ModeloAscensor m(2);
        eosim::core::Experiment e;
        std::cout << "Arranco ...\n";
        m.connectToExp(&e);
        e.setSeed((unsigned long)i+ 129);
        e.run(10000.0);
        std::cout << '\n';
        m.tEspera.print(1);
        std::cout << '\n';
        m.ocupacionServidor.print(0);
        std :: cout << "Factor de utilizacion de ascensores: " << m.ocupacionServidor.getMean() / (m.dispAscensor1.getMax()+m.dispAscensor2.getMax()) << std :: endl;
        std::cin >> s;
    }
}

