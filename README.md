# adventofcode2021

The [input.txt](input.txt) lists a number of directions with their corresponding distance/aim. Goal is to process all instructions and determine the horizontal position and the depth.

The number after each "up"/"down" means decreasing/increasing the aim/heading. A "forward" instruction means advancing x units and changing the depth by x*aim units.

## How to compile

All programs are written in C++ and can be built using CMake. Therefore, to make an out-of-source build, enter
``` bash
mkdir build && cd build
cmake ..
make
```
