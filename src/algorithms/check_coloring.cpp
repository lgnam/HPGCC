#include "check_coloring.hpp"

#include <iostream>

bool CheckColoring(std::vector<std::vector<int>> &neighbors, std::vector<int> &vertex_colors, int size)
{
    bool valid = true;
    //Check vertex coloring
    std::cout << "  Checking coloring";
    for (size_t vert_id = 0; vert_id < size; ++vert_id)
    {
        for (auto neigh_id : neighbors[vert_id])
        {
            if (vertex_colors[vert_id] == vertex_colors[neigh_id])
            {
                //#pragma omp atomic write
                std::cout << "WRONG COLORING" << std::endl;
                std::cout << "vertex " << vert_id << " has color " << vertex_colors[vert_id] << std::endl;
                std::cout << "neighbor " << neigh_id << " has color " << vertex_colors[neigh_id] << std::endl;//*/
                valid = false;
            }
        }
    }

    return valid;
}
