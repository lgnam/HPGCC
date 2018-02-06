#include "../hpgcc.hpp"
#include "shuffle.hpp"

#include <iostream>
#include <map>

#include <random>
#include <functional>
#include <algorithm>

bool HPGCC::Shuffle()
{
    std::cout << "Shuffling vertex indices of " << _filename << std::endl;

    //std::cout << neighbors.size() << std::endl;

    std::vector<std::vector<int>> old_neighbors = neighbors;

   // std::cout << old_neighbors.size() << std::endl;

    std::map<int, int> index_remapping;

    std::vector<int> new_indices(neighbors.size());
    std::vector<int> old_indices(neighbors.size());

    std::iota(new_indices.begin(), new_indices.end(), 0);
    std::iota(old_indices.begin(), old_indices.end(), 0);

    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine(rnd_device());
    std::uniform_int_distribution<int> dist(1, 52);

    std::shuffle(new_indices.begin(), new_indices.end(), mersenne_engine);   
    
    for (size_t i = 0; i < neighbors.size(); ++i)
    {
        index_remapping.insert(std::pair<int,int>(old_indices[i], new_indices[i]));
    }

    /*DEBUG*/
    /*for (auto it : index_remapping)
    {
        std::cout << it.first << " " << it.second << std::endl;
    }//*/
    /*END OF DEBUG*/

    neighbors.empty();
    neighbors.resize(old_neighbors.size());

    for (size_t i = 0; i < old_neighbors.size(); ++i)
    {
        for (size_t j = 0; j < old_neighbors[i].size(); ++j)
        {
            neighbors[index_remapping[i]].push_back(index_remapping[old_neighbors[i][j]]);
        }
    }

    return true;
}