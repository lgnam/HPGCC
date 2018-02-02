#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <map>

#include <omp.h>

#include "algorithms/rokos.hpp"
#include "algorithms/greedy.hpp"
#include "algorithms/greedy-lu.hpp"
#include "algorithms/sched-rev.hpp"
#include "algorithms/catalyurek.hpp"

#include "io/io.hpp"


int main (int argc, char *argv[])
{
    std::vector<std::vector<int>> neighbors;

    std::string filename = "bmw3_2.mtx";

    int size = read_mmx(filename, neighbors);

    std::string options = "greedy";

    Greedy(options,neighbors,size);


    return 1;
}