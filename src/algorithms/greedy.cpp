#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

#include "../hpgcc.hpp"

bool HPGCC::Greedy()
{
    std::cout << std::endl;
    std::cout << "Greedy Algorithm" << std::endl;
    
    auto begin_color = std::chrono::system_clock::now();

    int max_colors = 1;

    int size = neighbors.size();

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

    bool valid = CheckColoring(vertex_colors);
    std::string valid_str = "valid";
    //Check vertex coloring
    if(!valid)
    {
        std::cerr << "  WRONGFUL COLORING DETECTED!" << std::endl;
        //return false;
        valid_str.clear();
        valid_str = "invalid";

    }
    
    std::cout << " -> " << valid_str << std::endl;

    std::vector<double> times;
    times.push_back(color_dur.count());

    GetColorStats(vertex_colors, "Greedy", 1, times);//*/

    std::ofstream output;
    output.open("output/times_greedy.csv", std::ofstream::app);

    output << _filename << ", " << size << ", " << "Greedy" << ", " << "1" << ", " << color_dur.count() << ", " << max_colors << ", " << valid_str << std::endl;

    output.close();

    std::cout << " Time: " << color_dur.count() << " s" << std::endl;

    return true;
}

//bool GreedyInit(std::string file, std::vector<std::vector<int>> &neighbors, int size, std::vector<int>& vertex_colors, int* colors, std::vector<int>& num_color_vertices)
bool HPGCC::GreedyInit(std::vector<int>& vertex_colors, int* colors, std::vector<int>& num_color_vertices)
{
    int size = neighbors.size();
    /*std::cout << std::endl;
    std::cout << "  Inital Greedy coloring" << std::endl;*/
        int max_colors = 1;

    vertex_colors.resize(size, 0);

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

    return true;
}
