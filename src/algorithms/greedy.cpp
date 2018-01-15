#include "greedy.hpp"
#include "check_coloring.hpp"
#include "get_color_stats.hpp"

#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

bool Greedy(std::string file, std::vector<std::vector<int>> &neighbors, int size)
{
    std::cout << std::endl;
    std::cout << "Greedy Algorithm" << std::endl;
    
    auto begin_color = std::chrono::system_clock::now();

    int max_colors = 1;

    std::vector<int> vertex_colors(size, 0);

    //coloring algorithm
    for (size_t vert = 1; vert < size; ++vert)
    {
        std::vector<int> forbiddenColors(max_colors+1, -1);

        for (size_t neigh = 0; neigh < neighbors[vert].size() ; ++neigh)
        {
            int neigh_id = neighbors[vert][neigh];
            forbiddenColors[ vertex_colors[neigh_id] ] = vert;
        }

        for (size_t i = 0; i < forbiddenColors.size(); ++i)
        {
            if (forbiddenColors[i] != vert)
            {
                if (i == forbiddenColors.size()-1)
                {
                    ++max_colors;
                }
                
                vertex_colors[vert] = i;

                break;
            }
        }
    }
    //end of coloring algorithm
    std::chrono::duration<double> color_dur = std::chrono::system_clock::now() - begin_color;

    bool valid = CheckColoring(neighbors, vertex_colors, size);
    std::string valid_str = "valid";
    //Check vertex coloring
    if(!valid)
    {
        std::cerr << "  WRONGFUL COLORING DETECTED!" << std::endl;
        //return false;
        valid_str.clear();
        valid_str = "invalid";

    }

    GetColorStats(file, vertex_colors, size, "Greedy");//*/

    std::ofstream output;
    output.open("output/times_greedy.csv", std::ofstream::app);

    output << file << ", " << size << ", " << "Greedy" << ", " << "1" << ", " << color_dur.count() << ", " << max_colors << ", " << valid_str << std::endl;

    output.close();

    return true;
}

bool GreedyInit(std::string file, std::vector<std::vector<int>> &neighbors, int size, std::vector<int>& vertex_colors, int* colors, std::vector<int>& num_color_vertices)
{
    /*std::cout << std::endl;
    std::cout << "  Inital Greedy coloring" << std::endl;*/
        int max_colors = 1;

   // vertex_colors.resize(size, 0);

    //coloring algorithm
    for (size_t vert = 0; vert < size; ++vert)
    {
        std::vector<int> forbiddenColors(max_colors+1, -1);

        for (size_t neigh = 0; neigh < neighbors[vert].size() ; ++neigh)
        {
            int neigh_id = neighbors[vert][neigh];
            forbiddenColors[ vertex_colors[neigh_id] ] = vert;
        }

        for (size_t i = 0; i < forbiddenColors.size(); ++i)
        {
            if (forbiddenColors[i] != vert)
            {
                if (i == forbiddenColors.size()-1)
                {
                    ++max_colors;
                }
                
                vertex_colors[vert] = i;

                break;
            }
        }
    }

    *colors = max_colors;
    
    for (size_t i = 0; i < size; ++i)
    {
        num_color_vertices[ vertex_colors[i] ]++;
    }
/*
    //end of coloring algorithm
    std::chrono::duration<double> color_dur = std::chrono::system_clock::now() - begin_color;

    //Check vertex coloring
    if(!CheckColoring(neighbors, vertex_colors, size))
    {
        std::cerr << "  WRONGFUL COLORING DETECTED!" << std::endl;
        return false;
    }

    GetColorStats(file, vertex_colors, size, "SchedRevGreedyInit");

    std::ofstream output;
    output.open("output/times_sched-rev-init.csv", std::ofstream::app);

    output << file << ", " << size << ", " << "SchedRevGreedyInit" << ", " << "1" << ", " << color_dur.count() << ", " << max_colors << std::endl;

    output.close();//*/

    return true;
}
