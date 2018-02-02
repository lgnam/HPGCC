#ifndef IO_HPP
#define IO_HPP

#include "../hpgcc.hpp"

#include <string>
#include <boost/graph/adjacency_list.hpp>

bool read_mmx(std::string filename, std::vector<std::vector<int>> &neighbors);
bool write_mmx(std::string filename, boost::adjacency_list<> graph);


#endif