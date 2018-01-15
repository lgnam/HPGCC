#ifndef SCHED_REV_HPP
#define SCHED_REV_HPP

#include <vector>
#include <string>

bool SchedRev(std::string file, std::vector<std::vector<int>> &neighbors, int size, int nthreads);
#endif