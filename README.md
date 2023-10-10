# COL333_A3
CNF Formulation and SAT Solvers

# File structure

## /scripts

Contains the necessary script compile.sh, run1.sh, run2.sh, run3.sh as described in the assignment pdf

## /src

The main executable code(s) for the problem statement

## /testing

The folder with all the executables, scripts, problem generator, checker and testcase files

## /submission

The final submitted files 

## /extras 

For now contains just TA_codes.zip (which has _MACOSX folder if required)

# Running the code

As mentioned in the assignment pdf, do the following:

## For part 1:
- ```cd testing``` (The folder where all required files are present)
- ```python3 problemGenerator <N> <K1> <K2>``` (Generate graph with N vertices and possibly K1 subgraph, K2 subgraph and stored in test.graph)
- ```./compile.sh``` (Compile all the .cpp files)
- ```./run1.sh test``` (Run Part1 and generate all files with name "test")
- ```minisat test.satinput test.satoutput``` (Generated satinput file is given as input to minisat solver and output produced is stored in test.satoutput)
- ```./run2.sh test``` (Run the mapping code (here named as output_graph.cpp) and generate output in test.mapping)
- ```python3 checker.py test.graph test.mapping 1``` (Checks whether there exists the k1 complete subgraph and k2 complete subgraph)

## For part 2:
- ```cd testing``` (The folder where all required files are present)
- ```python3 problemGenerator <N>``` (Generate graph with N vertices and stored in test.graph)
- ```./compile.sh``` (Compile all the .cpp files)
- ```./run3.sh test``` (Run Part2 and generate all files with name "test")
- ```python3 checker.py test.graph test.mapping 2``` (Checks whether the output is indeed the maximum complete subgraph)
