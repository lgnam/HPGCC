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

#include <boost/graph/use_mpi.hpp>
#include <boost/graph/distributed/mpi_process_group.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/rmat_graph_generator.hpp>
#include <boost/random/linear_congruential.hpp>

int main (int argc, char *argv[])
{
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
