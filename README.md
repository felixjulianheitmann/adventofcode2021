# adventofcode2021

The [input.txt](input.txt) lists a number of directions with their corresponding distance. Goal is to process all instructions and determine the depth ("amount" down - amount "up") and distance (amount "forward"). The solution is the product of final depth and distance.

## How to compile

All programs are written in C++ and can be built using CMake. Therefore, to make an out-of-source build, enter
``` bash
mkdir build && cd build
cmake ..
make
```
