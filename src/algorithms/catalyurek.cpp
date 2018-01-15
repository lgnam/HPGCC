#include "catalyurek.hpp"

#include <iostream>
#include <string>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <fstream>

#include "check_coloring.hpp"
#include "get_color_stats.hpp"

#include <omp.h>

bool Catalyurek(std::string file, std::vector<std::vector<int>> &neighbors, int size, int nthreads)
{
    std::cout << std::endl;
    std::cout << "Catalyurek's Algorithm with " << nthreads << " threads" << std::endl;

    auto begin_color = std::chrono::system_clock::now();
    
    std::vector<int> vertex_colors(size, 0);

    std::vector<int> worklist (size);
    std::iota(worklist.begin(), worklist.end(), 0);

    int round = 1;

    while(worklist.size() != 0)
    {
        
        #pragma omp parallel for schedule(dynamic)
        for(size_t vert = 0; vert < worklist.size(); ++vert)
        {
            std::vector<int> forbiddenColors(2000, 0);
            
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

        #pragma omp parallel for schedule(dynamic)
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
    bool valid = CheckColoring(neighbors, vertex_colors, size);
    std::string valid_str = "valid";
    if(!valid)
    {
        std::cerr << "  WRONGFUL COLORING DETECTED!" << std::endl;
        //return false;
        valid_str.clear();
        valid_str = "invalid";

    }
    GetColorStats(file, vertex_colors, size, "Catalyurek", nthreads);//*/

    std::ofstream output;
    output.open("output/times_catalyurek.csv", std::ofstream::app);

    output << file << ", " << size << ", " << "Catalyurek" << ", " << nthreads << ", " << total_color_dur.count() << ", ";
    output << max_colors << ", " << round << ", " << valid_str << std::endl;

    output.close();

    std::cout << max_colors << std::endl;

    return true;
}
