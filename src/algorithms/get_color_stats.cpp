#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <numeric>

#include "../hpgcc.hpp"

//bool GetColorStats(std::string input, std::vector<int>& vertex_colors, int size, std::string algo, int threads, std::vector<double>& times, int num_shuffles)
bool HPGCC::GetColorStats(std::vector<int>& vertex_colors, std::string algo, int threads, std::vector<double>& times)
{
    std::cout << "  Getting color population" << std::endl;

    std::vector<int> degrees(neighbors.size(),0);
    
    int num_edges = 0;

    for (size_t i = 0; i < neighbors.size(); ++i)
    {
        degrees[i] = neighbors[i].size();
        num_edges+= neighbors[i].size();
    }

    //find maximum degree
    int max_degree = *(std::max_element(degrees.begin(), degrees.end())) +1;

    //find average degree
    auto avg = std::accumulate(degrees.begin(), degrees.end(),0) / (double)neighbors.size();

    std::cout << "  Max Degree: " << max_degree << std::endl;
    std::cout << "  Avg Degree: " << avg << std::endl;

    std::cout << "  Num Edges " << num_edges << std::endl;

    //get degree distribution
    std::vector<int> degree_dist(max_degree,0);

    for (auto it : degrees)
    {
        degree_dist[it]++;
        /*if (it == max_degree)
            std::cout << it << std::endl;

        else if (it == 0)
            std::cout << it << std::endl;*/
    }
    //end of get graph stats
    
    std::string output_degree_dist = "output/";
    output_degree_dist+=_filename;
    output_degree_dist+="_degree_distribution_";
    output_degree_dist+=algo;
    output_degree_dist+="_";
    output_degree_dist+=std::to_string(threads);
    output_degree_dist+="_threads_";
    output_degree_dist+=std::to_string(num_shuffles);
    output_degree_dist+="_shuffles";
    output_degree_dist+=".csv";

    std::ofstream file_dist;
    file_dist.open(output_degree_dist.c_str());

    for (size_t i = 0; i < degree_dist.size(); ++i)
    {
        file_dist << degree_dist[i] << std::endl;
    }

    file_dist.close();

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
    }

    file.close();

    return true;
}