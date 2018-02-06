#!/usr/bin/python
import os
import sys

sys.path.append('./build/')
import pyhpgcc as hpgcc
#help(hpgcc)

gcc = hpgcc.HPGCC()

gcc.Read("cit-Patents.mtx");

gcc.Shuffle();

gcc.Greedy();
gcc.GreedyLU();
gcc.Catalyurek(1);
gcc.SchedRev(1);
gcc.Catalyurek(2);
gcc.SchedRev(2);
gcc.Catalyurek(4);
gcc.SchedRev(4);
gcc.Catalyurek(8);
gcc.SchedRev(8);

gcc2 = hpgcc.HPGCC()

gcc2.Read("bmw3_2.mtx");

gcc2.Shuffle();

gcc2.Greedy();
gcc2.GreedyLU();
gcc2.Catalyurek(1);
gcc2.SchedRev(1);
gcc2.Catalyurek(2);
gcc2.SchedRev(2);
gcc2.Catalyurek(4);
gcc2.SchedRev(4);
gcc2.Catalyurek(8);
gcc2.SchedRev(8);

#print(gcc.filename)
#gcc.shuffle();
#print(gcc.shuffled)
#output = gcc.colorGreedy(10);
#print(output)
