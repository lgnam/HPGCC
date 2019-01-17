#include <iostream>
#include <unordered_map>

#include <random>
#include <functional>
#include <algorithm>
#include <math.h>

#include <chrono>

#include "../hpgcc.hpp"

//LargestDegreeFirst
bool LargestDegreeFirst(std::vector<std::vector<int>>& neighbors)
{
    std::cout << "Applying Largest-Degree-First ordering heuristic" << std::endl;

    auto begin_time = std::chrono::system_clock::now();

    std::vector<std::vector<int>> old_neighbors(neighbors);

    std::unordered_map<int, int> index_remapping;

    std::vector<int> new_indices(neighbors.size());
    std::vector<int> old_indices(neighbors.size());

    std::iota(new_indices.begin(), new_indices.end(), 0);
    std::iota(old_indices.begin(), old_indices.end(), 0);

    //sort by largest degree first
    std::sort(new_indices.begin(), new_indices.end(), [&neighbors](int v1, int v2){return neighbors[v1].size() > neighbors[v2].size();});//*/
/*
    //DEBUG 
    for (size_t i = 0; i < new_indices.size(); ++i)
    {
        std::cout << i << ": " << std::endl;
        std::cout << "  " << neighbors[new_indices[i]].size() << std::endl;
    }
    std::cout << std::endl;
    //END OF DEBUG*/

    neighbors.clear();
    neighbors.resize(old_neighbors.size());

    for (size_t i = 0; i < old_neighbors.size(); ++i)
    {
        for (size_t j = 0; j < old_neighbors[i].size(); ++j)
        {
            //neighbors[index_remapping[i]].push_back(index_remapping[old_neighbors[i][j]]);
            neighbors[ new_indices[i] ].push_back( new_indices[old_neighbors[i][j]] );
        }

       // std::cout << std::endl;
    }

    std::chrono::duration<double> remap_time = std::chrono::system_clock::now() - begin_time;
    return true;
} //LargestDegreeFirst End

bool SmallestDegreeLast(std::vector<std::vector<int>>& neighbors)
{
    std::cout << "Applying Smallest-Degree-Last ordering heuristic" << std::endl;

    auto begin_time = std::chrono::system_clock::now();

    std::vector<std::vector<int>> old_neighbors(neighbors);

    std::unordered_map<int, int> index_remapping;
    std::vector<int> new_indices(neighbors.size());
    std::vector<int> old_indices(neighbors.size());

    std::iota(new_indices.begin(), new_indices.end(), 0);
    std::iota(old_indices.begin(), old_indices.end(), 0);

    //sort by largest degree first
    std::sort(new_indices.begin(), new_indices.end(), [&neighbors](int v1, int v2){return neighbors[v1].size() < neighbors[v2].size();});//*/
/*
    //DEBUG 
    for (size_t i = 0; i < new_indices.size(); ++i)
    {
        std::cout << i << ": " << std::endl;
        std::cout << "  " << neighbors[new_indices[i]].size() << std::endl;
    }
    std::cout << std::endl;
    //END OF DEBUG*/

    neighbors.clear();
    neighbors.resize(old_neighbors.size());

    for (size_t i = 0; i < old_neighbors.size(); ++i)
    {
        for (size_t j = 0; j < old_neighbors[i].size(); ++j)
        {
            //neighbors[index_remapping[i]].push_back(index_remapping[old_neighbors[i][j]]);
            neighbors[ new_indices[i] ].push_back( new_indices[old_neighbors[i][j]] );
        }

       // std::cout << std::endl;
    }

    std::chrono::duration<double> remap_time = std::chrono::system_clock::now() - begin_time;
    return true;
} //end of smallest degree last

//Largest Log Degree First
bool LargestLogDegreeFirst(std::vector<std::vector<int>>& neighbors)
{
    std::cout << "Applying Largest-Log-Degree-First ordering heuristic" << std::endl;

    auto begin_time = std::chrono::system_clock::now();

    std::vector<std::vector<int>> old_neighbors(neighbors);

    std::unordered_map<int, int> index_remapping;

    std::vector<int> new_indices(neighbors.size());
    std::vector<int> old_indices(neighbors.size());

    std::iota(new_indices.begin(), new_indices.end(), 0);
    std::iota(old_indices.begin(), old_indices.end(), 0);

    //sort by largest degree first
    std::sort(new_indices.begin(), new_indices.end(), [&neighbors](int v1, int v2){return log10(neighbors[v1].size()) > log10(neighbors[v2].size());});//*/
/*
    //DEBUG 
    for (size_t i = 0; i < new_indices.size(); ++i)
    {
        std::cout << i << ": " << std::endl;
        std::cout << "  " << neighbors[new_indices[i]].size() << std::endl;
        std::cout << "  " << log10(neighbors[new_indices[i]].size()) << std::endl;
    }
    std::cout << std::endl;
    //END OF DEBUG*/

    neighbors.clear();
    neighbors.resize(old_neighbors.size());

    for (size_t i = 0; i < old_neighbors.size(); ++i)
    {
        for (size_t j = 0; j < old_neighbors[i].size(); ++j)
        {
            //neighbors[index_remapping[i]].push_back(index_remapping[old_neighbors[i][j]]);
            neighbors[ new_indices[i] ].push_back( new_indices[old_neighbors[i][j]] );
        }

       // std::cout << std::endl;
    }

    std::chrono::duration<double> remap_time = std::chrono::system_clock::now() - begin_time;
    return true;
}
//end of Largest Log Degree First

//Smallest Log Degree Last
bool SmallestLogDegreeLast(std::vector<std::vector<int>>& neighbors)
{
    std::cout << "Applying Smallest-Log-Degree-Last ordering heuristic" << std::endl;

    auto begin_time = std::chrono::system_clock::now();

    std::vector<std::vector<int>> old_neighbors(neighbors);

    std::unordered_map<int, int> index_remapping;
    std::vector<int> new_indices(neighbors.size());
    std::vector<int> old_indices(neighbors.size());

    std::iota(new_indices.begin(), new_indices.end(), 0);
    std::iota(old_indices.begin(), old_indices.end(), 0);

    //sort by largest degree first
    std::sort(new_indices.begin(), new_indices.end(), [&neighbors](int v1, int v2){return log10(neighbors[v1].size()) < log10(neighbors[v2].size());});//*/
/*
    //DEBUG 
    for (size_t i = 0; i < new_indices.size(); ++i)
    {
        std::cout << i << ": " << std::endl;
        std::cout << "  " << neighbors[new_indices[i]].size() << std::endl;
        std::cout << "  " << log10(neighbors[new_indices[i]].size()) << std::endl;
    }
    std::cout << std::endl;
    //END OF DEBUG*/

    neighbors.clear();
    neighbors.resize(old_neighbors.size());

    for (size_t i = 0; i < old_neighbors.size(); ++i)
    {
        for (size_t j = 0; j < old_neighbors[i].size(); ++j)
        {
            //neighbors[index_remapping[i]].push_back(index_remapping[old_neighbors[i][j]]);
            neighbors[ new_indices[i] ].push_back( new_indices[old_neighbors[i][j]] );
        }

       // std::cout << std::endl;
    }

    std::chrono::duration<double> remap_time = std::chrono::system_clock::now() - begin_time;
    return true;
}
//end of Smallest Log Degree Last

//Heuristic Selection
bool HPGCC::OrderGraph(std::string heuristic)
{
    if(heuristic == "rnd")
    {
        return true;
    }

    else if (heuristic == "ldf")
    {
        return LargestDegreeFirst(neighbors);
    }

    else if (heuristic == "lldf")
    {
        return LargestLogDegreeFirst(neighbors);
    }

    else if (heuristic == "sdl")
    {
        return SmallestDegreeLast(neighbors);
    }

    else if (heuristic == "sldl")
    {
        return SmallestLogDegreeLast(neighbors);
    }

    else
    {
        std::cerr << "No ordering heuristic!" << std::endl;
        return false;
    }
}//Heuristic Selection End