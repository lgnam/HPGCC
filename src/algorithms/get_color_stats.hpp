#ifndef GET_COLOR_STATS_HPP
#define GET_COLOR_STATS_HPP

#include <vector>
#include <string>

bool GetColorStats(std::string input, std::vector<int>& vertex_colors, int size, std::string algo, int threads=1);

#endif