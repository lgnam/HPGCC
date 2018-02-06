#include <iostream>

#include "hpgcc.hpp"

int main ()
{
    int nthreads = 1;
    HPGCC Coloring;
    
    std::string filename = "cit-Patents.mtx";

    Coloring.Read(filename);
    Coloring.Shuffle();    
    Coloring.Greedy();
    Coloring.GreedyLU();
    Coloring.Catalyurek(1);
    Coloring.Catalyurek(2);
    Coloring.Catalyurek(4);
    Coloring.Catalyurek(8);
    Coloring.SchedRev(1);
    Coloring.SchedRev(2);
    Coloring.SchedRev(4);
    Coloring.SchedRev(8);

    return 0;
}