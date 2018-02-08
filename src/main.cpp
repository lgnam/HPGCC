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
   //int nthreads = 1;
    HPGCC Coloring;
    
    std::string filename = argv[1];

   // auto begin_time = std::chrono::system_clock::now();
   if( !Coloring.Read(filename.c_str()))
   {
       return -1;
   }
   // std::chrono::duration<double> read_time = std::chrono::system_clock::now() - begin_time;
    
   // begin_time = std::chrono::system_clock::now();
   Coloring.Shuffle(1);    
   // std::chrono::duration<double> shuffle_time = std::chrono::system_clock::now() - begin_time;
/*
    std::cout << "read time: " << read_time.count() << std::endl;
    std::cout << "shuffle time: " << shuffle_time.count() << std::endl;
*/
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
//*/
    return 0;
}