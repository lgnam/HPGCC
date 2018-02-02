#include <iostream>

#include "hpgcc.hpp"

int main ()
{
    HPGCC Coloring;
    
    std::string filename = "bmw3_2.mtx";

    Coloring.Read(filename);
    Coloring.Greedy();

    return 0;
}