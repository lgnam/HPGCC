#!/usr/bin/python
import os
import sys

sys.path.append('./build/')
import pyhpgcc as hpgcc
#help(hpgcc)

gcc = hpgcc.HPGCC()

gcc.Read("Graph_10.000_100.000_0.000_0.000_0.000_1.000.mtx");
gcc.Greedy();
#print(gcc.filename)
#gcc.shuffle();
#print(gcc.shuffled)
#output = gcc.colorGreedy(10);
#print(output)
