#include <iostream>
#include <string>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <fstream>

#include <omp.h>

#include "../hpgcc.hpp"

bool HPGCC::Catalyurek(int nthreads)
{
    std::cout << std::endl;
    std::cout << "Catalyurek's Algorithm with " << nthreads << " threads" << std::endl;

    auto begin_color = std::chrono::system_clock::now();

    int size = neighbors.size();
    
    std::vector<int> vertex_colors(size, 0);

    std::vector<int> worklist (size);
    std::iota(worklist.begin(), worklist.end(), 0);

    int round = 1;

    while(worklist.size() != 0)
    {
        #pragma omp parallel for schedule(dynamic) num_threads(nthreads)
        for(size_t vert = 0; vert < worklist.size(); ++vert)
        {
            std::vector<int> forbiddenColors(max_degree, 0);
            
            for (size_t neigh = 0; neigh < neighbors[worklist[vert]].size(); ++neigh)
            {
                int neigh_id = neighbors[worklist[vert]][neigh];
                forbiddenColors[vertex_colors[neigh_id]] = worklist[vert];
            }
            
            for (size_t i = 0; i < forbiddenColors.size(); ++i)
            {
                if (forbiddenColors[i] != worklist[vert])
                {
                    vertex_colors[worklist[vert]] = i;
                    //std::cout << worklist[vert] << " " << i << std::endl;
                    break;
                }
            }

        }//end of parallel for

        std::vector<std::vector<int>> recolor(nthreads);

        #pragma omp parallel for schedule(dynamic) num_threads(nthreads)
        for (size_t vert = 0; vert < worklist.size(); ++vert)
        {
            for (size_t neigh = 0; neigh < neighbors[worklist[vert]].size(); ++neigh)
            {
                int neigh_id = neighbors[worklist[vert]][neigh];
                
                if (vertex_colors[ worklist[vert] ] == vertex_colors[neigh_id] && worklist[vert] > neigh_id)
                {
                    recolor[omp_get_thread_num()].push_back(worklist[vert]);
                }
            }
        } //end of parallel for

        worklist.clear();
        worklist.reserve(size);
        
        for (size_t i = 0; i < recolor.size(); ++i)
        {
            for (size_t j = 0; j < recolor[i].size(); ++j)
            {
                worklist.push_back(recolor[i][j]);
            }
        }
        ++round;
    } //end of while

    std::chrono::duration<double> total_color_dur = std::chrono::system_clock::now() - begin_color;
    
    int max_colors = *( std::max_element(vertex_colors.begin(), vertex_colors.end()) ) + 1;

    //Check vertex coloring
    bool valid = CheckColoring(vertex_colors);
    std::string valid_str = "valid";
    if(!valid)
    {
        std::cerr << "  WRONGFUL COLORING DETECTED!" << std::endl;
        //return false;
        valid_str.clear();
        valid_str = "invalid";

    }

    std::cout << " -> " << valid_str << std::endl;

    std::vector<double> times;
    times.push_back(total_color_dur.count());

    GetColorStats(vertex_colors, "Catalyurek", nthreads, times);//*/

    //std::ofstream output;
    //output.open("output/times_catalyurek.csv", std::ofstream::app);
    std::string output_file = "output/";
    output_file += _filename;
    output_file += "_times_catalyurek.csv";
    std::ofstream output;
    //output.open("output/times_greedy.csv", std::ofstream::app);
    output.open(output_file.c_str(), std::ofstream::app);

    output << _filename << ", " << size << ", " << "Catalyurek" << ", " << nthreads << ", " << total_color_dur.count() << ", ";
    output << max_colors << ", " << round << ", " << valid_str << std::endl;

    output.close();

    std::cout << " Time: " << total_color_dur.count() << " s" << std::endl;

    return true;
}