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
        #callargs.append('-'+param.name)
        callargs.append(param.value)
    callargs.append(filename)
    fullcall = [exefile] + callargs
    print(fullcall)
    subprocess.call(fullcall)   
    return

## define parameter ranges
names = []

number_nodes = np.linspace(10,100,10) 
names.append("number_nodes")

number_edges = np.linspace(100,1000,10) 
names.append("number_edges")

a = np.linspace(0,1,2) 
names.append("a")

b = np.linspace(0,1,2) 
names.append("b")

c = np.linspace(0,1,2) 
names.append("c")

d = np.linspace(0,1,2) 
names.append("d")

parameters = [number_nodes,number_edges,a,b,c,d]

## create graph outputs
outfolder = 'build/output'
exefile = './build/RMAT_generator'

if not os.path.exists(outfolder):
    os.makedirs(outfolder)

for items in product(*parameters):
    if (sum(items[2:])==1):
        print(items)
        stritems = [ '%.3f' % item for item in items ]
        #stritems = list(map(str, items))
        strparam = "_".join(stritems)
        filename = 'Graph_%s.mtx' % strparam
        print(filename)
        fullpath = os.path.join(script_path, outfolder , filename)
        print(fullpath)
        callargs = []
        for name, value in zip(names, stritems):
            callargs.append(Param(name,value))
        print(callargs)

        createGraph(exefile,fullpath,callargs)