#include "io.hpp"

#include <iostream>
#include <fstream>

bool read_mmx(std::string filename)
{
    std::cout << "Reading adjacency matrix in MMX format from " << filename << std::endl;
    return true;
}

bool write_mmx(std::string filename, boost::adjacency_list<> g)
{
   // graph_traits<adjacency_list>::vertices_size_type;
    std::cout << "Writing adjacency matrix in MMX format into " << filename << std::endl;

    std::ofstream output;
    output.open(filename.c_str());

    typedef boost::adjacency_list<> Graph;

    output << "%%MatrixMarket matrix coordinate real general" << std::endl;
/*
    boost::graph_traits<boost::adjacency_list<>>::vertex_iterator vi, vi_end;
    boost::tie(vi, vi_end) = vertices(g);*/

    output << num_vertices(g) << " " << num_vertices(g) << " " << num_edges(g) << std::endl; 

    // Iterate through the vertices and print them out
    typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
    typedef boost::graph_traits<Graph>::adjacency_iterator adjacency_it;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first)
    {
        //std::cout << *vp.first << std::endl;

        for (std::pair<adjacency_it, adjacency_it> neighbours = boost::adjacent_vertices(*vp.first, g); neighbours.first != neighbours.second; ++neighbours.first)
        {
           // std::cout << "  " << *neighbours.first << std::endl;

            output << *vp.first << " " << *neighbours.first << std::endl;
        }
    }

    output.close();

    return true;
}