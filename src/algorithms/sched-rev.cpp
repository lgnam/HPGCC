#include "sched-rev.hpp"
#include "greedy.hpp"
#include "check_coloring.hpp"
#include "get_color_stats.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <omp.h>

bool SchedRev(std::string file, std::vector<std::vector<int>> &neighbors, int size, int nthreads)
{
    std::cout << std::endl;
    std::cout << "Scheduled-Revisits Algorithm with " << nthreads << " threads" << std::endl;

    auto begin_color = std::chrono::system_clock::now();

    //get initial coloring
    std::vector<int> vertex_colors(size,0);
    std::vector<int> num_color_vertices(size, 0);
    int colors;

    GreedyInit(file, neighbors, size, vertex_colors, &colors, num_color_vertices);
    
    double sched_time = 0.0;

    double gamma = size / colors;

    //std::cout << "parts: " << num_regions << ", colors: " << colors << ", gamma (parts/colors): " << gamma << std::endl;
    //std::cout << "colors " << colors << " gamma " << gamma << std::endl;
    int no_of_iterations = 3;
    int errors = 0;
/*
    double loop1 = 0.0;
    double loop2 = 0.0;
    double sort_reverse = 0.0;

    double loop_2a = 0.0;
    double loop_2b = 0.0;*/

    for (size_t iteration = 0; iteration < no_of_iterations; ++iteration)
    {
        ///std::cout << "ITERATION " << iteration+1 << "/" << no_of_iterations << std::endl;

        //create ordered set of over-full bins in increasing color order
        //and create an ordered set under-full bins in decreasing color order

      /* auto loop1_tic = std::chrono::system_clock::now();*/
        
        std::vector<int> overfull_colors;
        std::vector<int> underfull_colors;

        for (size_t i = 0; i < colors; ++i)
        {
            if ( num_color_vertices[i] > gamma )
            {
                overfull_colors.push_back(i);
            }

            else if ( num_color_vertices[i] < gamma )
            {
                underfull_colors.push_back(i);
            }
        }
/*
        std::chrono::duration<double> loop1_dur = std::chrono::system_clock::now() - loop1_tic;
        loop1 += loop1_dur.count();

        auto sort_rev_tic = std::chrono::system_clock::now();*/
        //order underfull colors in increasing size
        std::sort(underfull_colors.begin(), underfull_colors.end(), [&num_color_vertices] (int a, int b) { return num_color_vertices[a] > num_color_vertices[b];} );
        std::reverse(underfull_colors.begin(), underfull_colors.end());
/*
        std::chrono::duration<double> sort_rev_dur = std::chrono::system_clock::now() - sort_rev_tic;
        sort_reverse += sort_rev_dur.count();

        auto loop2_tic = std::chrono::system_clock::now();
*/
        std::vector<std::vector<std::vector<int>>> moves(overfull_colors.size(), std::vector<std::vector<int>>(underfull_colors.size())); //list containing moves from overfull to underfull bins, moves[i][j] moves partition j to color i
        std::vector<std::vector<int>> moves_2(colors);
        //for each j E Q_o do from Algorithm 4
        for (size_t of_color = 0; of_color < overfull_colors.size(); ++of_color)
        {
            int of_color_id = overfull_colors[of_color];

            std::vector<int> surplus_verts(num_color_vertices[ of_color_id ]-gamma); //contains ids of vertices which have to be recolored

            //find vertices with color i, and add them to the list V'(j) from Algorithm 4
            //Select V'(j) subset of V(j) such that |V'(j)|=|V(j)| - gamma
            //for (size_t j = 0; j < surplus_verts.size(); ++j)

            //auto loop_2a_tic = std::chrono::system_clock::now();
            size_t counter = 0;
            for (size_t j = 0; /*j < size ||*/ counter < surplus_verts.size(); ++j)
            {
                if ( vertex_colors[j] == of_color_id )
                {
                    surplus_verts[counter] = j;
                    ++counter;
                }
            }

           // std::cout << " surplus vertices created" << std::endl;

           /* //DEBUG
            for (auto at : surplus_verts)
            {
                std::cout << at << std::endl;  
                
                for (auto ne : neighbors[at])
                    std::cout << " " << ne << std::endl;
            }//END OF DEBUG//*/
/*
            std::chrono::duration<double> loop2a_dur = std::chrono::system_clock::now() - loop_2a_tic;
            loop_2a += loop2a_dur.count();*/

            //for each k E Q_u AND V'(j) neq 0 do (Algorithm 4)
            //note that the underfull_bins are sorted in descending order of their size

            //auto loop2b_tic = std::chrono::system_clock::now();
            int glob_it = 0;
            for(size_t uf_color = 0; uf_color < underfull_colors.size() && glob_it < surplus_verts.size()/*!surplus_verts.empty()*/; ++uf_color)
            {
                int uf_color_id = underfull_colors[uf_color];
                //std::cout << "   underfull_color " << underfull_colors[uf_color] << " has size " << color_vertices[ underfull_colors[uf_color] ].size() << std::endl;
                std::vector<int> movable_verts(gamma - num_color_vertices[ uf_color_id ] );
                
                size_t iterator =0;
                for (size_t vert_to_move = 0; vert_to_move < movable_verts.size() && iterator < surplus_verts.size()/*!surplus_verts.empty()*/; ++vert_to_move)
                {
                    moves[of_color][ uf_color ].push_back(surplus_verts[iterator]);
                    ++iterator;
                    
                   /* moves[ uf_color_id ].push_back(surplus_verts[0]);
                    surplus_verts.erase( surplus_verts.begin() );*/
                }

                glob_it += iterator;
            }
/*
            std::chrono::duration<double> loop2b_dur = std::chrono::system_clock::now() - loop2b_tic;
            loop_2b += loop2b_dur.count();*/
        }
/*
        std::chrono::duration<double> loop2_dur = std::chrono::system_clock::now() - loop2_tic;
        loop2 += loop2_dur.count();*/
        for (size_t i = 0; i < underfull_colors.size(); ++i)
        {
            //int counter = 0;
            int uf_color_id = underfull_colors[i];

            auto sched_tic = std::chrono::system_clock::now();
            
            for (size_t of_col = 0; of_col < overfull_colors.size(); ++of_col)
            {
                int of_col_id = overfull_colors[of_col];
                #pragma omp parallel for schedule(static)
                for (size_t vert = 0; vert < moves[of_col][i].size(); ++vert)
                {
                    //check if new color is permissible and if yes, assign it;
                    bool permissible = true;
                    int new_color = uf_color_id;
                    size_t vert_id = moves[of_col][i][vert];

                    for (auto neigh_id : neighbors[ vert_id ])
                    {
                        //forbid re-coloring if neighbor has the same color
                        if( (vertex_colors[ neigh_id ] == new_color))
                        {
                            permissible = false;
                            continue;
                        }

                        //forbid coloring if neighbor with smaller vertex id is also in the queue and would get the same color 
                        /*auto iter = std::find(moves[new_color].begin(), moves[new_color].end(), neigh_id);
                        if (iter != moves[new_color].end() && neigh_id < vert_id)
                        {
                            ++errors;
                            permissible = false;
                        }//*/
                    }

                    if (permissible)
                    {
                        //#pragma omp critical 
                        //{
                            #pragma omp atomic
                            num_color_vertices[ vertex_colors[vert_id] ]--;

                            vertex_colors[ vert_id ] = new_color; 

                            #pragma omp atomic                        
                            num_color_vertices[ new_color ]++;
                        //}
                        // ++counter;
                    }
                }
            }//end of omp parallel for

            std::chrono::duration<double> sched_dur = std::chrono::system_clock::now() - sched_tic;
            sched_time += sched_dur.count();
        } //end of for loop iterating underfull colors

    } //end of for loop iterating no_of_iterations

    std::chrono::duration<double> total_color_dur = std::chrono::system_clock::now() - begin_color;

    int max_colors = *( std::max_element(vertex_colors.begin(), vertex_colors.end()) ) + 1;
    
    //Check vertex coloring
    bool valid = CheckColoring(neighbors, vertex_colors, size);
    std::string valid_str = "valid";
    if(!valid)
    {
        std::cerr << "  WRONGFUL COLORING DETECTED!" << std::endl;
        //return false;
        valid_str.clear();
        valid_str = "invalid";

    }

    GetColorStats(file, vertex_colors, size, "Sched-Rev", nthreads);
//*/
    std::ofstream output;
    output.open("output/times_sched-rev.csv", std::ofstream::app);

    output << file << ", " << size << ", " << "Sched-Rev" << ", " << nthreads << ", " << total_color_dur.count() << ", ";
    output << total_color_dur.count() - sched_time << ", " << sched_time << ", ";
    output << max_colors << ", " << valid_str << std::endl;

    output.close();

    return true;
}
