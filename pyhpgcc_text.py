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

gcc.Read("bmw3_2.mtx");

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

gcc.Read("ca-HepPh.mtx");

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

gcc.Read("amazon0312.mtx");

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

gcc.Read("roadNet-CA.mtx");

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

gcc.Read("soc-LiveJournal1.mtx");

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

#print(gcc.filename)
#gcc.shuffle();
#print(gcc.shuffled)
#output = gcc.colorGreedy(10);
#print(output)