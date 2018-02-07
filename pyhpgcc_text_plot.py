#!/usr/bin/python
# read all files from output folder
import numpy as np
import os
import glob
import matplotlib
print(matplotlib.__version__)
import pylab as plt
import re


def extract_header(line):
    pattern = re.compile(r"""\s*\#\s*                 # hash and any number of whitespaces
                             (?P<file>.*?)         
                             \s*,\s*                  
                             (?P<algo>.*?)     
                             \s*,\s*                    
                             (?P<numthreads>.*?) 
                             \s*,\s*
                             (?P<runtime>.*?)
                             \s*,\s*""", re.VERBOSE)
    match = pattern.match(line)

    file = match.group("file")
    algo = match.group("algo")
    numthreads = int(match.group("numthreads"))
    runtime = float(match.group("runtime"))
    return file, algo, numthreads, runtime


def extract_color(line):
    ints = re.findall(r'\d+', line)
    ints = [int(s) for s in ints]
    return ints[0], ints[1]


basefolder = "./output/"

outputs = glob.glob(basefolder + "*.csv")
print(outputs)

fig1, ax1 = plt.subplots(figsize=(6, 2))
fig1.tight_layout()

for filename in outputs:
    # read file
    if not "times" in filename:
        x = []
        y = []
        with open(filename, "r") as f:
            print(filename)
            header = True
            for line in f:
                if header:
                    header = False
                    #print(line)
                    file, algo, numthreads, runtime = extract_header(line)
                else:
                    colorID, population = extract_color(line)
                    x.append(colorID)
                    y.append(population)
                    #print(colorID)
                    #print(population)


        ax1.semilogy(x,y,label=algo+str(numthreads))

legend = ax1.legend(loc='upper center', shadow=True)
plt.show()
    
fig1.savefig("./output/plot_" + str(file) + ".pdf")