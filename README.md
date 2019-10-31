# computeBricks Technical
## Jaisal Friedman
## Euler Project 215

## Compilation & Environment
1. c++11 (specified in make file)
2. g++ --version (shown below)
Apple LLVM version 10.0.1 (clang-1001.0.46.4)
Target: x86_64-apple-darwin18.2.0
Thread model: posix

## Execution
1. make will execute for 32x10 wall
2. ./output -w [width] -h [height]

## Code Structure
There are three main functions which are used to calculate the answer
1. computeRows
  - This computes the number of different unique combinations of 2 and 3 brick for the given width.
2. computeAlignment
  - This builds the alignment matrix which specifies which rows are in alignment with other rows (i.e. there is no crack)
3. computeCombinations
  - This builds the answer using memoization for the height. As we add columns (height), the number of combinations for each unique row combination is computed and memoized up. 
