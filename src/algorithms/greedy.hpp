#ifndef GREEDY_HPP
#define GREEDY_HPP

#include <vector>
#include <string>

bool Greedy(std::string file, std::vector<std::vector<int>> &neighbors, int size);
bool GreedyInit(std::string file, std::vector<std::vector<int>> &neighbors, int size, std::vector<int> &vertex_colors, int* color_ptr, std::vector<int>& num_color_vertices);

#endif