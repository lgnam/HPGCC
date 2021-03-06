#include "io.hpp"

#include "../hpgcc.hpp"

#include <boost/graph/adjacency_list.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
/*
bool read_mmx(std::string filename, std::vector<std::vector<int>> &neighbors)
{
    std::cout << "Reading adjacency matrix in MMX format from " << filename <<
std::endl;

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
            neighbors[b].push_back(a); //mtx file of bmw3_2 starts indexing with
1
            neighbors[a].push_back(b);
        }
    } //end of while(in_file)

    return true;
}*/

bool HPGCC::Read(std::string filename) 
{
  std::size_t iter = filename.find(".mtx");
  std::size_t begin = filename.find_last_of("/");
  if (begin == filename.npos )
  {
    begin=0;
  }

  _filename = filename.substr(begin+1, iter-begin-1);
  std::cout << std::endl
            << "Reading adjacency matrix in MTX format from " << filename
            << std::endl;

  std::ifstream input;
  input.open(filename.c_str());

  if (!input) {
    std::cerr << "  Error when opening file '" << filename << "'" << std::endl;
    return false;
  }

  int dimension = 0;
  int hui, pfui;
  std::string dummyLine;
  while (getline(input, dummyLine)) 
  {
    if (!dummyLine.compare(0, 1, "%")) 
    {
      ;
    } 
    
    else 
    {
      std::smatch res;
      const std::regex myRegex("\\d");
      dimension = std::stoi(dummyLine.substr(0, dummyLine.find(' ')));
      break;
    }
  }

  std::cout << " " << dimension << " vertices in the graph" << std::endl;

  neighbors.empty();
  neighbors.resize(dimension);

  int a = 0, b = 0;
  double c = 0.0;
  int decrementor = 1;

  while (input >> a >> b >> c) {
    //checks if indexing starts with 0 or 1
    if (a == 0 || b == 0)
    {
      decrementor = 0;
    }
     //std::cout << "a " << a << " b " << b << " c " << c << std::endl;
    if (a != b) {
      neighbors[b - decrementor].push_back(a - decrementor); // mtx file of bmw3_2 starts indexing with 1
      neighbors[a - decrementor].push_back(b - decrementor);
      /*
      neighbors[b - 1].push_back(a - 1); // mtx file of bmw3_2 starts indexing with 1
      neighbors[a - 1].push_back(b - 1);*/
    }
  } // end of while(in_file)

  GetMaxDegree();

  std::cout << std::endl;

  return true;
}

bool HPGCC::Write(std::string out_file) 
{
  std::cout << "Writing adjacency matrix in MMX format into " << out_file
  << std::endl;

  std::ofstream output;
  output.open("shuffled.mtx");

  output << "%%MatrixMarket matrix coordinate real general" << std::endl;

  output << neighbors.size() << " " << neighbors.size() << " " << "0" << std::endl;

  return true;
}

bool write_mmx(std::string filename, boost::adjacency_list<> g) {
  // graph_traits<adjacency_list>::vertices_size_type;
  std::cout << "Writing adjacency matrix in MMX format into " << filename
            << std::endl;

  std::ofstream output;
  output.open(filename.c_str());

  typedef boost::adjacency_list<> Graph;

  output << "%%MatrixMarket matrix coordinate real general" << std::endl;
  /*
      boost::graph_traits<boost::adjacency_list<>>::vertex_iterator vi, vi_end;
      boost::tie(vi, vi_end) = vertices(g);*/

  output << num_vertices(g) << " " << num_vertices(g) << " " << num_edges(g)
         << std::endl;

  // Iterate through the vertices and print them out
  typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
  typedef boost::graph_traits<Graph>::adjacency_iterator adjacency_it;
  std::pair<vertex_iter, vertex_iter> vp;
  for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
    // std::cout << *vp.first << std::endl;

    for (std::pair<adjacency_it, adjacency_it> neighbours =
             boost::adjacent_vertices(*vp.first, g);
         neighbours.first != neighbours.second; ++neighbours.first) {
      // std::cout << "  " << *neighbours.first << std::endl;

      output << *vp.first << " " << *neighbours.first << " " << 0 << std::endl;
    }
  }

  output.close();

  return true;
}