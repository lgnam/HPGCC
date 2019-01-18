#include <iostream>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <fstream>

#include "../hpgcc.hpp"

bool HPGCC::GreedyLU()
{
    std::cout << std::endl;
    std::cout << "Greedy-LU Algorithm" << std::endl;
    
    auto begin_color = std::chrono::system_clock::now();

    int size = neighbors.size();

    //resize vector
    //std::vector<int> vertex_colors(size, -1);
    std::vector<int> vertex_colors(size, 0);
/*
    int max_colors = 1;                 //number of used colors
    vertex_colors[0] = 0;       //assign first vertex color 0      */

    int max_colors = 1;
    
    //std::cout << "0 gets new color 0" << std::endl;

    std::vector<int> color_usage;   //vector storing how many times a color has been assigned (each element is a color)*/
    color_usage.reserve(2000);      
    color_usage.push_back(1);       //initialize the first color assigned to the first vertex (color 0, assigned 1 time)*/

    //visit every vertex and assign the least used color available (not already assigned to on of its neighbors)
    //if no used color is permissible, assign a new color
    for (size_t vert = 1; vert < vertex_colors.size(); ++vert)
    {
        //OLD VERSION        
        //find set of permissible colors
        std::vector<bool> permissible_colors(max_colors, true);

        for (auto neighbor : neighbors[vert])
        {
            //since we assign colors to vertices in ascending ID order, check only
            //neighbors with smaller vertex ID
            if (neighbor > vert)
            {
                continue;
            }

            permissible_colors[ vertex_colors[neighbor] ] = false;
        }

        std::vector<int> permissible_usage = color_usage;

        //set usage of colors not allowed for assignement to the numerical limit of int
        for (size_t i = 0; i < permissible_colors.size(); ++i)
        {
            if (!permissible_colors[i])
            {
                permissible_usage[i] = std::numeric_limits<int>::max();
            }
        }

        //check if we need to create a new color
        if ( !std::accumulate(permissible_colors.begin(), permissible_colors.end(), false) )
        {
            vertex_colors[vert] = max_colors;
            color_usage.push_back(1);
            ++max_colors;           
        }

        else
        {
            vertex_colors[vert] = std::min_element(permissible_usage.begin(), permissible_usage.end()) - permissible_usage.begin();
            ++color_usage[vertex_colors[vert]];
        }      
/*
        std::vector<int> forbiddenColors(max_colors+1, -1);


        //std::cout << vert+1 << "/" << size << std::endl;
        //find set of permissible colors
        std::vector<bool> permissible_colors(max_colors, true);

        //find permissible (forbidden) colors
        for (size_t neigh = 0; neigh < neighbors[vert].size() ; ++neigh)
        {
            int neigh_id = neighbors[vert][neigh];
            forbiddenColors[ vertex_colors[neigh_id] ] = vert;
        }

        bool use_old_color = false;
        int new_color = 0;
        
        for (size_t i = 0; i < forbiddenColors.size(); ++i)
        {
            if (forbiddenColors[i] != vert)
            { 
                if ( !use_old_color && i == (forbiddenColors.size()-1) )
                {
                    ++max_colors;
                    new_color = i;
                    color_usage.push_back(1);
                }

                if (color_usage[i] < color_usage[new_color])
                {
                    new_color = i;
                    use_old_color = true;
                }
            }
        }

        if (use_old_color)
        {
            ++color_usage[new_color];
        }

        vertex_colors[vert] = new_color;
    */
                //*/
 
    } //end of for loop iterating vertices

    std::chrono::duration<double> color_dur = std::chrono::system_clock::now() - begin_color;
    
    //Check vertex coloring
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

    //Get Statistics of Coloring
    GetColorStats(vertex_colors, "Greedy-LU", 1, times);
/*
    std::cout << "  Finished Greedy-LU Algorithm using " << "1" << " thread" << std::endl;
    std::cout << "    Colors: " << max_colors << std::endl;
    std::cout << "    Vertices: " << size << std::endl;
    std::cout << "    Total Time [s]: " << color_dur.count() << std::endl;*/
    

    std::string output_file = "output/";
    output_file += _filename;
    output_file += "_times_greedy-lu.csv";
    std::ofstream output;
    //output.open("output/times_greedy.csv", std::ofstream::app);
    output.open(output_file.c_str(), std::ofstream::app);

    output << _filename << ", " << size << ", " << "Greedy-LU" << ", " << "1" << ", " << color_dur.count() << ", " << max_colors << ", " << valid_str << std::endl;

    output.close();

    std::cout << " Time: " << color_dur.count() << " s" << std::endl;

    return true;
}