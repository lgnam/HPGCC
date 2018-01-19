#!/usr/bin/env python3
"""Creation of Graphs."""

import subprocess
import argparse
from itertools import product
import numpy as np
import os 
from collections import namedtuple

Param = namedtuple("Param", "name value")

script_path = os.path.dirname(os.path.realpath(__file__))

def createGraph(exefile,filename, params):
    callargs = []
    for param in params:
        callargs.append('-'+param.name)
        callargs.append(param.value)
    fullcall = [exefile] + callargs
    print(fullcall)
    #subprocess.call(fullcall)   
    return


## define parameter ranges
names = []
a = np.linspace(0,1,12) 
names.append("a")
b = np.linspace(0,1,11) 
names.append("b")
c = np.linspace(0,1,11) 
names.append("c")
d = np.linspace(0,1,11) 
names.append("d")
parameters = [a,b,c,d]


## create graph outputs
outfolder = 'output'
exefile = './build/program'

if not os.path.exists(outfolder):
    os.makedirs(outfolder)

for items in product(*parameters):
    if (sum(items)==1):
        print(items)
        stritems = [ '%.3f' % item for item in items ]
        #stritems = list(map(str, items))
        strparam = "_".join(stritems)
        filename = 'Graph_%s.dat' % strparam
        print(filename)
        fullpath = os.path.join(script_path, outfolder , filename)
        print(fullpath)
        callargs = []
        for name, value in zip(names, stritems):
            callargs.append(Param(name,value))
        print(callargs)

        createGraph(exefile,filename,callargs)
