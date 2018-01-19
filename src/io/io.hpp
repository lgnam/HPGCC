#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <boost/graph/adjacency_list.hpp>

bool read_mmx(std::string filename);
bool write_mmx(std::string filename, boost::adjacency_list<> graph);

#endif