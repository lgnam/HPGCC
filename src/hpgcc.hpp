#ifndef HPGCC_HPP
#define HPGCC_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class HPGCC
{
    public:
        /*HPGCC(int num_threads) : nthreads{num_threads} {};        //constructor*/

        //IO functions
        bool Read(std::string filename);    //read graph
        bool Write();

        //coloring algorithms
        bool Greedy();
        bool GreedyLU();
        bool Catalyurek(int num_threads=1);
        bool SchedRev(int num_threads=1);

        //Helper Functions
        bool Shuffle();
        bool GetMaxDegree() 
        {
            std::vector<int> degrees(neighbors.size(),0);
            
            int num_edges = 0;
        
            for (size_t i = 0; i < neighbors.size(); ++i)
            {
                degrees[i] = neighbors[i].size();
                num_edges+= neighbors[i].size();
            }
        
            //find maximum degree
            max_degree = *(std::max_element(degrees.begin(), degrees.end()));
            std::cout << " Max Degree: " << max_degree << std::endl;
        };

    private:
        std::vector<std::vector<int>> neighbors;
        std::string _filename;
        int max_degree;
        //int nthreads;
};

#endif