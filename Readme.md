DESCRIPTION:
cgol is a program which reads in a seed file of dimensions exactly 40x20 characters, then performs Conway's Game of Life algorithm on that seed file, writing each tick to stdout. Seed files must be formatted as lines of 0's and 1's. The user may also specify the number of ticks the program should run before pausing. If this number is not specified, it defaults to 50.
The commandline for cgol is as follows: "$./cgol [seedfile] [ticks]"

dynCGOL is almost identical to cgol, but it can read in a seed file of any dimensions the user specifies.
The commandline for dynCGOL is as follows: "$./dynCGOL [seedfile] [ticks] [rows] [columns]"

COMPILATION:
Compile all: $make all
Clean compiled files: make clean
