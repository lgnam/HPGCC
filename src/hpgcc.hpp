#ifndef HPGCC_HPP
#define HPGCC_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class HPGCC
{
    public:
        HPGCC(int num_shuffles=0) : num_shuffles{num_shuffles} {};        //constructor*/

        //IO functions
        bool Read(std::string filename);    //read graph
        bool Write(std::string out_file);

        //coloring algorithms
        bool Greedy();
        bool GreedyLU();
        bool Catalyurek(int num_threads=1);
        bool SchedRev(int num_threads=1);

        //Helper Functions
        bool Shuffle(int shuffles=1);
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
            max_degree = *(std::max_element(degrees.begin(), degrees.end()))+1;
            std::cout << " Max Degree: " << max_degree << std::endl;
        };

        bool OrderGraph(std::string heuristic);

    private:

        bool GreedyInit(std::vector<int>& vertex_colors, int* colors, std::vector<int>& num_color_vertices);
        bool GetColorStats(std::vector<int>& vertex_colors, std::string algo, int threads, std::vector<double>& times);
        bool CheckColoring(std::vector<int> &vertex_colors);

    
        /*bool LargestDegreeFirst();
        bool SmallestDegreeFirst();*/

        std::vector<std::vector<int>> neighbors;
        std::string _filename;
        std::string heuristic;
        int max_degree;
        int num_shuffles;
        //int nthreads;
};

#endif