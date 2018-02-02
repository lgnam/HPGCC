#ifndef HPGCC_HPP
#define HPGCC_HPP

#include <string>
#include <vector>

class HPGCC
{
    public:
        /*HPGCC();        //constructor*/

        //IO functions
        bool Read(std::string filename);    //read graph
        bool Write();

        //coloring algorithms
        bool Greedy();

    private:
        std::vector<std::vector<int>> neighbors;
        std::string _filename;
};

#endif