#include "io.hpp"

#include "../hpgcc.hpp"

#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include <fstream>

bool read_mmx(std::string filename, std::vector<std::vector<int>> &neighbors)
{
    std::cout << "Reading adjacency matrix in MMX format from " << filename << std::endl;

    std::ifstream input;
    input.open(filename.c_str());

    int dimension = 0;

    std::string dummyLine;
    getline(input, dummyLine);

    input >> dimension;

    int hui, pfui;

    input >> hui >> pfui;

    std::cout << " " << dimension << " vertices in the graph" << std::endl;

    neighbors.resize(dimension);

    int a =0,b=0;
    double c=0.0;

    while(input >> a >> b >> c)
    {
       // std::cout << a << " " << b << " " << c << std::endl;
        if ( a != b )
        {
            neighbors[b].push_back(a); //mtx file of bmw3_2 starts indexing with 1
            neighbors[a].push_back(b);
        }
    } //end of while(in_file)

    return true;
}

bool HPGCC::Read(std::string filename)
{
    _filename=filename;
    std::cout << "Reading adjacency matrix in MTX format from " << filename << std::endl;

    std::ifstream input;
    input.open(filename.c_str());

    int dimension = 0;

    std::string dummyLine;
    getline(input, dummyLine);

    input >> dimension;

    int hui, pfui;

    input >> hui >> pfui;

    std::cout << " " << dimension << " vertices in the graph" << std::endl;

    neighbors.resize(dimension);

    int a =0,b=0;
    double c=0.0;

    while(input >> a >> b >> c)
    {
        //std::cout << a << " " << b << " " << c << std::endl;
        if ( a != b )
        {
            neighbors[b].push_back(a); //mtx file of bmw3_2 starts indexing with 1
            neighbors[a].push_back(b);
        }
    } //end of while(in_file)

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

            output << *vp.first << " " << *neighbours.first << " " << 0 << std::endl;
        }
    }

    output.close();

    return true;
}