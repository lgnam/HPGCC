#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <map>

#include "algorithms/rokos.hpp"
#include "algorithms/greedy.hpp"
#include "algorithms/greedy-lu.hpp"
#include "algorithms/sched-rev.hpp"
#include "algorithms/catalyurek.hpp"

#include <omp.h>

//#include <boost/graph/use_mpi.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/rmat_graph_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/graph_utility.hpp>
//using boost::graph::distributed::mpi_process_group;
#include <boost/graph/graph_traits.hpp>

#include <boost/program_options.hpp>

#include "io/io.hpp"

#include <iterator>


typedef boost::adjacency_list<> Graph;
typedef boost::rmat_iterator<boost::minstd_rand, Graph> RMATGen;

typedef boost::property<boost::vertex_property_tag, double> VertexProperty;

int main (int argc, char *argv[])
{
    std::cout << "Checking input parameters" << std::endl;
    int number_nodes;
    int number_edges;
    double a, b, c, d;
    std::string filename;

    if (argc < 7)
    {
        std::cout << "Usage: number_nodes number_edges a b c d filename" << std::endl;
        return -1;
    }

    number_nodes = std::atoi(argv[1]);
    number_edges = std::atoi(argv[2]);
    a = std::stod(argv[3]);
    b = std::stod(argv[4]);
    c = std::stod(argv[5]);
    d = std::stod(argv[6]);
    filename = argv[7];


    std::cout << "Call R-MAT graph generator" << std::endl;
    boost::minstd_rand gen;

    // Create graph with num_vertices nodes and 400 edges
    Graph g(RMATGen(gen, number_nodes, number_edges, a, b, c, d), RMATGen(), 100);
/*
    std::cout << "numVertices: " << num_vertices(g) << std::endl;
    std::cout << "numEdges: " << num_edges(g) << std::endl;*/

//    std::cout << "writing graph into file (matrix market exchange format)..." << std::endl;
/*
    // Iterate through the vertices and print them out
    typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
    typedef boost::graph_traits<Graph>::adjacency_iterator adjacency_it;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first)
    {
        std::cout << *vp.first << std::endl;

        for (std::pair<adjacency_it, adjacency_it> neighbours = boost::adjacent_vertices(*vp.first, g); neighbours.first != neighbours.second; ++neighbours.first)
        {
            std::cout << "  " << *neighbours.first << std::endl;
        }
    }
        //std::cout << g[*vp.first]  << std::endl;
    std::cout << std::endl;*/

    write_mmx(filename, g);
   // read_mmx("test.mmx", g);

    //boost::print_graph(g);
/*
    std::vector<std::vector<int>> neighbors(number_nodes); 

    for (size_t i = 0; i < number_nodes; ++i)
    {
        ;
    }*/
    /*
    std::string options;
    int nthreads=0;

    if (argc < 2)
    {
        std::cout << "Usage: graph-coloring <graph> <#threads>" << std::endl;
        return -1;
    }

    options = argv[1];
    nthreads=std::stoi(argv[2]);

    //create neighborhood information
    std::ifstream in_file;
    int size=0;

    if (options == "bmw")
    {
        std::cout << std::endl;
        std::cout << "Reading BMW3_2" << std::endl;
        size = 227362;    //bmw3_2 has 227362 entries        
        in_file.open("data/bmw3_2.mtx");

    }

    else if (options == "hollywood")
    {
        std::cout << std::endl;
        std::cout << "Reading hollywood_2009" << std::endl;
        size = 57515616;
        in_file.open("data/hollywood-2009.mtx");
    }

    else if (options == "queen")
    {
        std::cout << std::endl;
        std::cout << "Reading Queen_4147" << std::endl;
        size = 166823197;
        in_file.open("data/Queen_4147.mtx");
    }

    else if (options == "pwtk")
    {
        std::cout << std::endl;
        std::cout << "Reading Pressurized Wind Tunnel from Boeing" << std::endl;
        size = 217918;
        in_file.open("data/pwtk.mtx");
    }

    else if (options == "rmat_er")
    {
        std::cout << std::endl;
        std::cout << "Reading R-MAT-ER" << std::endl;
        size = 16777216;
        //in_file.open("data/rmat_er.txt");
        in_file.open("data/rmat_er_catal.txt");
    }

    else if (options == "rmat_g")
    {
        std::cout << std::endl;
        std::cout << "Reading R-MAT-g" << std::endl;
        size = 16777216;
        in_file.open("data/rmat_g_catal.txt");
        //in_file.open("data/rmat_g.txt");
    }

    else if (options == "rmat_b")
    {
        std::cout << std::endl;
        std::cout << "Reading R-MAT-b" << std::endl;
        size = 16777216;
        in_file.open("data/rmat_b_catal.txt");
        //in_file.open("data/rmat_b.txt");
    }

    else if (options == "channel")
    {
        std::cout << std::endl;
        std::cout << "Reading Channel" << std::endl;
        size = 4802000;
        in_file.open("data/channel-500x100x100-b050.mtx");
    }

    else if (options == "uk-2002")
    {
        std::cout << std::endl;
        std::cout << "Reading uk-2002" << std::endl;
        size = 18520486;
        in_file.open("data/uk-2002.mtx");
    }

    else if (options == "n3c4")
    {
        std::cout << std::endl;
        std::cout << "Reading n3c4-b3 graph" << std::endl;
        size = 60;
        in_file.open("data/n3c4-b3.mtx");
    }

    else
    {
        std::cout << "Wrong test graph! Options are:" << std::endl;
        std::cout << "bmw\nhollywood\nqueen\nrmat_er\nrmat_g\nrmat_b" << std::endl;
        return -1;
    }

    if (!in_file)
    {
        std::cout << "Can not open graph file!" << std::endl;
        return -1;
    }

    //std::cout << "sizing" << std::endl;
    std::vector<std::vector<int>> neighbors(size);  
    //std::cout << "sizing done" << std::endl;
    //std::cout << options << std::endl;
    std::string str;

    std::chrono::duration<double> total_color_dur;
    std::chrono::duration<double> tentative_color_dur;

    int a =0,b=0;
    double c=0.0;
    //using vector<vector<int>> to store neighborhood information

    if (options == "bmw" || options == "hollywood" || options == "queen" || options == "pwtk" ||
        options == "channel" || options == "uk-2002" || options == "n3c4") 
    {
        while(in_file >> a >> b >> c)
        {
            //std::cout << a << " " << b << " " << c << std::endl;
            if ( a != b )
            {
                neighbors[b-1].push_back(a-1); //mtx file of bmw3_2 starts indexing with 1
                neighbors[a-1].push_back(b-1);
            }
        } //end of while(in_file)
    }

    else //R-MAT starts indexing with 0!!!
    {
        //std::cout << "rmat" << std::endl;
        while(in_file >> a >> b)
        {
            //std::cout << a << " " << b << std::endl;
            if ( a != b )
            {
                neighbors[b].push_back(a); //mtx file of bmw3_2 starts indexing with 1
                neighbors[a].push_back(b);
            }
        } //end of while(in_file)
    }//

    in_file.close();

    //Get graph stats
    std::cout << " Getting statistics for " << options << std::endl;

    std::vector<int> degrees(size,0);

    int num_edges = 0;

    for (size_t i = 0; i < neighbors.size(); ++i)
    {
        degrees[i] = neighbors[i].size();
        num_edges+= neighbors[i].size();
    }

    //find maximum degree
    int max_degree = *(std::max_element(degrees.begin(), degrees.end()));

    //find average degree
    auto avg = std::accumulate(degrees.begin(), degrees.end(),0) / (double)size;

    std::cout << "  Max Degree: " << max_degree << std::endl;
    std::cout << "  Avg Degree: " << avg << std::endl;

    std::cout << "  num_edges " << num_edges << std::endl;
    //end of get graph stats

    /*Now do the actual graph coloring*/
   /* Greedy(options,neighbors, size);

    GreedyLU(options, neighbors, size);//*/

   /* for (size_t threads = 1; threads <= nthreads; threads=2*threads)
    {*//*
        Rokos(options, neighbors, size, nthreads);//*/
        /*Catalyurek(options, neighbors, size, nthreads);//*/
        /*SchedRev(options, neighbors, size, nthreads);//*/
    /*} */

    return 0;
}
