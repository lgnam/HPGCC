#include "get_color_stats.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

bool GetColorStats(std::string input, std::vector<int>& vertex_colors, int size, std::string algo, int threads)
{
    std::cout << "  Getting color population" << std::endl;

    std::string filename = "output/";
    filename+=input;
    filename+="_color_population_";
    filename+=algo;
    filename+="_";
    filename+=std::to_string(threads);
    filename+="_threads.csv";

    std::ofstream file;
    file.open(filename.c_str());

    int colors = *( std::max_element(vertex_colors.begin(), vertex_colors.end()) ) + 1;

    std::vector<std::vector<int>> color_vertices(colors);
    
    for (size_t i = 0; i < vertex_colors.size(); ++i)
    {
        color_vertices[ vertex_colors[i] ].push_back(i);
    }

    for (size_t i = 0; i < color_vertices.size(); ++i)
    {
        file << "          " << i << " | " << color_vertices[i].size() << std::endl;

        //std::cout << "          " << i << " | ";
       /* for (auto it : color_vertices[i])
        {
            std::cout << it << " ";
        }
        
        std::cout << std::endl;//*/
    }

    file.close();

    return true;
}