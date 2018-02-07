#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

#include "../hpgcc.hpp"

//bool GetColorStats(std::string input, std::vector<int>& vertex_colors, int size, std::string algo, int threads, std::vector<double>& times, int num_shuffles)
bool HPGCC::GetColorStats(std::vector<int>& vertex_colors, std::string algo, int threads, std::vector<double>& times)
{
    std::cout << "  Getting color population" << std::endl;

    //auto iter = input.find_last_of("/");

    std::string output = "output/";
    //output+=input;
    //output+=input.substr(iter+1);
    output+=_filename;
    output+="_color_population_";
    output+=algo;
    output+="_";
    output+=std::to_string(threads);
    output+="_threads_";
    output+=std::to_string(num_shuffles);
    output+="_shuffles";
    output+=".csv";

    std::ofstream file;
    file.open(output.c_str());

    int colors = *( std::max_element(vertex_colors.begin(), vertex_colors.end()) ) + 1;

    //file << "# " << input.substr(iter+1) << ", " << algo << ", " << threads << ", " << num_shuffles << ", ";,
    file << "# " << _filename << ", " << algo << ", " << threads << ", " << num_shuffles << ", ";
    
    for (auto time : times)
        file << time << ", ";
    
    file << std::endl;

    std::vector<std::vector<int>> color_vertices(colors);
    
    for (size_t i = 0; i < vertex_colors.size(); ++i)
    {
        color_vertices[ vertex_colors[i] ].push_back(i);
    }

    for (size_t i = 0; i < color_vertices.size(); ++i)
    {
        file << i << ", " << color_vertices[i].size() << std::endl;

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