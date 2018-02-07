#include "../hpgcc.hpp"
#include "shuffle.hpp"

#include <iostream>
#include <unordered_map>

#include <random>
#include <functional>
#include <algorithm>

#include <chrono>

bool HPGCC::Shuffle(int shuffles)
{
    num_shuffles = shuffles;

    std::cout << "Shuffling " << num_shuffles << " times the vertex indices of " << _filename << std::endl;

    auto begin_time = std::chrono::system_clock::now();

    //std::cout << neighbors.size() << std::endl;

    std::vector<std::vector<int>> old_neighbors = neighbors;

   // std::cout << old_neighbors.size() << std::endl;

    std::unordered_map<int, int> index_remapping;

    std::vector<int> new_indices(neighbors.size());
    std::vector<int> old_indices(neighbors.size());

    std::iota(new_indices.begin(), new_indices.end(), 0);
    std::iota(old_indices.begin(), old_indices.end(), 0);

    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine(rnd_device());
    std::uniform_int_distribution<int> dist(1, 52);

    for (size_t i = 0; i < num_shuffles; i++)
        std::shuffle(new_indices.begin(), new_indices.end(), mersenne_engine);   
    
    std::chrono::duration<double> prep_time = std::chrono::system_clock::now() - begin_time;

    begin_time = std::chrono::system_clock::now();

    for (size_t i = 0; i < neighbors.size(); ++i)
    {
        index_remapping.insert(std::pair<int,int>(old_indices[i], new_indices[i]));
    }

    std::chrono::duration<double> for1_time = std::chrono::system_clock::now() - begin_time;

    /*DEBUG*/
    /*for (auto it : index_remapping)
    {
        std::cout << it.first << " " << it.second << std::endl;
    }//*/
    /*END OF DEBUG*/

    begin_time = std::chrono::system_clock::now();

    neighbors.empty();
    neighbors.resize(old_neighbors.size());

    for (size_t i = 0; i < old_neighbors.size(); ++i)
    {
        for (size_t j = 0; j < old_neighbors[i].size(); ++j)
        {
            neighbors[index_remapping[i]].push_back(index_remapping[old_neighbors[i][j]]);
        }
    }

    std::chrono::duration<double> remap_time = std::chrono::system_clock::now() - begin_time;
/*
    std::cout << "  Prep Time: " << prep_time.count() << std::endl;
    std::cout << "  Create Map Time: " << for1_time.count() << std::endl;
    std::cout << "  Remap Time: " << remap_time.count() << std::endl;//*/

    return true;
}