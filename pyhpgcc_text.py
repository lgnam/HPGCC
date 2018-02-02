#!/usr/bin/python
import os
import sys

sys.path.append('./build/')
import pyhpgcc as hpgcc
help(hpgcc)

gcc = hpgcc.HPGCC()

gcc.read("test.input");
print(gcc.filename)
gcc.shuffle();
print(gcc.shuffled)
output = gcc.colorGreedy(10);
print(output)
