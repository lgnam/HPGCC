#include <iostream>
#include <chrono>

#include "hpgcc.hpp"

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Filename is missing!" << std::endl;
        return -1;
    }
    
    HPGCC Coloring;
    
    std::string filename = argv[1];
    
    std::string heuristic;
    if (argc >= 2)
    {
        heuristic = argv[2];
    }

    if( !Coloring.Read(filename.c_str()))
    {
        return -1;
    }
    
    Coloring.Shuffle(1);    //*/

    //Coloring.OrderGraph(heuristic);

    Coloring.Greedy();
    Coloring.GreedyLU();
    Coloring.Catalyurek(1);
    Coloring.Catalyurek(2);
    Coloring.Catalyurek(4);
    Coloring.Catalyurek(8);
    Coloring.Catalyurek(16);
    Coloring.SchedRev(1);
    Coloring.SchedRev(2);
    Coloring.SchedRev(4);
    Coloring.SchedRev(8);
    Coloring.SchedRev(16);
//*/
    return 0;
}