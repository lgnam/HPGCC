#include "rokos.hpp"
#include <iostream>
#include <chrono>
#include <numeric> 
#include <algorithm>
#include <string>
#include <fstream>

#include <omp.h>

#include "check_coloring.hpp"
#include "get_color_stats.hpp"

bool Rokos(std::string file, std::vector<std::vector<int>> &neighbors, int size, int nthreads)
{
    std::cout << std::endl;
    std::cout << "Rokos' Algorithm with " << nthreads << " threads" << std::endl;

    auto begin_color = std::chrono::system_clock::now();

    int round = 0;
    int max_color = 1;

    std::chrono::duration<double> total_color_dur;
    std::chrono::duration<double> tentative_color_dur;

    std::vector<int> vertex_colors(size, 0);

    std::vector<double> mem (nthreads, 0.0);
    std::vector<double> loop1(nthreads, 0.0);
    std::vector<double> loop2(nthreads, 0.0);

    //tentative coloring
    #pragma omp parallel for schedule(static) //num_threads(nthreads)//shared(max_color)
    for (size_t vert = 0; vert < size; ++vert)
    {
        // std::cerr << omp_get_thread_num() << std::endl;
        //std::cout << vert << std::endl;
        //std::vector<int> forbiddenColors ( max_color + 900, -1 );
        auto tic = omp_get_wtime();
        std::vector<int> forbiddenColors(2000, -1);
        auto toc = omp_get_wtime();
        mem[omp_get_thread_num()]+=toc-tic;

        tic = omp_get_wtime();
        for (size_t neigh = 0; neigh < neighbors[vert].size() ; ++neigh)
        {
            int neigh_id = neighbors[vert][neigh];
            //std::cout << " neigh " << neigh_id << std::endl;
            forbiddenColors[ vertex_colors[neigh_id] ] = vert;
        }
        toc = omp_get_wtime();
        loop1[omp_get_thread_num()]+=toc-tic;

        tic = omp_get_wtime();
        for (size_t i = 0; i < forbiddenColors.size(); ++i)
        {
            if (forbiddenColors[i] != vert)
            {
                /*if (i == forbiddenColors.size()-1)
                {
                    #pragma omp atomic
                    ++max_color;
                }//*/
                //std:cout << " " << vert << " gets " << i << std::endl;
                vertex_colors[vert] = i; //i

                break;
            }
        }//*/
        toc = omp_get_wtime();
        loop2[omp_get_thread_num()]+=toc-tic;
    }
    //end of tentative coloring
    tentative_color_dur = std::chrono::system_clock::now() - begin_color;
    
    //mark all vertices for inspection
    std::vector<int> worklist(size);
    std::iota(worklist.begin(), worklist.end(), 0);

    //inspect vertices and check the validity of their color; if invalid mark it for recoloring;
    while ( !worklist.empty() )
    {
        //std::cout << "checking vertices" << std::endl;
        std::vector<std::vector<int>> recolor(nthreads);//(nthreads);

        #pragma omp parallel for schedule(static) //num_threads(nthreads) //shared(max_color)
        for (size_t iter = 0; iter < worklist.size(); ++iter)
        {
            int vert = worklist[iter];
           // if (vert == 1 || vert == 0)
                //std::cout << vert << " with color " << vertex_colors[vert]  << " has " << neighbors[vert].size() << " neighbors" << std::endl;
            //check if vertex has to be recolored and recolor if necessary
            for (size_t neigh : neighbors[vert])
            {
               // if (vert == 0 || vert ==1 )
                    //std::cout << " checking " << neigh << " with color " << vertex_colors[neigh]<< std::endl;

                if ( (vertex_colors[vert] == vertex_colors[neigh]) && (neigh > vert) )
                {
                    //if (vert == 0 || vert == 1)
                       // std::cout << "     problem! " << std::endl;

                    std::vector<int> forbiddenColors(2000,-1); //( max_color + 900, -1 );
                    
                    for (size_t neigh = 0; neigh < neighbors[vert].size(); ++neigh)
                    {
                        int neigh_id = neighbors[vert][neigh];
                        forbiddenColors[ vertex_colors[neigh_id] ] = vert;
                    }
        
                    for (size_t i = 0; i < forbiddenColors.size(); ++i)
                    {
                        //if (vert == 0 || vert ==1)
                           // std::cout << "i " << i << " forbiddenColors[i] " << forbiddenColors[i] << " vert " << vert << std::endl;

                        if (forbiddenColors[i] != vert)
                        {
                            //std::cout << "recolor" << std::endl;

                            /*if ( vert == 1 || vert == 0)
                                std::cout << "recolor with " << i << std::endl;*/

                            /*if (i == forbiddenColors.size()-1)
                            {
                                #pragma omp atomic
                                ++max_color;
                            }*/
                            vertex_colors[vert] = i;
                            recolor[omp_get_thread_num()].push_back(vert);
                            break;
                        }
                    }
                }
            } //end of for loop check if vertex has to be recolored and recolor if necessary*/
        } //end of parallel for loop for vertex checking

        worklist.clear();
        
        //create worklist for next round of inspection
        for (auto rec : recolor)
        {
            worklist.insert(worklist.end(), rec.begin(), rec.end());
        }
        //std::cout << worklist.size() << " round " << round << std::endl;
        ++round;
    } //end of while( !worklist.empty() ) //end of inspect and recolor vertices

    total_color_dur = std::chrono::system_clock::now() - begin_color;
    
    int max_colors = *( std::max_element(vertex_colors.begin(), vertex_colors.end()) ) + 1;

    //Check vertex coloring
    bool valid = CheckColoring(neighbors, vertex_colors, size);
    std::string valid_str = "valid";
    //Check vertex coloring
    if(!valid)
    {
        std::cerr << "  WRONGFUL COLORING DETECTED!" << std::endl;
        //return false;
        valid_str.clear();
        valid_str = "invalid";

    }

    std::vector<double> times;
    times.push_back(total_color_dur.count());
    times.push_back(tentative_color_dur.count());
    times.push_back(total_color_dur.count()-tentative_color_dur.count());
    
    GetColorStats(file, vertex_colors, size, "Rokos", nthreads, times);//*/

    std::ofstream output;
    output.open("output/times_rokos.csv", std::ofstream::app);

    output << file << ", " << size << ", " << "Rokos" << ", " << nthreads << ", " << total_color_dur.count() << ", " << tentative_color_dur.count() << ", ";
    output << total_color_dur.count() - tentative_color_dur.count() << ", " << max_colors << ", " << round  << ", " << valid_str << ", ";
    
    for (auto it : mem)
    {
        output << it << ", ";
    }

    for (auto it : loop1)
    {
        output << it << ", ";
    }

    for (auto it : loop2)
    {
        output << it << ", ";
    }

    output  << std::endl;

    output.close();

    return true;
}
